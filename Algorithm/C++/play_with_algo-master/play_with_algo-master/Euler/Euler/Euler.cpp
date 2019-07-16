// Euler.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_VERTEXNODE = 20;


typedef struct
{
    bool visited;
    std::vector<int> relVertex; //���ڱ߶���
}VERTEX_NODE;

typedef struct
{
    int count; //ͼ�Ķ���ĸ���
    VERTEX_NODE vertexs[MAX_VERTEXNODE]; //ͼ�Ķ����б�
}EU_GRAPH;

void DsfEnumeration(EU_GRAPH& g, int node)
{
    g.vertexs[node].visited = true; //���õ�ǰ��ķ��ʱ�־
    for (int i : g.vertexs[node].relVertex)
    {
        if (!g.vertexs[i].visited) //i��node�����ڵ㣬����iû�б����ʹ�
        {
            DsfEnumeration(g, i);
        }
    }
}

void BsfEnumeration(EU_GRAPH& g, int node)
{
    std::queue<int> q;
    q.push(node); //��ʼλ�������

    while (!q.empty())
    {
        int cur = q.front(); //ȡ����Ԫ�أ������ţ�
        q.pop(); //ɾ������Ԫ��
        g.vertexs[cur].visited = true; //���÷��ʱ�־
        for (int i : g.vertexs[cur].relVertex)
        {
            if (!g.vertexs[i].visited) //i��cur�����ڵ㣬����iû�б����ʹ�
            {
                q.push(i); //û�б����ʹ��Ķ��������
            }
        }

    }
}

bool IsConnected(EU_GRAPH& g)
{
    for (int i = 0; i < g.count; i++)
    {
        if (!g.vertexs[i].visited)
        {
            return false;
        }
    }
    
    return true;
}

bool IsEuler(EU_GRAPH& g)
{
    if (!IsConnected(g))
    {
        return false;
    }

    for (int i = 0; i < g.count; i++)
    {
        int n = g.vertexs[i].relVertex.size();
        if ((n & 1) != 0)
        {
            return false;
        }
    }

    return true;
}


int main()
{
    EU_GRAPH g = {  7,
                   { { false, {3, 4} },
                     { false, {3, 4, 5, 6} },
                     { false, {5, 6} },
                     { false, {0, 1, 2, 5} },
                     { false, {0, 1, 5, 6} },
                     { false, {1, 3, 4, 6} },
                     { false, {1, 2, 4, 5} }
                   }
                 };
    //DsfEnumeration(g, 0);
    BsfEnumeration(g, 0);
    bool isConnected = IsConnected(g);
    bool isEuler = IsEuler(g);

    return 0;
}

