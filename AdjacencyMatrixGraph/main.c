#include <stdio.h>
#include <stdlib.h>

#define VERTEX_NUM 20
#define INFINTE  32768
int visited[VERTEX_NUM];

typedef struct
{
    char vertex[VERTEX_NUM];
    int matrix[VERTEX_NUM][VERTEX_NUM];
    int verNum, arcNum;
}graph;
void (*visitFunc)(graph, int);

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
    printf("���붥������ͱ�����\n");
    scanf("%d%d", &g->verNum, &g->arcNum);
    int i = 0, j = 0;
    //����
    printf("���붥����Ϣ:\n");
    getchar();
    for(i = 0; i < g->verNum; i++)
        scanf("%c", &g->vertex[i]);
    //����ͼ�ı�
    printf("�������Ϣ��\n");
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
    return (i == g->verNum) ? (v + 1) : result;
}

void DFS(graph *g, int v, void (*visitFunc)(graph, int))
{
    visited[v] = 1;
    (*visitFunc)(*g, v);
    int w = 0;
    for(w = firstAdjVex(g, v); w >= 0; w = nextAdjVex(g, v, w))
    {
        if(w >= g->verNum) break;
        if(!visited[w])
            DFS(g, w, (*visitFunc));
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

int main()
{
    graph *g = (graph*)malloc(sizeof(graph));
    createGraph(g);
    DFSTraverse(g);
    free(g);
    g = NULL;
    return 0;
}
