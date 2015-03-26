#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

//priority queue
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

pQueue* initQueue(pQueue *queue, huffmanTree *hTree)
{
    queue = (pQueue*)malloc(sizeof(pQueue));
    memcpy(queue->data, hTree, sizeof(unsigned int) * 15);
    queue->length = 0;
    return queue;
}

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
    copy(temp, tree1);
    copy(tree1, tree2);
    copy(tree2, temp);
    free(temp);
    temp = NULL;
}

void enQueue(pQueue *queue, huffmanTree newData)
{
    if(queue->length == QUEUE_MAX_SIZE) return;
    queue->data[(queue->length)].weight = newData.weight;
    int index = queue->length;
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
    copy(&(queue->data[0]), &(queue->data[queue->length - 1]));
    queue->length--;

    int rc = queue->data[0].weight;
    int j = 0, s = 0;
    //从完全二叉树的第一个非叶子节点开始向前逐个调整成大顶堆
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
    return data.index;
}
//typedef char** HuffmanCode;
int select(huffmanTree *hTree, int n)
{
    pQueue *queue = NULL;
    queue = initQueue(queue, hTree);
    huffmanTree *p = hTree;
    int i = 0;
    for(i = 0; i <= n; i++)
    {
        enQueue(queue, *p);
        p++;
    }
    huffmanTree data;
    int index = deQueue(queue, data);
    destroyQueue(queue);
    return index;
}

void huffmanCoding(huffmanTree *hTree, unsigned int *weight, int n)
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
    for(; i < m; i++)
    {
        p->weight = 0;
        p->parent = 0;
        p->leftChild = 0;
        p->rightChild = 0;
        p->index = i;
    }
    //创建Huffman树
    int s1, s2;
    for(i = n; i < m; i++)
    {
        s1 = select(hTree, i - 1);
        s2 = select(hTree, i - 2);
        printf("s1 = %d, s2 = %d\n", s1, s2);
        hTree[s1].parent = i;
        hTree[s2].parent = i;
        //新结点
        hTree[i].weight = hTree[s1].weight + hTree[s2].weight;
        hTree[i].parent = 0;
        hTree[i].leftChild = s1;
        hTree[i].rightChild = s2;
    }
    for(p = hTree, i = 0; i < m; p++, i++)
        printf("%d ", p->weight);
    printf("\n");
}

int main()
{
    int n = 8;
    int m = 2 * n - 1;
    huffmanTree *tree = (huffmanTree*)malloc(m * sizeof(huffmanTree));
    unsigned int *weight = (unsigned int*)malloc(sizeof(unsigned int) * n);
    weight[0] = 5;
    weight[1] = 29;
    weight[2] = 7;
    weight[3] = 8;
    weight[4] = 14;
    weight[5] = 23;
    weight[6] = 3;
    weight[7] = 11;
    huffmanCoding(tree, weight, n);
    free(tree);
    tree = NULL;
    free(weight);
    weight = NULL;
    return 0;
}
