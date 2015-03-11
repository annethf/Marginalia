#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>
#include "header.h"

extern unsigned srcSymbolNum;
extern unsigned encounter;
extern int saveNode;
extern int pathNum;
unsigned *encode(unsigned *src);
unsigned *genSideSrc(unsigned *src);
unsigned *decode(Node *tree, unsigned *encodeOutcome, unsigned *sideSrc);

unsigned *genSource(unsigned srcSymbolNum)
{
    unsigned *src = (unsigned *)malloc(sizeof(unsigned) * ((srcSymbolNum >> 5) + 1));
    memset(src, 0, sizeof(unsigned) * ((srcSymbolNum >> 5) + 1));
    unsigned i;
    byte symbol;
    for(i = 0; i < srcSymbolNum; i++)
    {
        symbol = (rand() < RAND_MAX * 0.50);
        PUTBIT(src, i, symbol);
    }
    return src;
}

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
    unsigned *source = NULL;
    unsigned *encodeOutcome = NULL;
    unsigned *sideSrc = NULL;
    unsigned *decodeOutcome = NULL;
    Node *tree = (Node*)malloc(sizeof(Node)*pathNum);;
    int errorNum = 0;

    srand(time(NULL));
    source = genSource(srcSymbolNum);
    encodeOutcome = encode(source);
    printf("encounter = %u\n", encounter);
    srand(time(NULL));
    sideSrc = genSideSrc(source);

    decodeOutcome = decode(tree, encodeOutcome, sideSrc);
    errorNum = errorCheck(decodeOutcome, source);
    printf("errorNum = %d, saveNode = %d\n", errorNum, saveNode);

    free(source);
    source = NULL;
    free(sideSrc);
    sideSrc = NULL;
    int i;
    for(i = 0; i < saveNode; i++)
    {
        free(tree[i].decodeOutcome);
        tree[i].decodeOutcome = NULL;
    }
    free(tree);
    tree = NULL;
    free(encodeOutcome);
    encodeOutcome = NULL;
    return 0;
}
