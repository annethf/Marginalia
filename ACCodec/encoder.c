#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include "header.h"

unsigned enCounter = 0;
unsigned neglectedSecondhighBit = 0;

/**
 * \brief encoding curSymbol and save the results in encodeOutcome
 * \param curSymbol (byte) current encoding symbol
 * \param encodeOutcome (unsigned*) encoding results
 */
void encodeOneSymbol(byte curSymbol, unsigned *encodeOutcome)
{
    //computing current range
    unsigned range = high - low + 1;
    //computing high and low according to current symbol
    if(curSymbol)
        low = low + (unsigned)(range * (1 - pr) + 0.5);
    else
        high = low + (unsigned)(range * (1 - pr) + 0.5) - 1;
    //update range
    while(1)
    {
        if(!(FHIGH(high) ^ FHIGH(low)))    //condition 1 and 2
        {
            byte bit = FHIGH(high) >> (BIT - 1) & 1;
            PUTBIT(encodeOutcome, enCounter, bit);
            enCounter++;
            //condition 3 meets with condition 1
            while(neglectedSecondhighBit)
            {
                PUTBIT(encodeOutcome, enCounter, !bit);
                enCounter++;
                neglectedSecondhighBit--;
            }
        }
        else if((!SHIGH(high)) && SHIGH(low))  //condition 3
        {
            neglectedSecondhighBit++;
            low -= FIRST_QUATER;
            high -= FIRST_QUATER;
        }
        else break; //others
        //expand range
        low <<= 1;
        low &= TOP_VALUE;
        high <<= 1;
        high |= 1;
        high &= TOP_VALUE;
    }
}

/**
* \brief encoding source and save the results in encodeOutcome
* \param encodeOutcome (unsigned*) encoding results
*/
void encodeEnding(unsigned *encodeOutcome)
{
    byte highBit = SHIGH(high) >> (BIT -2) & 1;
    byte bit = (highBit ? (FHIGH(high) >> (BIT - 1) & 1) : (FHIGH(low) >> (BIT - 1) & 1));
    PUTBIT(encodeOutcome, enCounter, bit);
    enCounter++;
    while(neglectedSecondhighBit)
    {
        PUTBIT(encodeOutcome, enCounter, !bit);
        enCounter++;
        neglectedSecondhighBit--;
    }
    PUTBIT(encodeOutcome, enCounter, !highBit);
    enCounter++;
}

/**
 * \brief encoding the source
 * \param src (unsigned*) source generated randomly
 * \return encoding results
 */
unsigned *encode(unsigned *src)
{
    unsigned *encodeOutcome = NULL;
    encodeOutcome = (unsigned *)malloc(((srcSymbolNum >> 5) + 1) * sizeof(unsigned));
    memset(encodeOutcome, 0, (((srcSymbolNum >> 5) + 1)) * sizeof(unsigned));
    unsigned i = 0;
    for(i = 0; i < srcSymbolNum; i++)
        encodeOneSymbol(GETBIT(src, i), encodeOutcome);
    encodeEnding(encodeOutcome);
    return encodeOutcome;
}
