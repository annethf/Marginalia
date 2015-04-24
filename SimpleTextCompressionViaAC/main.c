#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <sys/stat.h>
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
void genSource(unsigned *src)
{
    FILE *srcFile = fopen("encoder.c", "r");
    if(!srcFile)
    {
        printf("Source file open error!\n");
        getchar();
        exit(1);
    }
    char c;
    byte bit;
    unsigned j = 0, i;
    int oneNum = 0;
    while(!feof(srcFile))
    {
        c = fgetc(srcFile);
        for(i = 0;  i < 8; i++, j++, c >>= 1)
        {
            bit = c & 1;
            if(bit)
                oneNum++;
            PUTBIT(src, j, bit);
        }
    }
    pr = (double)(oneNum) / srcSymbolNum;
    printf("pr = %.2f\n", pr);
    fclose(srcFile);
}

/**
 * \brief convert decoded binary file to text file
 * \param decodeOutcome (unsigned*) decode result
 */
void bin2Txt(unsigned *decodeOutcome)
{
    FILE *fout = fopen("output.txt", "w");
    if(fout == NULL)
    {
        printf("output file open error!\n");
        getchar();
        exit(1);
    }
    unsigned i, j;
    byte bit;
    char c = 0;
    for(i = 0, j = 0; j < srcSymbolNum && i < 8; j++, i++)
    {
        bit = GETBIT(decodeOutcome, j);
        bit <<= i;
        c |= bit;
        if(i == 7)
        {
            fprintf(fout, "%c", c);
            i = -1;
            c = 0;
        }
    }
    fclose(fout);
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
    //get file size
    struct stat buf;
    stat("encoder.c", &buf);
    srcSymbolNum = (int)buf.st_size << 3;
    printf("srcSymbolNum = %d\n", srcSymbolNum);
    //initialize source
    unsigned *source = (unsigned *)malloc(((srcSymbolNum >> 5) + 1) * sizeof(unsigned));
    memset(source, 0, ((srcSymbolNum >> 5) + 1) * sizeof(unsigned));
    //generate binary source
    srand(time(NULL));
    genSource(source);
    //encode
    init(0, NULL);
    unsigned *encodeOutcome = encode(source);
    printf("encoded number = %d\n", enCounter);
    //decode
    init(1, encodeOutcome);
    unsigned *decodeOutcome = decode(encodeOutcome);
    //check error bit
    int errorNum = errorCheck(decodeOutcome, source);
    printf("errorNum = %d\n", errorNum);
    //convert binary file to text file
    bin2Txt(decodeOutcome);

    free(source);
    source = NULL;
    free(encodeOutcome);
    encodeOutcome = NULL;
    free(decodeOutcome);
    decodeOutcome = NULL;

    return 0;
}
