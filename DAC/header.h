#ifndef _HEADER_H_INCLUDE_
#define _HEADER_H_INCLUDE_

#define BIT (16)
#define MAX (1 << BIT)
#define TOP_VALUE (MAX - 1)
#define FIRST_QUATER (MAX >> 2)
#define FHIGH(bond) ((bond) & (MAX >> 1))
#define SHIGH(bond) ((bond) & (MAX >> 2))
#define PUTBIT(buf, i, bit) ((buf[(i) >> 5]) |= ((bit) << ((i) & 31)))
#define GETBIT(buf, i) ((buf[(i) >> 5] >> ((i) & 31)) & 1)
typedef unsigned char byte;

struct Node
{
    unsigned low;
    unsigned high;
    unsigned value;
    unsigned decounter;
    float metric;
    unsigned *decodeOutcome;
};
typedef struct Node Node;

#endif // _HEADER_H_INCLUDE_
