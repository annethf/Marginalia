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
    for(i = 0; i < queue->length; i++)
        printf("%d ", queue->data[i]);
    printf("\n");
}

int empty(pQueue queue)
{
    if(!queue.length) return 1;
    else return 0;
}

int getMax(pQueue queue)
{
    if(empty(queue)) return 0;
    return queue.data[1];
}

int size(pQueue queue)
{
    return queue.length;
}

void enQueue(pQueue *queue, int newData)
{
    if(queue->length == QUEUE_MAX_SIZE) return;
    queue->data[queue->length] = newData;
    int index = queue->length;
    int temp = 0;
    while(queue->data[index] < queue->data[(index - 1) / 2])
    {
        temp = queue->data[index];
        queue->data[index] = queue->data[(index - 1) / 2];
        queue->data[(index - 1) / 2] = temp;
        index = (index - 1) / 2;
    }
    (queue->length)++;
}

int deQueue(pQueue *queue, int data)
{
    if(empty(*queue)) return 0;
    data = queue->data[0];
    queue->data[0] = queue->data[queue->length - 1];
    queue->length--;

    int rc = queue->data[0];
    int j = 0, s = 0;
    //从完全二叉树的第一个非叶子节点开始向前逐个调整成大顶堆
    for(j = s + 1; j < queue->length; j = 2 * j + 1)
    {
        if(j < queue->length - 1 && queue->data[j] > queue->data[j + 1])
            j++;
        if(rc <= queue->data[j])
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
    enQueue(queue, 5);
    enQueue(queue, 29);
    enQueue(queue, 7);
    enQueue(queue, 8);
    enQueue(queue, 14);
    enQueue(queue, 23);
    enQueue(queue, 3);
    enQueue(queue, 11);
    printQueue(queue);
    int data = 0;
    data = deQueue(queue, data);
    printf("data = %d\n", data);
    printQueue(queue);
    destroyQueue(queue);
    return 0;
}
