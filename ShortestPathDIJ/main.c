#include <stdio.h>
#include <stdlib.h>

#define MAX 65535

void Dijkstra(int n, int u, float dist[], int p[], int C[n][n])
{
    int s[n];
    int i = 0;
    for(i = 1; i <= n; i++)
    {
        dist[i] =  C[u][i];
        s[i] = 0;
        if(dist[i] == MAX)
            p[i] = -1;
        else
            p[i] = u;
    }
    dist[u] = 0;
    s[u] = 1;
    for(i = 1; i <= n; i++)
    {
        int temp = MAX;
        int t = u;
        int j = 0;
        for(j = 1; j <=n; j++)
        {
            if(!s[j] && dist[j] < temp)
            {
                t = j;
                temp = dist[j];
            }
        }
        if(t == u) break;
        s[t] = 1;
        for(j = 1; j <= n; j++)
        {
            if(!s[j] && C[t][j] < MAX)
            {
                if(dist[j] > (dist[t] + C[t][j]))
                {
                    dist[j] = dist[t] + C[t][j];
                    p[j] = t;
                }
            }
        }
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int u = 0;
    int **C = (int**)malloc(sizeof(int*));
    int i = 0, j = 0;
    for(i = 0; i < n; i++)
        C[i] = (int)malloc(sizeof(int));
    int weight = 0;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &weight);
            C[i][j] = weight;
        }
    }
    float dist[n];
    int p[n];
    Dijkstra(n, u, dist, p, C);
    for(i = 0; i < n; i++)
    {
        free(C[i]);
        C[i] = NULL;
    }
    free(C);
    C = NULL;
    return 0;
}
