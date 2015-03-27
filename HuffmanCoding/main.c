#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define QUEUE_MAX_SIZE 100

struct HTNode
{
    unsigned int weight;
    unsigned int parent, leftChild, rightChild;
    int index;
};
typedef struct HTNode huffmanTree;

typedef struct
{
    huffmanTree data[QUEUE_MAX_SIZE];
    int length;
}priorityQueue;

typedef priorityQueue pQueue;

void destroyQueue(pQueue *queue)
{
    queue->length = 0;
    free(queue);
    queue = NULL;
}

int empty(pQueue queue)
{
    if(!queue.length) return 1;
    else return 0;
}

void copy(huffmanTree *tree1, huffmanTree *tree2)
{
    tree1->weight = tree2->weight;
    tree1->parent = tree2->parent;
    tree1->leftChild = tree2->leftChild;
    tree1->rightChild = tree2->rightChild;
    tree1->index = tree2->index;
}

void swap(huffmanTree *tree1, huffmanTree *tree2)
{
    huffmanTree *temp = (huffmanTree*)malloc(sizeof(huffmanTree));
    memset(temp, 0, sizeof(huffmanTree));
    copy(temp, tree1);
    copy(tree1, tree2);
    copy(tree2, temp);
    free(temp);
    temp = NULL;
}

void printQueue(pQueue *queue)
{
    int i = 0;
    for(i = 0; i < queue->length; i++)
        printf("%d      %d\n", queue->data[i].weight, queue->data[i].index);
}

void enQueue(pQueue *queue, huffmanTree newData)
{
    if(queue->length == QUEUE_MAX_SIZE) return;
    int index = queue->length;
    copy(&(queue->data[index]), &newData);
    while((queue->data[index]).weight < (queue->data[(index - 1) / 2]).weight)
    {
        swap(&(queue->data[index]), &(queue->data[(index - 1) / 2]));
        index = (index - 1) / 2;
    }
    (queue->length)++;
}

int deQueue(pQueue *queue, huffmanTree data)
{
    if(empty(*queue)) return 0;
    data.index = queue->data[0].index;
    const int i = queue->length - 1;
    copy(&(queue->data[0]), &(queue->data[i]));
    (queue->length)--;

    huffmanTree *node = (huffmanTree*)malloc(sizeof(huffmanTree));
    copy(node, queue->data);
    int rc = node->weight;
    int j = 0, s = 0;
    for(j = s + 1; j < queue->length; j = 2 * j + 1)
    {
        if(j < queue->length - 1 && queue->data[j].weight > queue->data[j + 1].weight)
            j++;
        if(rc <= queue->data[j].weight)
            break;
        copy(&(queue->data[s]), &(queue->data[j]));
        s = j;
    }
    queue->data[s].weight = rc;
    copy(&(queue->data[s]), node);
    free(node);
    node = NULL;
    return data.index;
}

void createHuffmanTree(huffmanTree *hTree, unsigned int *weight, int n)
{
    if(n <= 1) return;
    int m = 2 * n - 1;
    huffmanTree *p = NULL;
    int i = 0;
    //n个叶子结点
    for(p = hTree, i = 0; i < n; i++, p++, weight++)
    {
        p->weight = *weight;
        p->parent = 0;
        p->leftChild = 0;
        p->rightChild = 0;
        p->index = i;
    }
    //m - n + 1个空白结点
    for(; i < m; p++, i++)
    {
        p->weight = 0;
        p->parent = 0;
        p->leftChild = 0;
        p->rightChild = 0;
        p->index = i;
    }
    //创建Huffman树
    pQueue *queue = NULL;
    queue = (pQueue*)malloc(sizeof(pQueue));
    memcpy(queue->data, hTree, sizeof(huffmanTree) * 15);
    queue->length = 0;
    p = hTree;
    for(i = 0; i < n; p++, i++)
        enQueue(queue, *p);

    huffmanTree data;
    int s1, s2;
    for(i = n; i < m; i++)
    {
        s1 = deQueue(queue, data);
        s2 = deQueue(queue, data);
        hTree[s1].parent = i;
        hTree[s2].parent = i;
        //新结点
        hTree[i].weight = hTree[s1].weight + hTree[s2].weight;
        hTree[i].parent = 0;
        hTree[i].leftChild = s1;
        hTree[i].rightChild = s2;
        enQueue(queue, hTree[i]);
    }
    destroyQueue(queue);
}

void printHTree(huffmanTree *hTree, int m)
{
    huffmanTree *p = NULL;
    int i = 0;
    for(p = hTree, i = 0; i < m; p++, i++)
        printf("%d ", p->weight);
    printf("\n");
}

int main()
{
    int n = 8;
    int m = 2 * n - 1;
    huffmanTree *hTree = (huffmanTree*)malloc(m * sizeof(huffmanTree));
    unsigned int *weight = (unsigned int*)malloc(sizeof(unsigned int) * n);
    weight[0] = 5; weight[1] = 29; weight[2] = 7;
    weight[3] = 8; weight[4] = 14; weight[5] = 23;
    weight[6] = 3; weight[7] = 11;
    createHuffmanTree(hTree, weight, n);
    printHTree(hTree, m);
    free(hTree);
    hTree = NULL;
    free(weight);
    weight = NULL;
    return 0;
}
