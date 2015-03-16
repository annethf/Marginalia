#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

struct stack
{
    int *top;
    int *base;
    int size;
};

typedef struct stack stack;

void initStack(stack *s)
{
    s->base = (int*)malloc(sizeof(int) * STACK_INIT_SIZE);
    s->top = s->base;
    s->size = STACK_INIT_SIZE;
}

void destroyStack(stack *s)
{
    if(!s->base)return;
    free(s->base);
    s->base = NULL;
    s->top = NULL;
    s->size = 0;
}

void clearStack(stack *s)
{
    if(s->top == s->base)return;
    s->top = s->base;
}

int stackEmpty(stack *s)
{
    return (s->top == s->base) ? 1 : 0;
}

int stackLength(stack *s)
{
    return (s->top - s->base);
}

int getTop(stack *s)
{
    if(s->top == s->base) return 0;
    int e = *(s->top - 1);
    return e;
}

void push(stack *s, int elem)
{
    if(s->top - s->base >= s->size)
    {
        s->base = (int*)realloc(s->base, (s->size + STACKINCREMENT) * sizeof(int));
        s->top = s->base + s->size;
    }
    *(s->top++) = elem;
}

void pop(stack *s, int e)
{
    if(s->top == s->base)return;
    e = *(--(s->top));
}

void visit(int e)
{
    printf("%d ", e);
}

void stackTraverse(stack *s, void visit(int e))
{
    int *p = s->base;
    while(s->base < s->top)
        visit(*(s->base++));
    s->base = p;
}

int main()
{
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);
    stackTraverse(s, visit);
    printf("\nstack length = %d\n",stackLength(s));
    int e = getTop(s);
    printf("e = %d\n", e);
    pop(s, e);
    pop(s, e);
    stackTraverse(s, visit);
    printf("\nIs stack empty: %d\n", stackEmpty(s));
    printf("stack length = %d\n",stackLength(s));
    clearStack(s);
    stackTraverse(s, visit);
    printf("Is stack empty: %d\n", stackEmpty(s));
    printf("\nstack length = %d\n",stackLength(s));
    destroyStack(s);
    free(s);
    s = NULL;
    return 0;
}
