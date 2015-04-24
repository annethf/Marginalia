#ifndef _HEADER_
#define _HEADER_

#define BIT 16
#define MAX (1 << BIT)
#define TOP_VALUE (MAX - 1)
#define FIRST_QUATER (MAX >> 2)

#define FHIGH(bond)             ((bond) & (MAX >> 1))
#define SHIGH(bond)             ((bond) & (MAX >> 2))
#define PUTBIT(buf, i, bit)     (buf[(i) >> 5] |= ((bit) << ((i) & 31)))
#define GETBIT(buf, i)          ((buf[(i) >> 5] >> ((i) & 31)) & 1)
#define ENTROPY(p)              (((-p) * (log2(p))) - (1 - (p)) * (log2(1 - (p))))

unsigned high;
unsigned low;
unsigned srcSymbolNum;
float pr;

#endif // _HEADER_

