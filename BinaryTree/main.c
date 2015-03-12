#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

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

treeNode *parent(treeNode *tree, char e)
{
    return NULL;
}

treeNode *leftChild(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = find(tree, e);
    if(!p) return NULL;
    else return p->leftChild;
}

treeNode *rightChild(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = find(tree, e);
    if(!p) return NULL;
    else return p->rightChild;
}

treeNode *leftSibling(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = parent(tree, e);
    treeNode *q = find(tree, e);
    if(q == p->leftChild || !q) return NULL;
    else return p->leftChild;
}

treeNode *rightSibling(treeNode *tree, char e)
{
    if(!tree) return NULL;
    treeNode *p = parent(tree, e);
    treeNode *q = find(tree, e);
    if(q == p->rightChild || !q) return NULL;
    else return p->rightChild;
}

void insertChild(treeNode *tree, treeNode *p, int flag, treeNode *ntree)
{
}

void deleteChild(treeNode *tree, treeNode *p, int flag)
{
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

void destroyBiTree(treeNode *tree)
{
    if(!tree) return; //µÝ¹é½áÊøÌõ¼þ
    else    //µÝ¹é½áÊøÌõ¼þ²»Âú×ã£¬¼ÌÐøµÝ¹é
    {
        destroyBiTree(tree->leftChild);
        destroyBiTree(tree->rightChild);
        tree->c = ' ';
        free(tree);
        tree = NULL;
    }
}

//²âÊÔÐòÁÐ£ºABC##DE#G##F###
int main()
{
    treeNode *tree = NULL;
    initBiTree(tree);
    tree = createBiTree(tree);
    printf("root = %c\n", root(tree));
    printBiTree(tree);
    printf("\ndepth = %d\n", depthBiTree(tree));
    printf("find = %c\n", find(tree, 'G')->c);
    printf("left child = %c\n", leftChild(tree, 'D')->c);
    printf("preorder:\n");
    preOrderTraverse(tree, visit);
    printf("\ninorder:\n");
    inOrderTraverse(tree, visit);
    printf("\npostorder:\n");
    postOrderTraverse(tree, visit);
    clearBiTree(tree);
    printBiTree(tree);
    destroyBiTree(tree);
    return 0;
}
