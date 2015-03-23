#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

enum pointerTag{link, thread};
typedef enum pointerTag  pTag;

struct thrBiTreeNode
{
    char elem;
    struct thrBiTreeNode *leftChild, *rightChild;
    pTag leftTag, rightTag;
};
typedef struct thrBiTreeNode thrBiTree;

struct stack
{
    thrBiTree *top;
    thrBiTree *base;
    int size;
};
typedef struct stack stack;

void initStack(stack *s)
{
    s->base = (thrBiTree*)malloc(sizeof(thrBiTree) * STACK_INIT_SIZE);
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

int stackEmpty(stack *s)
{
    return (s->top == s->base) ? 1 : 0;
}

int stackLength(stack *s)
{
    return (s->top - s->base);
}

char getTop(stack *s, thrBiTree *node)
{
    if(s->top == s->base) return 0;
    node = s->top - 1;
    return node->elem;
}

void push(stack *s, thrBiTree node)
{
    if(s->top - s->base >= s->size)
    {
        s->base = (thrBiTree*)realloc(s->base, (s->size + STACKINCREMENT) * sizeof(thrBiTree));
        s->top = s->base + s->size;
    }
    *s->top++ = node;
}

thrBiTree* pop(stack *s, thrBiTree *node)
{
    if(s->top == s->base)return NULL;
    node = --s->top;
    return node;
}

thrBiTree* createBiTree(thrBiTree *tree)
{
    char e;
    scanf("%c",&e);
    if(e == '#') tree = NULL;
    else
    {
        tree = (thrBiTree*)malloc(sizeof(thrBiTree));
        tree->elem = e;
        tree->leftTag = link;
        tree->rightTag = link;
        tree->leftChild = createBiTree(tree->leftChild);
        tree->rightChild = createBiTree(tree->rightChild);
    }
    return tree;
}

void inOrderThreading(thrBiTree *thrTree, thrBiTree *tree)
{
    //Í·½Úµã
    thrTree->leftTag = link;
    thrTree->rightTag = thread;
    thrTree->rightChild = thrTree;

    thrBiTree *pre = NULL;
    thrBiTree *p = tree;
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
    if(!tree)
        thrTree->leftChild = thrTree;
    else
    {
        thrTree->leftChild = tree;
        pre = thrTree;
        while(p || !stackEmpty(s))
        {
            if(p)
            {
                push(s, *p);
                p = p->leftChild;
            }
            else
            {
                p = pop(s, p);
                if(!p->leftChild)
                {
                    p->leftTag = thread;
                    p->leftChild = pre;
                }
                if(!pre->rightChild)
                {
                    pre->rightTag = thread;
                    pre->rightChild = p;
                }
                pre = p;
                p = p->rightChild;
            }
        }
        pre->rightChild = thrTree;
        pre->rightTag = thread;
        thrTree->rightChild = pre;
    }
    destroyStack(s);
    free(s);
    s = NULL;
}

void visit(char e)
{
    printf("%c ", e);
}

void inOrderTraverseThrBiTree(thrBiTree *tree, void visit(char e))
{
    thrBiTree *p = tree->leftChild;
    while(p != tree)
    {
        while(p->leftTag == link)
            p = p->leftChild;
        visit(p->elem);
        while(p->rightTag == thread && p->rightChild != tree)
        {
            p = p->rightChild;
            visit(p->elem);
        }
        p = p->rightChild;
    }
}

int main()
{
    thrBiTree *tree = NULL;
    tree = createBiTree(tree);
    thrBiTree *thrTree = (thrBiTree*)malloc(sizeof(thrBiTree));
    inOrderThreading(thrTree, tree);
    //inOrderTraverseThrBiTree(tree, visit);
    free(thrTree);
    thrTree = NULL;
    //destroyBiTree(tree);
    return 0;
}
