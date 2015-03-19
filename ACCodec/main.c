#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include <math.h>
#include "header.h"

extern unsigned enCounter;
extern unsigned value;
extern unsigned deCounter;
unsigned *encode(unsigned *src);
unsigned *decode(unsigned *encodeOutcome);

/**
 * \brief generate source with srcSymbomNum symbol numbers and probability p
 * \param src (unsigned*) generated source
 * \param srcSymbolNum (unsigned) source symbol number
 * \param p (float) probability of symbol 1
 */
void genSource(unsigned *src, unsigned srcSymbolNum, float p)
{
    unsigned i;
    byte s;
    for(i = 0; i < srcSymbolNum; i++)
    {
        s = (rand() < RAND_MAX * p);
        PUTBIT(src, i, s);
    }
}

/**
 * \brief initialize encoder/decoder according to flag
 * \param flag (int) indicate encoding with 0 or decoding with 1
 * \param encodeOutcome (unsigned*) used only in the decoder
 */
void init(int flag, unsigned *encodeOutcome)
{
    high = TOP_VALUE;
    low = 0;
    if(flag)
    {
        int i = 0;
        for(i = 0; i < BIT; i++)
        {
            value <<= 1;
            value |= GETBIT(encodeOutcome, deCounter);
            deCounter++;
        }
    }
}

/**
 * \brief compare dec with src
 * \param dec (const unsigned*) decoding results
 * \param src (const unsigned*) source
 * \return errorNum (int) number of decoding error
 */
int errorCheck(const unsigned *dec, const unsigned *src)
{
    int errorNum = 0;
    unsigned i = 0;
    for(i = 0; i < srcSymbolNum; i++)
        errorNum += (GETBIT(dec, i) ^ GETBIT(src, i));
    return errorNum;
}

int main()
{
    printf("Input source symbol number:");
    scanf("%d", &srcSymbolNum);
    printf("Input probabiliy of symbol 1:");
    scanf("%f", &pr);

    //source
    unsigned *source = (unsigned *)malloc(((srcSymbolNum >> 5) + 1) * sizeof(unsigned));
    memset(source, 0, ((srcSymbolNum >> 5) + 1) * sizeof(unsigned));
    //encoding results
    unsigned *encodeOutcome = NULL;
    //decoding results
    unsigned *decodeOutcome = NULL;
    int errorNum = 0;

    //generate source randomly
    srand(time(NULL));
    genSource(source,srcSymbolNum, pr);
    //encode
    init(0, NULL);
    encodeOutcome = encode(source);
    //source entropy
    printf("entropy = %.2f\n", ENTROPY(pr));
    //decode
    init(1, encodeOutcome);
    decodeOutcome = decode(encodeOutcome);
    //check error bit
    errorNum = errorCheck(decodeOutcome, source);
    printf("errorNum = %d\n", errorNum);

    free(source);
    source = NULL;
    free(encodeOutcome);
    encodeOutcome = NULL;
    free(decodeOutcome);
    decodeOutcome = NULL;
    system("pause");
    return 0;
}
