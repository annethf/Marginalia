#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "header.h"

unsigned value = 0;
unsigned deCounter = 0;

/**
 * \brief update high and low according bit from encoding results
 * \param encodeOutcome (unsigned*) encoding results
 * \return symbol (byte) decoding symbol
 */
byte decodeOneSymbol(unsigned *encodeOutcome)
{
    byte symbol;
    //computing current range
    unsigned range = high - low + 1;
    //estimate current decode symbol
    if((value - low) < (unsigned)(range * (1 - pr) + 0.5))
    {
        symbol = 0;
        high = low + (unsigned)(range * (1 - pr) + 0.5) - 1;
    }
    else
    {
        symbol = 1;
        low = low + (unsigned)(range * (1 - pr) + 0.5);
    }
    //update range and value
    while(1)
    {
        if(!(FHIGH(high) ^ FHIGH(low)));           //condition 1 and 2
        else if((!SHIGH(high)) && SHIGH(low))      //condition 3
        {
            low -= FIRST_QUATER;
            high -= FIRST_QUATER;
            value -= FIRST_QUATER;
        }
        else break;        //others
        //expand range
        low <<= 1;
        low &= TOP_VALUE;
        high <<= 1;
        high |= 1;
        high &= TOP_VALUE;
        //update value
        value <<= 1;
        value |= GETBIT(encodeOutcome, deCounter);
        value &= TOP_VALUE;
        deCounter++;
    }
    return symbol;
}

/**
 * \brief decode encoding results
 * \param encodeOutcome (unsigned*) encoding results
 * \return decoding results
 */
unsigned *decode(unsigned *encodeOutcome)
{
    unsigned *decodeOutcome = NULL;
    unsigned i = 0;
    decodeOutcome = (unsigned*)malloc(sizeof(unsigned) * ((srcSymbolNum >> 5) + 1));
    memset(decodeOutcome, 0, sizeof(unsigned) * ((srcSymbolNum >> 5) + 1));
    for(i = 0; i < srcSymbolNum; i++)
        PUTBIT(decodeOutcome, i, decodeOneSymbol(encodeOutcome));
    return decodeOutcome;
}
