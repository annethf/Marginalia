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

void init(treeNode *tree)
{
    tree = NULL;  //¿ÕÊ÷
}

treeNode* createTree(treeNode *tree)
{
    char c;
    scanf("%c", &c);
    if(c == '#') tree = NULL;
    else
    {
        tree = (treeNode *)malloc(sizeof(treeNode));
        tree->c = c;
        tree->leftChild = createTree(tree->leftChild);
        tree->rightChild = createTree(tree->rightChild);
    }
    return tree;
}

void print(treeNode *tree)
{
    if(!tree) return;
    else
    {
        printf("%c ", tree->c);
        print(tree->leftChild);
        print(tree->rightChild);
    }
}

void destroyTree(treeNode *tree)
{
    if(!tree) return; //µÝ¹é½áÊøÌõ¼þ
    else    //µÝ¹é½áÊøÌõ¼þ²»Âú×ã£¬¼ÌÐøµÝ¹é
    {
        destroyTree(tree->leftChild);
        destroyTree(tree->rightChild);
        tree->c = ' ';
        free(tree);
        tree = NULL;
    }
}

int main()
{
    treeNode *tree = NULL;
    init(tree);
    tree = createTree(tree);
    print(tree);
    destroyTree(tree);
    return 0;
}
