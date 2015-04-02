#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 20
#define STACK_SIZE 100
#define INCREASE 10

//邻接表表示图
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

void (*visitFunc)(adjListGraph g, int);
int visited[MAX_VERTEX_NUM];
//栈定义
typedef struct
{
    char* base, *top;
    int stackSize;
} stack;
//队列定义
typedef struct qNode
{
    char elem;
    struct qNode *next;
} queue;

//栈操作
void initStack(stack *s)
{
    s->base = (char*)malloc(sizeof(char) * STACK_SIZE);
    s->top = s->base;
    s->stackSize = STACK_SIZE;
}

void destroyStack(stack *s)
{
    free(s->top);
    s->top = NULL;
    free(s->base);
    s->base = NULL;
}

int stackEmpty(stack s)
{
    return (s.base == s.top) ? 1 : 0;
}

void getTop(stack *s, char *elem)
{
    if(s->top == s->base) return;
    *elem = *--s->top;
    s->top++;
}

void push(stack *s, char elem)
{
    if(s->top - s->base >= s->stackSize)
    {
        s->base = (char*)realloc(s->base, sizeof(char) * (s->stackSize + INCREASE));
        s->stackSize += INCREASE;
        s->top = s->base + s->stackSize;
    }
    *s->top++ = elem;
}

void pop(stack *s, char *elem)
{
    if(s->base == s->top) return;
    else
        *elem = *--s->top;
}

//队列操作
queue* initQueue(queue *q)
{
    q = (queue*)malloc(sizeof(queue));
    q->elem = 0;
    q->next = NULL;
    return q;
}

void destroyQueue(queue *q)
{
    queue *p = q;
    while(p->next)
    {
        q = p->next;
        free(p);
        p = q;
    }
    free(p);
    q = p = NULL;
}

int queueEmpty(queue q)
{
    return (!q.next) ? 1 : 0;
}

void enQueue(queue *q, char elem)
{
    queue *node = (queue*)malloc(sizeof(queue));
    node->elem = elem;
    node->next = NULL;
    queue *p = q;
    if(!q->next)
        q->next = node;
    else
    {
        while(p->next)
            p = p->next;
        p->next = node;
    }
}

void deQueue(queue *q, char *elem)
{
    queue *p = q->next;
    q->next = p->next;
    *elem = p->elem;
    free(p);
    p = NULL;
}

//邻接表表示图的操作
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

void visit(adjListGraph g, int v)
{
    printf("%c ", g.adjList[v].data);
}

int firstAdjVex(adjListGraph *g, int v)
{
    arcNode *p = g->adjList[v].firstArc;
    if(p)
        return p->adjVex;
    return -1;
}

int nextAdjVex(adjListGraph *g, int v, int w)
{
    arcNode *p = g->adjList[v].firstArc;
    while(p && p->adjVex <= w)
        p = p->nextArc;
    if(p)
        return p->adjVex;
    return -1;
}

void DFS(adjListGraph *g, int v, void (*visitFunc)(adjListGraph, int))
{
    visited[v] = 1;
    (*visitFunc)(*g, v);
    int w = firstAdjVex(g, v);
    if(w < 0 || w >= g->vexNum) return;
    else
        for(; w >= 0; w = nextAdjVex(g, v, w))
            if(!visited[w])
                DFS(g, w, (*visitFunc));
}

void DFSTraverse(adjListGraph *g)
{
    visitFunc = visit;
    int v = 0;
    for(v = 0; v < g->vexNum; v++)
        visited[v] = 0;
    for(v = 0; v < g->vexNum; v++)
        if(!visited[v])
            DFS(g, v, (*visitFunc));
}

void print(char e)
{
    printf("%c ", e);
}

int findIndex(adjListGraph g, char elem)
{
    int i = 0;
    for(i = 0; i < g.vexNum; i++)
        if(g.adjList[i].data == elem)
            return g.adjList[i].index;
    return -1;
}

void DFSNonRecurTraverse(adjListGraph *g, void (*visitFunc)(char e))
{
    visitFunc = print;
    int v = 0, w = 0;
    char elem = 0;
    for(v = 0; v < g->vexNum; v++)
        visited[v] = 0;
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
    for(v = 0; v < g->vexNum; v++)
    {
        if(!visited[v])
        {
            push(s, g->adjList[v].data);
            (*visitFunc)(g->adjList[v].data);
            visited[v] = 1;
            v = firstAdjVex(g, v);
        }
        while(!stackEmpty(*s))
        {
            if(!visited[v])
            {
                push(s, g->adjList[v].data);
                visited[v] = 1;
                (*print)(g->adjList[v].data);
                v = firstAdjVex(g, v);
            }
            else
            {
                getTop(s, &elem);
                w = findIndex(*g, elem);
                v = nextAdjVex(g, w, v);
            }
            if(v == -1)
            {
                pop(s, &elem);
                w = findIndex(*g, elem);
                v = nextAdjVex(g, w, v);
            }
        }
    }
    destroyStack(s);
    s->stackSize = 0;
    free(s);
    s = NULL;
}

void BFSTraverse(adjListGraph *g, void (*visitFunc)(char e))
{
    visitFunc = print;
    int v = 0, w = 0;
    for(v = 0; v < g->vexNum; v++)
        visited[v] = 0;
    char elem;
    queue *q = NULL;
    q = initQueue(q);
    for(v = 0; v < g->vexNum; v++)
    {
        if(!visited[v])
        {
            (*visitFunc)(g->adjList[v].data);
            visited[v] = 1;
            enQueue(q, g->adjList[v].data);
        }
        while(!queueEmpty(*q))
        {
            deQueue(q, &elem);
            v = findIndex(*g, elem);
            if(v != -1)
            {
                for(w = firstAdjVex(g, v); w >= 0; w = nextAdjVex(g, v, w))
                {
                    if(!visited[w])
                    {
                        visited[w] = 1;
                        (*visitFunc)(g->adjList[w].data);
                        enQueue(q, g->adjList[w].data);
                    }
                }
            }
        }
    }
    destroyQueue(q);
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
    printf("DFS递归遍历：\n");
    DFSTraverse(graph);
    printf("\nDFS非递归遍历：\n");
    DFSNonRecurTraverse(graph, print);
    printf("\nBFS遍历：\n");
    BFSTraverse(graph, print);
    destroyALGraph(graph);
    free(graph);
    graph = NULL;
    return 0;
}
