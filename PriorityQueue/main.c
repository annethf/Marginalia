#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX_SIZE 100

typedef struct
{
    int data[QUEUE_MAX_SIZE];
    int length;
}priorityQueue;

typedef priorityQueue pQueue;

pQueue* initQueue(pQueue *queue)
{
    queue = (pQueue*)malloc(sizeof(pQueue));
    queue->length = 0;
    return queue;
}

void destroyQueue(pQueue *queue)
{
    queue->length = 0;
    free(queue);
    queue = NULL;
}

void printQueue(pQueue *queue)
{
    int i = 0;
    for(i = 1; i <= queue->length; i++)
        printf("%d ", queue->data[i]);
    printf("\n");
}

int empty(pQueue *queue)
{
    if(!queue->length) return 1;
    else return 0;
}

int getMax(pQueue *queue)
{
    if(empty(queue)) return 0;
    return queue->data[1];
}

int size(pQueue *queue)
{
    return queue->length;
}

void enQueue(pQueue *queue, int newData)
{
    if(queue->length == QUEUE_MAX_SIZE) return;
    queue->data[(queue->length) + 1] = newData;
    int index = (queue->length) + 1;
    int temp = 0;
    while(queue->data[index] > queue->data[(queue->length) / 2])
    {
        temp = queue->data[index];
        queue->data[index] = queue->data[(queue->length) / 2];
        queue->data[(queue->length) / 2] = temp;
        index = (queue->length) / 2;
    }
    (queue->length)++;
}

int deQueue(pQueue *queue, int data)
{
    if(empty(queue)) return 0;
    data = queue->data[1];
    queue->data[1] = queue->data[queue->length];
    queue->length--;

    int rc = queue->data[1];
    int j = 0, s = 1;
    //从完全二叉树的第一个非叶子节点开始向前逐个调整成大顶堆
    for(j = 2 * s; j <= queue->length; j *= 2)
    {
        if(j < queue->length && queue->data[j] < queue->data[j + 1])
            j++;
        if(rc >= queue->data[j])
            break;
        queue->data[s] = queue->data[j];
        s = j;
    }
    queue->data[s] = rc;
    return data;
}

int main()
{
    pQueue *queue = NULL;
    queue = initQueue(queue);
    enQueue(queue, 49);
    enQueue(queue, 38);
    enQueue(queue, 65);
    enQueue(queue, 97);
    enQueue(queue, 76);
    enQueue(queue, 13);
    enQueue(queue, 27);
    enQueue(queue, 50);
    enQueue(queue, 40);
    int data = 0;
    data = deQueue(queue, data);
    printf("data = %d\n", data);
    printQueue(queue);
    destroyQueue(queue);
    return 0;
}
