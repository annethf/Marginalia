#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct queueNode
{
    char elem;
    struct queueNode *next;
};
typedef struct queueNode qNode;

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

struct treeNode
{
    char c;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
};

typedef struct treeNode treeNode;

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
    if(!tree) return; //递归结束条件
    else    //递归结束条件不满足，继续递归
    {
        destroyBiTree(tree->leftChild);
        destroyBiTree(tree->rightChild);
        tree->c = ' ';
        free(tree);
        tree = NULL;
    }
}

void clearBiTree(treeNode *tree)
{
    if(!tree) return;
    else
    {
        clearBiTree(tree->leftChild);
        clearBiTree(tree->rightChild);
        tree->c = ' ';
    }
}

int emptyBiTree(treeNode *tree)
{
    if(!tree) return 1;
    else return 0;
}

int depthBiTree(treeNode *tree)
{
    int leftDepth = 0;
    int rightDepth = 0;

    if(!tree) return 0;
    else
    {
        leftDepth = depthBiTree(tree->leftChild);
        rightDepth = depthBiTree(tree->rightChild);
    }
    int depth = leftDepth > rightDepth ? leftDepth + 1 : rightDepth + 1;
    return depth;
}

char root(treeNode *tree)
{
    return tree->c;
}

char value(treeNode *tree, char e)
{
    if(!tree) return ' ';
    else
        return e;
}

void assign(treeNode *tree, treeNode *node, char value)
{
    if(!tree) return;
    else
        node->c = value;
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

treeNode *parents(treeNode *tree, char e)
{
    if(!tree || e == tree->c) return NULL;
    treeNode *p = tree;
    char elem = 0;
    qNode *queue = NULL;
    queue = initQueue(queue);
    enQueue(queue, p->c);
    while(!queueEmpty(queue))
    {
        deQueue(queue, elem);
        if(p->leftChild)
        {
            if(p->leftChild->c != e)
                enQueue(queue, p->leftChild->c);
            else break;
        }
        if(p->rightChild)
        {
            if(p->rightChild->c != e)
                enQueue(queue, p->rightChild->c);
            else break;
        }
        p = find(tree, getHead(queue, elem));
    }
    destroyQueue(queue);
    return p;
}

treeNode *leftChilds(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = find(tree, e);
    if(!p) return NULL;
    else return p->leftChild;
}

treeNode *rightChilds(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = find(tree, e);
    if(!p) return NULL;
    else return p->rightChild;
}

treeNode *leftSiblings(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = parents(tree, e);
    if(!p) return NULL;
    treeNode *q = find(tree, e);
    if(q == p->leftChild || !q) return NULL;
    else return p->leftChild;
}

treeNode *rightSiblings(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = parents(tree, e);
    if(!p) return NULL;
    treeNode *q = find(tree, e);
    if(q == p->rightChild || !q) return NULL;
    else return p->rightChild;
}

void insertChild(treeNode *tree, treeNode *p, int flag, treeNode *c)
{
    if(!tree || !c) return;
    if(c->rightChild) return; //没有判断tree和c是否相交
    if(!flag)
    {
        c->rightChild = p->leftChild;
        p->leftChild = c;
    }
    else
    {
        c->rightChild = p->rightChild;
        p->rightChild = c;
    }
}

void deleteChild(treeNode *tree, treeNode *p, int flag)
{
    if(!tree) return;
    treeNode *q = NULL;
    if(!flag)
    {
        q = p->leftChild;
        if(q)
            destroyBiTree(q);
    }
    else
    {
        q = p->rightChild;
        if(q)
            destroyBiTree(q);
    }
}

void visit(char e)
{
    printf("%c ", e);
}

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

void printBiTree(treeNode *tree)
{
    if(!tree) return;
    else
    {
        printf("%c ", tree->c);
        printBiTree(tree->leftChild);
        printBiTree(tree->rightChild);
    }
}

//测试序列：ABC##DE#G##F###
int main()
{
    treeNode *tree = NULL;
    initBiTree(tree);
    tree = createBiTree(tree);
    printBiTree(tree);
    printf("root = %c\n", root(tree));
    printBiTree(tree);
    printf("\ndepth = %d\n", depthBiTree(tree));
    printf("find = %c\n", find(tree, 'G')->c);
    treeNode *parent = parents(tree, 'D');
    if(parent)
        printf("parent = %c\n", parent->c);
    treeNode *leftChild = leftChilds(tree, 'D');
    if(leftChild)
        printf("left child = %c\n", leftChild->c);
    treeNode *rightChild = rightChilds(tree, 'D');
    if(rightChild)
        printf("right child = %c\n", rightChild->c);
    treeNode *leftSibling = leftSiblings(tree, 'A');
    if(leftSibling)
        printf("leftSibling = %c\n", leftSibling->c);
    treeNode *rightSibling = rightSiblings(tree, 'A');
    if(rightSibling)
        printf("rightSibling = %c\n", rightSibling->c);
    printf("preorder:\n");
    preOrderTraverse(tree, visit);
    printf("\ninorder:\n");
    inOrderTraverse(tree, visit);
    printf("\npostorder:\n");
    postOrderTraverse(tree, visit);
    printf("\nlevelorder:\n");
    levelOrderTraverse(tree, visit);
    printf("\n");
    //没有其他作用，只用来吃掉上一次输入结束时的回车换行符，
    //用char类型的数据也可以，只是如果这里temp是char类型的，那么
    //回车符就保存在了temp中；如果temp是非char类型的，那么回车符并不
    //会存入temp中，而是在异常的字符输入后，被自动清除了
    int temp = 0;
    scanf("%d",&temp);
    treeNode *c = NULL;
    initBiTree(c);
    c = createBiTree(c);
    printBiTree(c);
    treeNode *p = find(tree, 'D');
    insertChild(tree, p, 0, c);
    printf("\nlevelorder:\n");
    levelOrderTraverse(tree, visit);
    insertChild(tree, p, 1, c);
    printf("\nlevelorder:\n");
    levelOrderTraverse(tree, visit);
//    deleteChild(tree, p, 0);
//    printf("\nlevelorder:\n");
//    levelOrderTraverse(tree, visit);
    clearBiTree(tree);
    printBiTree(tree);
    destroyBiTree(tree);
    return 0;
}
