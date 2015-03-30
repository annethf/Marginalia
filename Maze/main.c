#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100
#define INCREASE 10

char maze[10][10] = {
    {'#','#','#','#','#','#','#','#','#','#'},
    {'#',' ',' ','#',' ',' ',' ','#',' ','#'},
    {'#',' ',' ','#',' ',' ',' ','#',' ','#'},
    {'#',' ',' ',' ',' ','#','#',' ',' ','#'},
    {'#',' ','#','#','#',' ',' ',' ',' ','#'},
    {'#',' ',' ',' ','#',' ',' ',' ',' ','#'},
    {'#',' ','#',' ',' ',' ','#',' ',' ','#'},
    {'#',' ','#','#','#',' ','#','#',' ','#'},
    {'#','#',' ',' ',' ',' ',' ',' ',' ','#'},
    {'#','#','#','#','#','#','#','#','#','#'}
};

typedef struct
{
    int x;
    int y;
}posType;

typedef struct
{
    posType seat;
    int direct;
    int order;
}sElemType;

typedef struct
{
    sElemType elem;
    sElemType *base, *top;
    int stackSize;
}stack;

void initStack(stack *s)
{
    s->base = (sElemType*)malloc(sizeof(sElemType));
    s->top = s->base;
    s->stackSize = STACK_SIZE;
    s->elem.direct = 0;
    s->elem.order = 0;
    s->elem.seat.x = 0;
    s->elem.seat.y = 0;
}

void destroyStack(stack *s)
{
    s->stackSize = 0;
    s->elem.direct = 0;
    s->elem.order = 0;
    s->elem.seat.x = 0;
    s->elem.seat.y = 0;
    free(s->base);
    s->base = NULL;
    free(s->top);
    s->top = NULL;
}

int stackEmpty(stack *s)
{
    if(s->base == s->top)
        return 1;
    return 0;
}

void push(stack *s, sElemType e)
{
    if(s->top - s->base >= STACK_SIZE)
    {
        s->base = (sElemType*)realloc(s->base, (s->stackSize + INCREASE) * sizeof(sElemType));
        s->top = s->base + s->stackSize;
        s->stackSize += INCREASE;
    }
    *s->top++ = e;
}

void pop(stack *s, sElemType *e)
{
    if(stackEmpty(s)) return;
    *e = *--s->top;
}

int pass(posType pos)
{
    if(maze[pos.x][pos.y] == ' ')
        return 1;
    return 0;
}

void footPrint(posType pos)
{
    maze[pos.x][pos.y] = '1';
}

posType nextPos(posType pos, int direct)
{
    posType next;
    if(direct == 1)
    {
        next.x = pos.x;
        next.y = pos.y + 1;
    }
    else if(direct == 2)
    {
        next.x = pos.x + 1;
        next.y = pos.y;
    }
    else if(direct == 3)
    {
        next.x = pos.x;
        next.y = pos.y - 1;
    }
    else
    {
        next.x = pos.x - 1;
        next.y = pos.y;
    }
    return next;
}

void markPrint(posType pos)
{
    maze[pos.x][pos.y] = '0';
}

int mazePath(char maze[][10], posType start, posType end)
{
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
    posType curPos = start;
    int curStep = 1;
    sElemType e;
    do{
            if(pass(curPos) && maze[curPos.x][curPos.y] != '1')
            {
                footPrint(curPos);
                e.direct = 1;
                e.order = curStep;
                e.seat.x = curPos.x;
                e.seat.y = curPos.y;
                push(s, e);
                if(curPos.x == end.x && curPos.y == end.y)
                    return 1;
                curPos = nextPos(curPos, 1);
                curStep++;
            }
            else
            {
                if(!stackEmpty(s))
                {
                    pop(s, &e);
                    while(e.direct == 4 && !stackEmpty(s))
                    {
                        markPrint(e.seat);
                        pop(s, &e);
                    }
                    if(e.direct < 4)
                    {
                        e.direct++;
                        push(s, e);
                        curPos = nextPos(e.seat, e.direct);
                    }
                }
            }

    }while(!stackEmpty(s));
    free(s);
    s = NULL;
    return 0;
}

void printMaze(char maze[][10])
{
    int i, j;
    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
            printf("%c", maze[i][j]);
        printf("\n");
    }
}

int main()
{
    posType start, end;
    start.x = 1;
    start.y = 1;
    end.x = 5;
    end.y = 8;
    mazePath(maze, start, end);
    printMaze(maze);
    return 0;
}
