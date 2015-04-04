#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX_NUM 7
#define INFINITE 32687

typedef struct
{
    char vertex[MAX_VERTEX_NUM];
    int matrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int vexNum, arcNum;
}adjUDN; //无向网

typedef struct
{
    char adjVex;
    unsigned int lowcost;
}edge[MAX_VERTEX_NUM];

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
    for(i = 0; i < udNet->vexNum; i++)
        for(j = 0; j < udNet->vexNum; j++)
            udNet->matrix[i][j] = INFINITE;
    //权值
    char v1, v2;
    unsigned int weight;
    for(k = 0; k < udNet->arcNum; k++)
    {
        scanf("%c%c%u", &v1, &v2, &weight);
        i = locateVex(*udNet, v1);
        j = locateVex(*udNet, v2);
        if(i == -1 || j == -1) return;
        udNet->matrix[i][j] = weight;
        udNet->matrix[j][i] = weight;
    }
}

void printAdjUDN(adjUDN udNet)
{
    int i = 0, j = 0;
    for(i = 0; i < udNet.vexNum; i++)
    {
        for(j = 0; j < udNet.vexNum; j++)
            printf("%u  ", udNet.matrix[i][j]);
        printf("\n");
    }
    printf("\n");
}

int minmum(adjUDN udNet, edge closedge)
{
    int i = 0, k = -1;
    unsigned int min = INFINITE;
    for(i = 0; i < udNet.vexNum; i++)
    {
        if(closedge[i].lowcost < min && closedge[i].lowcost != 0)
        {
            k = i;
            min = closedge[i].lowcost;
        }
    }
    return k;
}

void minSpanTreePrim(adjUDN udNet, char vex)
{
    edge closedge;
    int k = locateVex(udNet, vex);
    int i = 0, j = 0;
    for(i = 0; i < udNet.vexNum; i++)
    {
        if(i != k)
        {
            closedge[i].adjVex = vex;
            closedge[i].lowcost = udNet.matrix[k][i];
        }
    }
    closedge[k].lowcost = 0;
    for(j = 1; j < udNet.vexNum; j++)
    {
        k = minmum(udNet, closedge);
        printf("(%c,%c),", closedge[k].adjVex, udNet.vertex[k]);
        closedge[k].lowcost = 0;
        for(i = 0; i < udNet.vexNum; i++)
        {
            if(udNet.matrix[k][i] < closedge[i].lowcost)
            {
                closedge[i].adjVex = udNet.vertex[k];
                closedge[i].lowcost = udNet.matrix[k][i];
            }
        }
    }
}

/*
6 10
ABCDEF
AB6AC1AD5BC5BE3CD5CE6CF4DF2EF6
*/
int main()
{
    adjUDN udNet;
    char v = 'A';
    adjUDN *p = &udNet;
    createAdjUDN(p);
    printAdjUDN(udNet);
    minSpanTreePrim(udNet, v);
    printf("\n");
    return 0;
}
