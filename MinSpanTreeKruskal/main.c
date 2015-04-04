#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 7
#define MAX_ARCNUM_NUM ((MAX_VERTEX_NUM) * (MAX_VERTEX_NUM - 1)) / 2
#define INFINITE 32687
#define QUEUE_MAX_SIZE MAX_ARCNUM_NUM

typedef struct
{
    char start;
    char end;
    unsigned int weight;
}edge;

typedef struct
{
    char vertex[MAX_VERTEX_NUM];
    int vexNum, arcNum;
    edge edges[MAX_ARCNUM_NUM];
}adjUDN; //无向网

typedef struct
{
    edge data[QUEUE_MAX_SIZE];
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

void printQueue(pQueue queue)
{
    int i = 0;
    for(i = 0; i < queue.length; i++)
        printf("(%c,%c,%u)", queue.data[i].start, queue.data[i].end, queue.data[i].weight);
    printf("\n");
}

int empty(pQueue queue)
{
    if(!queue.length) return 1;
    else return 0;
}

edge getMax(pQueue queue)
{
    edge temp;
    temp.start = temp.end = temp.weight = 0;
    if(empty(queue)) return temp;
    return queue.data[1];
}

int size(pQueue queue)
{
    return queue.length;
}

void copy(edge *edgeA, const edge *edgeB)
{
    edgeA->start = edgeB->start;
    edgeA->end = edgeB->end;
    edgeA->weight = edgeB->weight;
}

void swap(edge *edgeA, edge *edgeB)
{
    edge temp;
    copy(&temp, edgeA);
    copy(edgeA, edgeB);
    copy(edgeB, &temp);
}

void enQueue(pQueue *queue, edge newData)
{
    if(queue->length == QUEUE_MAX_SIZE) return;
    copy(&queue->data[queue->length], &newData);
    int index = queue->length;
    edge temp;
    temp.start = temp.end = temp.weight = 0;
    while(queue->data[index].weight < queue->data[(index - 1) / 2].weight)
    {
        swap(&queue->data[index], &queue->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
    queue->length++;
}

edge deQueue(pQueue *queue, edge data)
{
    edge temp;
    temp.start = temp.end = temp.weight = 0;
    if(empty(*queue)) return temp;
    copy(&data, &queue->data[0]);
    copy(&queue->data[0], &queue->data[queue->length - 1]);
    queue->length--;

    edge rc;
    copy(&rc, &queue->data[0]);
    int j = 0, s = 0;
    //从完全二叉树的第一个非叶子节点开始向前逐个调整成大顶堆
    for(j = s + 1; j < queue->length; j = 2 * j + 1)
    {
        if(j < queue->length - 1 && queue->data[j].weight > queue->data[j + 1].weight)
            j++;
        if(rc.weight <= queue->data[j].weight)
            break;
        copy(&queue->data[s], &queue->data[j]);
        s = j;
    }
    copy(&queue->data[s], &rc);
    return data;
}

int locateVex(adjUDN udNet, char vex)
{
    int i = 0;
    for(i = 0; i < udNet.vexNum; i++)
        if(udNet.vertex[i] == vex)
            return i;
    return -1;
}

void createAdjUDN(adjUDN *udNet)
{
    //顶点个数及边的个数
    scanf("%d%d", &udNet->vexNum, &udNet->arcNum);
    getchar();
    int i = 0, j = 0, k = 0;
    //顶点信息
    for(i = 0; i < udNet->vexNum; i++)
        scanf("%c", &udNet->vertex[i]);
    getchar();
    //边
    char v1, v2;
    unsigned int weight;
    for(k = 0; k < udNet->arcNum; k++)
    {
        scanf("%c%c%u", &v1, &v2, &weight);
        i = locateVex(*udNet, v1);
        j = locateVex(*udNet, v2);
        if(i == -1 || j == -1) return;
        udNet->edges[k].start = v1;
        udNet->edges[k].end = v2;
        udNet->edges[k].weight = weight;
    }
}

void minSpanTreeKruskal(adjUDN udNet)
{
    pQueue *queue = NULL;
    queue = initQueue(queue);
    int i = 0;
    for(i = 0; i < udNet.arcNum; i++)
        enQueue(queue, udNet.edges[i]);
    edge e;
    int edgesAccepted = 0;
    while(edgesAccepted < udNet.vexNum - 1)
    {
        deQueue(queue, e);
        setType uSet = disjSet.find(e.start);
        setType vSet = disjSet.find(e.end);
        if(uSet != vSet)
        {
            edgesAccepted++;
            disjSet.unionSets(uSet, vSet);
        }
    }
    destroyQueue(queue);
}

/*
6 10
ABCDEF
AB6AC1AD5BC5BE3CD5CE6CF4DF2EF6
*/
int main()
{
    adjUDN udNet;
    adjUDN *p = &udNet;
    createAdjUDN(p);
    pQueue *queue = NULL;
    queue = initQueue(queue);
    int i = 0;
    for(i = 0; i < udNet.arcNum; i++)
        enQueue(queue, udNet.edges[i]);
    printQueue(*queue);
    edge e;
    e = deQueue(queue, e);
    printf("(%c,%c,%u)\n", e.start, e.end, e.weight);
    printQueue(*queue);
    destroyQueue(queue);
    return 0;
}
