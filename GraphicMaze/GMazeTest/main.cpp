#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int parent[170];
int mazeSet[15][15];

void init()
{
    int i, j;
    //ÿ������ĸ��ڵ���Ϊ�����Լ�
    for(int i = 1; i <= 169; ++i)
        parent[i] = -1;
    //����
    for(i = 1; i <= 13; ++i)
        for(j = 1; j <= 13; ++j)
            mazeSet[i][j] = 0;

    for(j = 0; j < 15; j++)
    {
        mazeSet[0][j] = 1;
        mazeSet[14][j] = 1;
    }

    for(i = 1; i <= 13; i++)
    {
        mazeSet[i][0] = 1;
        mazeSet[i][14] = 1;
    }

    for(i = 1; i <= 13; ++i)
    {
        if(i % 2 == 1)
        {
            //�����붥��֮��ı�
            for(j = 2; j <= 12; j += 2)
                mazeSet[i][j] = 1;
        }
        else
        {
            //ǽ��ǽ֮����νӴ�
            for(j = 2; j <= 12; j += 2)
                mazeSet[i][j] = 2;
            //�����붥��֮��ı�
            for(j = 1; j <= 13; j += 2)
                mazeSet[i][j] = 1;
        }
    }
}

int Find(int x)
{
    if(parent[x] < 0)
        return x;
    else
        return parent[x] = Find(parent[x]);
}

void unionSet(int root1, int root2)
{
    if(parent[root1] < parent[root2])
        parent[root1] = root2;
    else
    {
        if(parent[root1] == parent[root2])
            parent[root1]--;
        parent[root2] = root1;
    }
}

int pos(int x, int y)
{
    return (x - 1) * 13 + y;
}

int main()
{
    int x, y, x1, y1, x2, y2;
    init();
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
            cout << mazeSet[i][j] << " ";
        cout << endl;
    }
    srand(time(NULL));
    int t1 = Find(pos(1, 1));
    int t2 = Find(pos(13, 13));
    cout << "t1 = " << t1 << " t2 = " << t2 << endl;
    while(Find(pos(1, 1)) != Find(pos(13, 13)))
    {
        //�������һ����
        do
        {
            x = (rand() % 13) + 1;
            y = (rand() % 13) + 1;
        }while(mazeSet[x][y] != 1);
        int d = x % 2;
        if(d == 1)
        {
            //��
            x1 = x;
            y1 = y + 1;
            x2 = x;
            y2 = y - 1;
            if(Find(pos(x1, y1)) != Find(pos(x2, y2)))
            {
                mazeSet[x][y] = 0;
                unionSet(pos(x1, y1), pos(x2, y2));
            }
        }
        else
        {
            //��
            x1 = x + 1;
            y1 = y;
            x2 = x - 1;
            y2 = y;
            if(Find(pos(x1, y1)) != Find(pos(x2, y2)))
            {
                mazeSet[x][y] = 0;
                unionSet(pos(x1, y1), pos(x2, y2));
            }
        }
    }
//    for(int i = 0; i < 13; ++i)
//    {
//        mazeSet[i][12] = 1;
//        mazeSet[12][i] = 1;
//    }
    cout << "���ɵ��Թ�" << endl;
    for(int i = 0; i < 15; i++)
    {
        for(int j = 0; j < 15; j++)
            cout << mazeSet[i][j] << " ";
        cout << endl;
    }
    return 0;
}
