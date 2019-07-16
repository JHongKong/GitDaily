// Topological.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <queue>
#include <iostream>

const int MAX_VERTEXNODE = 20;

typedef struct 
{
    char *name;   //�����
    int days;     //��ɻ����ʱ��
    int sTime;    //����翪ʼʱ��
    int inDeg;  //���ǰ���ڵ����(���)
    std::vector<int> adjNode; //���ڻ�б�(�ڵ�����)
}VERTEX_NODE;

typedef struct 
{
    int count; //ͼ�Ķ������
    VERTEX_NODE vertexs[MAX_VERTEXNODE]; //ͼ�Ķ����б�
}TP_GRAPH;

TP_GRAPH graph =
{
    9,
    {
        { "P1", 8, 0, 0,{ 2, 6 } },
        { "P2", 5, 0, 0,{ 2, 4 } },
        { "P3", 6, 8, 2,{ 3 } },
        { "P4", 4, 14,2,{ 5, 8 } },
        { "P5", 7, 5, 1,{ 3, 5 } },
        { "P6", 7, 18, 2,{} },
        { "P7", 4, 8, 1,{ 7 } },
        { "P8", 3, 12, 1,{ 8 } },
        { "P9", 4, 18, 2,{} }
    }
};

struct QUEUE_ITEM
{
    int node;
    int sTime;
    bool operator < (const QUEUE_ITEM &a) const
    {
        return sTime > a.sTime;//��Сֵ����     
    }
};

void EnQueue(std::priority_queue<QUEUE_ITEM>& q, int node, int sTime)
{
    QUEUE_ITEM item = { node, sTime };
    q.push(item);
}

int DeQueue(std::priority_queue<QUEUE_ITEM>& q)
{
    int node = q.top().node;
    q.pop();
    return node;
}

bool TopologicalSorting(TP_GRAPH *g, std::vector<int>& sortedNode)
{
    std::priority_queue<QUEUE_ITEM> nodeQueue;

    //��һ�����������Ϊ0�Ķ�����ӣ�ջ��
    for (int i = 0; i < g->count; i++)
    {
        if (g->vertexs[i].inDeg == 0)
        {
            EnQueue(nodeQueue, i, g->vertexs[i].sTime);
        }
    }
    //�ڶ��������У�ջ����Ԫ�ش���
    while (nodeQueue.size() != 0)
    {
        int node = DeQueue(nodeQueue); //���տ�ʼʱ�����ȼ����ӣ�ջ��
        sortedNode.push_back(node);  //�����ǰ�ڵ㣬����˳������sortedNode������
        
        //�����ڵ�node�������ڽӵ㣬����ʾ�����inDegֵ��1
        for (int adjNode : g->vertexs[node].adjNode)
        {
            g->vertexs[adjNode].inDeg--;
            //���inDegֵΪ0����ýڵ�����У�ջ��
            if (g->vertexs[adjNode].inDeg == 0)
            {
                EnQueue(nodeQueue, adjNode, g->vertexs[adjNode].sTime);
            }
        }
    }

    return (sortedNode.size() == g->count);
}

void PrintSorting(TP_GRAPH *g, const std::vector<int>& sortedNode)
{
    for (int node : sortedNode)
    {
        std::cout << g->vertexs[node].name << std::endl;
    }
}

int main(int argc, char* argv[])
{
    std::vector<int> sortedNode;
    if (!TopologicalSorting(&graph, sortedNode))
    {
        std::cout << "Graph has circle!" << std::endl;
        return -1;
    }
    PrintSorting(&graph, sortedNode);
    return 0;
}

