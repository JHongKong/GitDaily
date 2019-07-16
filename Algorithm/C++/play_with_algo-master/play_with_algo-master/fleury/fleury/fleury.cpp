// fleury.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_VERTEXNODE = 16;



typedef struct
{
    int vertexs;
    int edges; //ͼ�ı���
    int edge[MAX_VERTEXNODE][MAX_VERTEXNODE]; //�ڽӾ���
}FE_GRAPH;


void DeleteEdge(FE_GRAPH& g, int u, int v)
{
    g.edge[u][v] = 0;
    g.edge[v][u] = 0;
}

void AddEdge(FE_GRAPH& g, int u, int v)
{
    g.edge[u][v] = 1;
    g.edge[v][u] = 1;
}

void fleury(FE_GRAPH& g, std::queue<int>& s, int cur, int start)
{
    bool flag = false;  //�Ƿ�����cur�����ı�
    s.push(cur);
    for (int i = start; i < g.vertexs; i++)
    {
        if (g.edge[cur][i] == 1)
        {
            flag = true;
            DeleteEdge(g, cur, i);
            fleury(g, s, i, 0);
            break;
        }
    }

    //û�ж����뵱ǰ�ڵ�cur����
    if (!flag)
    {
        s.pop(); //���������ջ���Ǹ�����
        int m = s.front();
        AddEdge(g, cur, m);  //û�ж����뵱ǰ����������˵��֮ǰɾ�������ţ��Ȼָ�������
        int new_start = cur + 1;
        if (s.size() == g.edges)
        { 
            s.push(cur);
        }
        else
        {
            s.pop();
            fleury(g, s, m, new_start);
        }
    }
}

int main()
{
    FE_GRAPH g = { 7, 12,
                    { { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 1, 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
                    }
                };

    std::queue<int> s;

    fleury(g, s, 0, 1);

    return 0;
}

