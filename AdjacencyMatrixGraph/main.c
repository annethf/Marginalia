#include <stdio.h>
#include <stdlib.h>

#define VERTEX_NUM 20

#define STACK_SIZE 100
#define INCREASE 10

typedef struct
{
    char vertex[VERTEX_NUM];
    int matrix[VERTEX_NUM][VERTEX_NUM];
    int verNum, arcNum;
} graph;
void (*visitFunc)(graph, int);

typedef struct
{
    char* base, *top;
    int stackSize;
} stack;

typedef struct qNode
{
    char elem;
    struct qNode *next;
} queue;

int visited[VERTEX_NUM];
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

void printMatrix(graph *g)
{
    int i = 0, j = 0;
    for(i = 0; i < g->verNum; i++)
    {
        for(j = 0; j < g->verNum; j++)
            printf("%d ", g->matrix[i][j]);
        printf("\n");
    }
}

void createGraph(graph *g)
{
    printf("输入顶点个数和边数：\n");
    scanf("%d%d", &g->verNum, &g->arcNum);
    int i = 0, j = 0;
    //顶点
    printf("输入顶点信息:\n");
    getchar();
    for(i = 0; i < g->verNum; i++)
        scanf("%c", &g->vertex[i]);
    //无向图的边
    printf("输入边信息：\n");
    FILE *fp = fopen("input.txt","r");
    for(i = 0; i < g->verNum; i++)
        for(j = 0; j < g->verNum; j++)
            fscanf(fp, "%d", &g->matrix[i][j]);
    printMatrix(g);
    fclose(fp);
}

void visit(graph g, int v)
{
    printf("%c ", g.vertex[v]);
}

int firstAdjVex(graph *g, int v)
{
    int i = 0, w = 0;
    for(i = 0; i < g->verNum; i++)
    {
        if(g->matrix[i][v] == 1)
        {
            w = i;
            break;
        }
    }
    return w;
}

int nextAdjVex(graph *g, int v, int w)
{
    int i = 0, result = 0;
    for(i = 0; i < g->verNum; i++)
    {
        if(g->matrix[i][v] == 1 && i > w)
        {
            result = i;
            break;
        }
    }
    return (i == g->verNum) ? -1 : result;
}

void DFS(graph *g, int v, void (*visitFunc)(graph, int))
{
    visited[v] = 1;
    (*visitFunc)(*g, v);
    int w = firstAdjVex(g, v);
    if(w < 0 || w >= g->verNum) return;
    else
    {
        for(; w >= 0; w = nextAdjVex(g, v, w))
        {
            if(!visited[w])
                DFS(g, w, (*visitFunc));
        }
    }
}

void DFSTraverse(graph *g)
{
    visitFunc = visit;
    int v = 0;
    for(v = 0; v < g->verNum; v++)
        visited[v] = 0;
    for(v = 0; v < g->verNum; v++)
        if(!visited[v])
            DFS(g, v, (*visitFunc));
}

void print(char e)
{
    printf("%c ", e);
}

int findIndex(graph g, char elem)
{
    int i = 0, index = 0;
    for(i = 0; i < g.verNum; i++)
    {
        if(g.vertex[i] == elem)
        {
            index = i;
            break;
        }
    }
    return (i == g.verNum) ? -1 : index;
}

void DFSNonRecurTraverse(graph *g, void (*visitFunc)(char e))
{
    visitFunc = print;
    int v = 0, w = 0;
    char elem = 0;
    for(v = 0; v < g->verNum; v++)
        visited[v] = 0;
    stack *s = (stack*)malloc(sizeof(stack));
    initStack(s);
    for(v = 0; v < g->verNum; v++)
    {
        if(!visited[v])
        {
            push(s, g->vertex[v]);
            (*visitFunc)(g->vertex[v]);
            visited[v] = 1;
            v = firstAdjVex(g, v);
        }
        while(!stackEmpty(*s))
        {
            if(!visited[v])
            {
                push(s, g->vertex[v]);
                visited[v] = 1;
                (*print)(g->vertex[v]);
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

void BFSTraverse(graph *g, void (*visitFunc)(char e))
{
    visitFunc = print;
    int v = 0, w = 0;
    for(v = 0; v < g->verNum; v++)
        visited[v] = 0;
    char elem;
    queue *q = NULL;
    q = initQueue(q);
    for(v = 0; v < g->verNum; v++)
    {
        if(!visited[v])
        {
            (*visitFunc)(g->vertex[v]);
            visited[v] = 1;
            enQueue(q, g->vertex[v]);
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
                        (*visitFunc)(g->vertex[w]);
                        enQueue(q, g->vertex[w]);
                    }
                }
            }
        }
    }
    destroyQueue(q);
}

int main()
{
    graph *g = (graph*)malloc(sizeof(graph));
    createGraph(g);
    printf("DFS递归遍历结果：\n");
    DFSTraverse(g);
    printf("\nDFS非递归遍历结果：\n");
    DFSNonRecurTraverse(g, print);
    printf("\nBFS遍历结果：\n");
    BFSTraverse(g, print);
    free(g);
    g = NULL;
    return 0;
}
