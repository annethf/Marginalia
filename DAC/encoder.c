#include <malloc.h>
#include <memory.h>
#include <math.h>
#include "header.h"

static unsigned low = 0;
static unsigned high = TOP_VALUE;
static unsigned neglectedSecondhighBit = 0;
unsigned encounter = 0;
unsigned srcSymbolNum = 200;
float k = 0.50;
float p1;
float p0;

void encodeOneSymbol(byte curSymbol, unsigned *encodeOutcome, unsigned symbolCounter)
{
    unsigned range = high - low + 1;
    //计算区间
    if(srcSymbolNum - symbolCounter > 15)
    {
        if(curSymbol)
            low = low + (unsigned)(range * (1 - p1) + 0.5);
        else
            high = low + (unsigned)(range * p0 + 0.5) - 1;
    }
    else
    {
        if(curSymbol)
            low = low + (unsigned)(range * 0.50 + 0.5);
        else
            high = low + (unsigned)(range * 0.50 + 0.5) - 1;
    }
    //调整区间
    byte bit;
    while(1)
    {
        if(!(FHIGH(high) ^ FHIGH(low)))
        {
            bit = FHIGH(high) >> (BIT - 1) & 1;
            PUTBIT(encodeOutcome, encounter, bit);
            encounter++;

            while(neglectedSecondhighBit)
            {
                PUTBIT(encodeOutcome, encounter, !bit);
                encounter++;
                neglectedSecondhighBit--;
            }
        }
        else if((!SHIGH(high)) && FHIGH(low))
        {
            neglectedSecondhighBit++;
            low -= FIRST_QUATER;
            high -= FIRST_QUATER;
        }
        else break;
        //扩展区间
        low <<= 1;
        low &= TOP_VALUE;
        high <<= 1;
        high |= 1;
        high &= TOP_VALUE;
    }
}

void encodeEnding(unsigned *encodeOutcome)
{
    byte highBit = SHIGH(high) >> (BIT -2) & 1;
    byte bit = (highBit ? (FHIGH(high) >> (BIT - 1) & 1) : (FHIGH(low) >> (BIT - 1) & 1));
    PUTBIT(encodeOutcome, encounter, bit);
    encounter++;
    while(neglectedSecondhighBit)
    {
        PUTBIT(encodeOutcome, encounter, !bit);
        encounter++;
        neglectedSecondhighBit--;
    }
    PUTBIT(encodeOutcome, encounter, !highBit);
    encounter++;
}

unsigned *encode(unsigned *src)
{
    p1 = powf(0.50, k);
    p0 = powf(0.50, k);
    unsigned *encodeOutcome = (unsigned *)malloc(sizeof(unsigned) * ((srcSymbolNum >> 5) + 1));
    memset(encodeOutcome, 0 , sizeof(unsigned) * ((srcSymbolNum >> 5) + 1));
    unsigned i;
    for(i = 0; i < srcSymbolNum; i++)
        encodeOneSymbol(GETBIT(src, i), encodeOutcome, i);
    encodeEnding(encodeOutcome);
    return encodeOutcome;
}
