#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <memory.h>
#include <math.h>
#include "header.h"

extern unsigned srcSymbolNum;
extern float k;
extern float p1;
extern float p0;

float q = 0.05;
int pathNum = 2048;
int saveNode;

unsigned *genSideSrc(unsigned *src)
{
    unsigned *sideSrc = (unsigned*)malloc(sizeof(unsigned)*((srcSymbolNum>>5)+1));
    memset(sideSrc,0,((srcSymbolNum >> 5) + 1) * sizeof(unsigned));
    byte bit;
    unsigned i;
    for(i = 0; i < srcSymbolNum; i++)
    {
        bit = GETBIT(src,i);
        bit ^= (rand()<RAND_MAX*q);
        PUTBIT(sideSrc,i,bit);
    }
    return sideSrc;
}

void init(Node *tree, unsigned *encodeOutcome)
{
    tree[0].low = 0;
    tree[0].high = TOP_VALUE;
    tree[0].value = 0;
    tree[0].metric = 0.0;
    tree[0].decounter = 0;
    unsigned i;
    for(i = 0; i < BIT; i++)
    {
        tree[0].value |= GETBIT(encodeOutcome, i);
        tree[0].decounter++;
    }
    tree[0].decodeOutcome = (unsigned*)malloc(sizeof(unsigned)*((srcSymbolNum>>5)+1));
    memset(tree[0].decodeOutcome,0,sizeof(unsigned)*((srcSymbolNum>>5)+1));

    for(i = 1; i < pathNum; i++)
        tree[i].decodeOutcome = NULL;
}

byte getSymbol(Node *node)
{
    unsigned range = node->high - node->low+1;
    if((node->value - node->low) < (unsigned)(range*(1-p1)+0.5)) return 0;
    else if((node->value - node->low) >= ((unsigned)(range*p0+0.5)-1)) return 1;
    else return 'e';
}

void updateValue(Node *node, byte bit, unsigned *encodeOutcome)
{
    unsigned range = node->high-node->low+1;
    if(bit) node->low += (unsigned)(range*(1-p1)+ 0.5);
    else  node->high = node->low+(unsigned)(range*p0+0.5)- 1;

    while(1)
    {
        if(!(FHIGH(node->low) ^ FHIGH(node->high)));
        else if(SHIGH(node->low)&&(!SHIGH(node->high)))
        {
            node->high -= FIRST_QUATER;
            node->low -= FIRST_QUATER;
            node->value -= FIRST_QUATER;
        }
        else break;

        node->low <<= 1;
        node->low &= TOP_VALUE;
        node->high <<= 1;
        node->high |= 1;
        node->high &= TOP_VALUE;
        node->value <<= 1;
        node->value |= GETBIT(encodeOutcome, node->decounter);
        node->decounter++;
    }
}

int compare(const void *a,const void *b)
{
    Node *A = (Node*)a;
    Node *B = (Node*)b;
    if(A->metric > B->metric)       return -1;
    else if(A->metric < B->metric)  return 1;
    else                            return 0;
}

unsigned *decode(Node *tree, unsigned *encodeOutcome, unsigned *sideSrc)
{
    p1 = powf(0.50, k);
    p0 = powf(0.50, k);
    saveNode = 1;
    int saveTemp = 0;

    init(tree, encodeOutcome);

    byte tempSymbol = 0;
    unsigned i;
    int j, n;

    for(i = 0; i < srcSymbolNum; i++)
    {
        saveTemp = saveNode;
        for(j = 0; j < saveNode; j++)
        {
            tempSymbol = getSymbol(&tree[j]);
            if(tempSymbol == 'e')
            {
                if(!tree[saveTemp].decodeOutcome)
                {
                    tree[saveTemp].decodeOutcome = (unsigned*)malloc(sizeof(unsigned)*((srcSymbolNum>>5)+1));
                    memset(tree[saveTemp].decodeOutcome,0,((srcSymbolNum>>5)+1)*sizeof(unsigned));
                }
                tree[saveTemp].decounter = tree[j].decounter;
                tree[saveTemp].high = tree[j].high;
                tree[saveTemp].low = tree[j].low;
                tree[saveTemp].value = tree[j].value;
                tree[saveTemp].metric = tree[j].metric;
                memcpy(tree[saveTemp].decodeOutcome,tree[j].decodeOutcome,((srcSymbolNum>>5)+1)*sizeof(unsigned));
                PUTBIT(tree[j].decodeOutcome,i,GETBIT(sideSrc,i));
                tree[j].metric += log(1-q);
                PUTBIT(tree[saveTemp].decodeOutcome,i,!GETBIT(sideSrc,i));
                tree[saveTemp].metric += log(q);
                saveTemp++;
            }
            else
            {
                PUTBIT(tree[j].decodeOutcome,i,tempSymbol);
                if(tempSymbol == GETBIT(sideSrc,i))
                    tree[j].metric += log(q);
                else
                    tree[j].metric += log(1-q);
            }
        }
        saveNode = saveTemp;
        if((i < srcSymbolNum)&&(saveNode >= (pathNum/2)))
        {
            qsort(tree,saveNode,sizeof(Node),compare);
            saveNode = pathNum >> 1;
        }
        for(n = 0; n < saveNode; n++)
            updateValue(&tree[n],GETBIT(tree[n].decodeOutcome,i),encodeOutcome);
    }
    qsort(tree,saveNode,sizeof(Node),compare);
    return tree[0].decodeOutcome;
}
