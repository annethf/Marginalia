#include <stdio.h>
#include <stdlib.h>

enum pointerTag{link, thread};
typedef enum pointerTag  pTag;

struct thrBiTreeNode
{
    char elem;
    struct thrBiTreeNode *leftChild, *rightChild;
    pTag leftTag, rightTag;
};

typedef struct thrBiTreeNode thrBiTree;

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
        tree->rightTag = thread;
        tree->leftChild = createBiTree(tree->leftChild);
        tree->rightChild = createBiTree(tree->rightChild);
    }
    return tree;
}

void inThreading(thrBiTree *tree, thrBiTree *pre)
{
    if(tree)
    {
        inThreading(tree->leftChild, pre);
        if(!tree->leftChild)
        {
            tree->leftTag = thread;
            tree->leftChild = pre;
        }
        if(!pre->rightChild)
        {
            pre->rightTag = thread;
            pre->rightChild = tree;
        }
        pre = tree;
        inThreading(tree->rightChild, pre);
    }
}

void inOrderThreading(thrBiTree *thrTree, thrBiTree *tree)
{
    //Í·½Úµã
    thrTree = (thrBiTree*)malloc(sizeof(thrBiTree));
    thrTree->leftTag = link;
    thrTree->rightTag = thread;
    thrTree->rightChild = thrTree;
    thrBiTree *pre = NULL;
    if(!tree)
        thrTree->leftChild = thrTree;
    else
    {
        thrTree->leftChild = tree;
        pre = thrTree;
        inThreading(tree, pre);
        pre->rightChild = thrTree;
        pre->rightTag = thread;
        thrTree->rightChild = pre;
    }
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
    thrBiTree *thrTree = NULL;
    tree = createBiTree(tree);
    inOrderThreading(thrTree, tree);
    inOrderTraverseThrBiTree(tree, visit);
    free(thrTree);
    thrTree = NULL;
    //destroyBiTree(tree);
    return 0;
}
