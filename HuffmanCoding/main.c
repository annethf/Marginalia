#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

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
        printf("%d      %d\n", queue->data[i].weight,  queue->data[i].index);
    printf("\n");
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
    copy(&data, &(queue->data[0]));
    const int i = queue->length - 1;
    copy(&(queue->data[0]), &(queue->data[i]));
    (queue->length)--;

    huffmanTree *node = (huffmanTree*)malloc(sizeof(huffmanTree));
    copy(node, queue->data);
    int j = 0, s = 0;
    for(j = s + 1; j < queue->length; j = 2 * j + 1)
    {
        if(j < queue->length - 1 && queue->data[j].weight > queue->data[j + 1].weight)
            j++;
        if(node->weight <= queue->data[j].weight)
            break;
        copy(&(queue->data[s]), &(queue->data[j]));
        s = j;
    }
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
        //printQueue(queue);
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
        printf("%3d  %3d  %3d  %3d  %3d\n", p->index, p->weight, p->parent, p->leftChild, p->rightChild);
}

char** huffmanCoding(huffmanTree *hTree, char **hCode, int n)
{
    int i = 0;
    int start = 0;
    int child = 0;
    int parent = 0;
    char *code = (char*)malloc(n * sizeof(char));
    code[n - 1] = '\0';
    for(i = 0; i < n; i++)
    {
        start = n - 1;
        for(child = i, parent = hTree[i].parent; parent != 0; child = parent, parent = hTree[parent].parent)
        {
            if(hTree[parent].leftChild == child)
                code[--start] = '0';
            else
                code[--start] = '1';
        }
        memcpy(hCode[i], &code[start], (n - start) * sizeof(char));
    }
    free(code);
    code = NULL;
    return hCode;
}

void decoding(huffmanTree *hTree, char** hCode, int n, int m)
{
    unsigned int* decode = (unsigned int*)malloc(sizeof(unsigned int) * n);
    unsigned int child = 0;
    int i = 0, j = 0;

    for(i = 0; i < n; i++)
    {
        child = m - 1;
        for(j = 0; j < strlen(hCode[i]); j++ )
        {
            if(hCode[i][j] == '0')
                child = hTree[child].leftChild;
            else
                child = hTree[child].rightChild;
        }
        decode[i] = hTree[child].weight;
    }
    printf(" 解码结果：\n");
    for(i = 0; i < n; i++)
        printf("%4u ", decode[i]);
    printf("\n");
    free(decode);
    decode = NULL;
}

int main()
{
    int n = 8; //叶子节点个数
    int m = 2 * n - 1; //树节点个数
    //权重
    unsigned int *weight = (unsigned int*)malloc(sizeof(unsigned int) * n);
    weight[0] = 5; weight[1] = 29; weight[2] = 7;
    weight[3] = 8; weight[4] = 14; weight[5] = 23;
    weight[6] = 3; weight[7] = 11;
    //Huffman树
    huffmanTree *hTree = (huffmanTree*)malloc(m * sizeof(huffmanTree));
    createHuffmanTree(hTree, weight, n);
    printf(" 哈夫曼树\n");
    printHTree(hTree, m);
    //Huffman编码
    int i = 0, j = 0;
    huffmanTree *p = NULL;
    char **hCode =  (char**)malloc(n * sizeof(char*));
    for(i = 0; i < n; i++)
        hCode[i] = (char*)malloc(n * sizeof(char));
    hCode = huffmanCoding(hTree, hCode, n);
    printf(" 索引  权重 父索引 左孩子 右孩子 编码值\n");
    for(i = 0, p = hTree; i < n; p++, i++)
    {
        printf("%4d  %4d  %4d  %4d  %4d      ", p->index, p->weight, p->parent, p->leftChild, p->rightChild);
        for(j = 0; j < strlen(hCode[i]); j++)
            printf("%c", hCode[i][j]);
        printf("\n");
    }
    decoding(hTree, hCode, n, m);
    free(hTree);
    hTree = NULL;
    free(weight);
    weight = NULL;
    for(i = 0; i < n; i++)
    {
        free(hCode[i]);
        hCode[i] = NULL;
    }
    free(hCode);
    hCode = NULL;
    return 0;
}
