#include <stdio.h>
#include <stdlib.h>
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

struct treeNode
{
    char c;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
};
typedef struct treeNode treeNode;

struct stack
{
    treeNode *top;
    treeNode *base;
    int size;
};
typedef struct stack stack;

struct queueNode
{
    char elem;
    struct queueNode *next;
};
typedef struct queueNode qNode;
//队列
qNode *initQueue(qNode *queue)
{
    if(!queue)
    {
        queue = (qNode*)malloc(sizeof(qNode));
        queue->elem = 0;
        queue->next = NULL;
    }
    return queue;
}

void destroyQueue(qNode *queue)
{
    qNode *p = queue;
    while(p->next)
    {
        queue = p->next;
        p->elem = 0;
        free(p);
        p = queue;
    }
    free(queue);
    queue = NULL;
}

int queueEmpty(qNode *queue)
{
    if(!queue->next) return 1;
    else return 0;
}

char getHead(qNode *queue, char e)
{
    if(!queue->next) return 0;
    e = queue->next->elem;
    return e;
}

void enQueue(qNode *queue, char e)
{
    qNode *p = queue;
    qNode *q = (qNode*)malloc(sizeof(qNode));
    q->elem = e;
    q->next = NULL;
    if(!p->next)
        p->next = q;
    else
    {
        while(p->next)
            p = p->next;
        p->next = q;
    }
}

int deQueue(qNode *queue, char e)
{
    qNode *p = queue;
    if(!p->next) return 0;
    qNode *q = p->next;
    e = q->elem;
    p->next = q->next;
    free(q);
    q = NULL;
    return 1;
}
//栈
void initStack(stack *s)
{
    s->base = (treeNode*)malloc(sizeof(treeNode) * STACK_INIT_SIZE);
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

char getTop(stack *s, treeNode *node)
{
    if(s->top == s->base) return 0;
    node = s->top - 1;
    return node->c;
}

void push(stack *s, treeNode node)
{
    if(s->top - s->base >= s->size)
    {
        s->base = (treeNode*)realloc(s->base, (s->size + STACKINCREMENT) * sizeof(treeNode));
        s->top = s->base + s->size;
    }
    *s->top++ = node;
}

treeNode* pop(stack *s, treeNode *node)
{
    if(s->top == s->base)return NULL;
    node = --s->top;
    return node;
}

void visit(char e)
{
    printf("%c ", e);
}

void initBiTree(treeNode *tree)
{
    tree = NULL;
}

treeNode* createBiTree(treeNode *tree)
{
    char c;
    scanf("%c", &c);
    if(c == '#') tree = NULL;
    else
    {
        tree = (treeNode *)malloc(sizeof(treeNode));
        tree->c = c;
        tree->leftChild = createBiTree(tree->leftChild);
        tree->rightChild = createBiTree(tree->rightChild);
    }
    return tree;
}

void destroyBiTree(treeNode *tree)
{
    if(!tree) return;
    else
    {
        destroyBiTree(tree->leftChild);
        destroyBiTree(tree->rightChild);
        tree->c = ' ';
        free(tree);
        tree = NULL;
    }
}
//递归遍历
void preOrderTraverse(treeNode *tree, void visit(char e))
{
    if(!tree) return;
    visit(tree->c);
    preOrderTraverse(tree->leftChild, visit);
    preOrderTraverse(tree->rightChild, visit);
}

void inOrderTraverse(treeNode *tree, void visit(char e))
{
    if(!tree) return;
    inOrderTraverse(tree->leftChild, visit);
    visit(tree->c);
    inOrderTraverse(tree->rightChild, visit);
}

void postOrderTraverse(treeNode *tree, void visit(char e))
{
    if(!tree) return;
    postOrderTraverse(tree->leftChild, visit);
    postOrderTraverse(tree->rightChild, visit);
    visit(tree->c);
}
//非递归遍历
void preOrderNonRcursionTraverse(treeNode *tree, void visit(char e))
{
    if(!tree) return;
    treeNode *p = tree;
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
    while(p || !stackEmpty(s))
    {
        if(p)
        {
             push(s, *p);
             visit(p->c);
             p = p->leftChild;
        }
        else
        {
            p = pop(s, p);
            p = p->rightChild;
        }
    }
    printf("\n");
    destroyStack(s);
    free(s);
    s = NULL;
}

void inOrderNonRcursionTraverse(treeNode *tree, void vist(char e))
{
    if(!tree) return;
    treeNode *p = tree;
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
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
            visit(p->c);
            p = p->rightChild;
        }
    }
    printf("\n");
    destroyStack(s);
    free(s);
    s = NULL;
}

void postOrderNonRcursionTraverse(treeNode *tree, void visit(char e))
{
    if(!tree) return;
    treeNode *p = tree;
    treeNode *q = NULL;
    stack *s1 = (stack*)malloc(sizeof(stack));
    stack *s2 = (stack*)malloc(sizeof(stack));
    initStack(s1);
    initStack(s2);
    while(p || !stackEmpty(s1))
    {
        if(p)
        {
            push(s1, *p);
            push(s2, *p);
            p = p->rightChild;
        }
        else
        {
            p = pop(s1, p);
            p = p->leftChild;
        }
    }
    while(!stackEmpty(s2))
    {
        q = pop(s2, q);
        visit(q->c);
    }
    printf("\n");
    destroyStack(s1);
    free(s1);
    s1 = NULL;
    destroyStack(s2);
    free(s2);
    s2 = NULL;
}

treeNode *find(treeNode *tree, char e)
{
    treeNode *p = NULL;
    if(!tree) return NULL;
    else if(tree->c == e) return tree;
    else
    {
        p = find(tree->leftChild, e);
        if(p) return p;
        else return find(tree->rightChild, e);
    }
}
//层序遍历
void levelOrderTraverse(treeNode *tree, void visit(char e))
{
    treeNode *p = tree;
    char e = 0;
    qNode *queue = NULL;
    queue = initQueue(queue);
    enQueue(queue, p->c);
    while(!queueEmpty(queue))
    {
        e = getHead(queue, e);
        visit(e);
        deQueue(queue, e);
        if(p->leftChild)
            enQueue(queue, p->leftChild->c);
        if(p->rightChild)
            enQueue(queue, p->rightChild->c);
        p = find(tree, getHead(queue, e));
    }
    destroyQueue(queue);
}
//测试序列：ABC##DE#G##F###
int main()
{
    treeNode *tree = NULL;
    initBiTree(tree);
    tree = createBiTree(tree);
    //递归遍历
    printf("递归遍历:\n");
    printf("先序:");
    preOrderTraverse(tree, visit);
    printf("\n");
    printf("中序:");
    inOrderTraverse(tree, visit);
    printf("\n");
    printf("后序");
    postOrderTraverse(tree, visit);
    printf("\n");
    //非递归遍历
    printf("非递归遍历:\n");
    printf("先序:");
    preOrderNonRcursionTraverse(tree, visit);
    printf("中序:");
    inOrderNonRcursionTraverse(tree, visit);
    printf("后序:");
    postOrderNonRcursionTraverse(tree, visit);
    printf("层序:");
    levelOrderTraverse(tree, visit);
    printf("\n");
    destroyBiTree(tree);
    return 0;
}
