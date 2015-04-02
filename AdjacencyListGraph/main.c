#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20

typedef struct arcNode
{
    int adjVex;
    struct arcNode *nextArc;
}arcNode;

typedef struct vexNode
{
    char data;
    int index;
    arcNode *firstArc;
}vexNode;

typedef struct
{
    vexNode adjList[MAX_VERTEX_NUM];
    int vexNum, arcNum;
}adjListGraph;

int locateVex(adjListGraph graph, char data)
{
    int i = 0;
    for(i = 0; i < graph.vexNum; i++)
        if(data == graph.adjList[i].data)
            return i;
    return -1;
}

void destroyALGraph(adjListGraph *graph)
{
    int i = 0;
    arcNode *p = NULL;
    arcNode *q = NULL;
    for(i = 0; i < graph->vexNum; i++)
    {
        p = graph->adjList[i].firstArc;
        if(!p)
        {
            q = p->nextArc;
            free(p);
            p = q;
        }
        graph->adjList[i].firstArc = NULL;
    }
}

void printALGraph(adjListGraph *graph)
{
    int i = 0;
    arcNode *p = NULL;
    printf("邻接表：\n");
    for(i = 0; i < graph->vexNum; i++)
    {
        printf("%2d %2c ", graph->adjList[i].index, graph->adjList[i].data);
        p = graph->adjList[i].firstArc;
        while(p)
        {
            printf("%2d ", p->adjVex);
            p = p->nextArc;
        }
        printf("\n");
    }
}

void createALGraph(adjListGraph *graph)
{
    printf("输入顶点和边的个数：\n");
    scanf("%d%d", &(graph->vexNum), &(graph->arcNum));
    getchar();
    printf("输入顶点:\n");
    int i = 0;
    for(i = 0; i < graph->vexNum; i++)
    {
        scanf("%c", &graph->adjList[i].data);
        graph->adjList[i].index = i;
        graph->adjList[i].firstArc = NULL;
    }
    getchar();
    printf("边信息：\n");
    int j = 0, m = 0, n = 0;
    char dataA, dataB;
    arcNode *p = NULL;
    arcNode *q = NULL;
    for(j = 0; j < graph->arcNum; j++)
    {
        scanf("%c%c", &dataA,&dataB);
        m = locateVex(*graph, dataA);
        n = locateVex(*graph, dataB);
        if(m == -1 || n == -1) return;
        p = (arcNode*)malloc(sizeof(arcNode));
        p->adjVex = n;
        p->nextArc = NULL;
        q = graph->adjList[m].firstArc;
        if(!q)
        {
            graph->adjList[m].firstArc = p;
            q = p;
        }
        else
        {
            while(q->nextArc)
                q = q->nextArc;
            q->nextArc = p;
        }

        p = (arcNode*)malloc(sizeof(arcNode));
        p->adjVex = m;
        p->nextArc = NULL;
        q = graph->adjList[n].firstArc;
        if(!q)
        {
            graph->adjList[n].firstArc = p;
            q = p;
        }
        else
        {
            while(q->nextArc)
                q = q->nextArc;
            q->nextArc = p;
        }
    }
}

/*
5 7
ABCDE
ABAEBCBDBECDDE
*/
int main()
{
    adjListGraph *graph = (adjListGraph*)malloc(sizeof(adjListGraph));
    createALGraph(graph);
    printALGraph(graph);
    destroyALGraph(graph);
    return 0;
}
