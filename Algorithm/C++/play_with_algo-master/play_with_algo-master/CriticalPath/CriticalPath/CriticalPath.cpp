// CriticalPath.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <queue>

const int MAX_VERTEXNODE = 20;

typedef struct 
{
    int endVertex;    //����յ�Ķ�������
    std::string name;   //��ߵ�����
    int duty;           //��ߵ�ʱ�䣨Ȩ�أ�
}EDGE_NODE;

typedef struct 
{
    int sTime;    //�¼����緢��ʱ��
    int eTime;    //�¼�������ʱ��
    int inDeg;  //���ǰ���ڵ����
    std::vector<EDGE_NODE> edges; //���ڱ߱�
}VERTEX_NODE;

typedef struct 
{
    int count; //ͼ�Ķ���ĸ���
    VERTEX_NODE vertexs[MAX_VERTEXNODE]; //ͼ�Ķ����б�
}CS_GRAPH;


void InitGraph(CS_GRAPH *g, int vertex)
{
    g->count = vertex;
    for (int i = 0; i < vertex; i++)
    {
        g->vertexs[i].sTime = 0;
        g->vertexs[i].eTime = 0x7FFFFFFF;
        g->vertexs[i].inDeg = 0;
    }
}

bool AddGraphEdge(CS_GRAPH *g, const char*name, int u, int v, int weight)
{
    if ((u >= g->count) || (v >= g->count))
    {
        return false;
    }
    EDGE_NODE edge = { v, name, weight };

    g->vertexs[u].edges.push_back(edge);
    g->vertexs[v].inDeg++;

    return true;
}

bool TopologicalSorting(CS_GRAPH *g, std::vector<int>& sortedNode)
{
    std::priority_queue<int> nodeQueue;

    for (int i = 0; i < g->count; i++)
    {
        if (g->vertexs[i].inDeg == 0)
        {
            nodeQueue.push(i);
        }
    }

    while (nodeQueue.size() != 0)
    {
        int u = nodeQueue.top();
        nodeQueue.pop();
        sortedNode.push_back(u);
        for (EDGE_NODE& edge : g->vertexs[u].edges)
        {
            int v = edge.endVertex;
            g->vertexs[v].inDeg--;
            if (g->vertexs[v].inDeg == 0)
            {
                nodeQueue.push(v);
            }
        }
    }

    return (sortedNode.size() == g->count);
}

void CalcESTime(CS_GRAPH *g, const std::vector<int>& sortedNode)
{
    g->vertexs[0].sTime = 0; //est[0] = 0

    for (int u : sortedNode)
    {
        //����u���������������
        for (EDGE_NODE& edge : g->vertexs[u].edges)
        {
            int v = edge.endVertex;  //��������ģ�͵Ķ��壬u��edge�ߵ���㣬v��edge�ߵ��յ�
            int uvst = g->vertexs[u].sTime + edge.duty;
            if (uvst > g->vertexs[v].sTime) //ȡ�����Ǹ�ʱ��
            {
                g->vertexs[v].sTime = uvst;
            }
        }
    }
}

void CalcLSTime(CS_GRAPH *g, const std::vector<int>& sortedNode)
{
    //���һ���ڵ������ʼʱ��������翪ʼʱ��
    g->vertexs[g->count - 1].eTime = g->vertexs[g->count - 1].sTime;

    std::vector<int>::const_reverse_iterator cit = sortedNode.rbegin();
    for (; cit != sortedNode.rend(); ++cit)
    {
        int u = *cit;
        //����u���������������
        for (EDGE_NODE& edge : g->vertexs[u].edges)
        {
            int v = edge.endVertex; //��������ģ�͵Ķ��壬u��edge�ߵ���㣬v��edge�ߵ��յ�
            int uvet = g->vertexs[v].eTime - edge.duty;
            if (uvet < g->vertexs[u].eTime)   //ȡ��С���Ǹ�ʱ��
            {
                g->vertexs[u].eTime = uvet;
            }
        }
    }
}

void PrintSorting(CS_GRAPH *g, const std::vector<int>& sortedNode)
{
    std::vector<int>::const_iterator cit = sortedNode.begin();
    for (; cit != sortedNode.end(); ++cit)
    {
        std::cout << "e" << *cit << std::endl;
    }
}

bool CriticalPath(CS_GRAPH *g)
{
    std::vector<int> sortedNode;
    if (!TopologicalSorting(g, sortedNode)) //����1
    {
        return false;
    }
    CalcESTime(g, sortedNode); //����2
    CalcLSTime(g, sortedNode); //����4

    //����4������ؼ�·���ϵĻ����
    for (int u : sortedNode)
    {
        for (EDGE_NODE& edge : g->vertexs[u].edges)
        {
            int v = edge.endVertex;
            //�Ƿ��ǹؼ����
            if (g->vertexs[u].sTime == g->vertexs[v].eTime - edge.duty)
            {
                if (!edge.name.empty())//���������¼������������
                {
                    std::cout << edge.name << std::endl;
                }
            }
        }
    }

    return true;
}

int main(int argc, char* argv[])
{

    CS_GRAPH graph;
    InitGraph(&graph, 10);
    AddGraphEdge(&graph, "P1", 0, 1, 8);
    AddGraphEdge(&graph, "P2", 0, 2, 5);
    AddGraphEdge(&graph, "", 1, 3, 0);
    AddGraphEdge(&graph, "", 2, 3, 0);
    AddGraphEdge(&graph, "P7", 1, 6, 4);
    AddGraphEdge(&graph, "P5", 2, 5, 7);
    AddGraphEdge(&graph, "P3", 3, 4, 6);
    AddGraphEdge(&graph, "P4", 4, 8, 4);
    AddGraphEdge(&graph, "P8", 6, 7, 3);
    AddGraphEdge(&graph, "", 8, 7, 0);
    AddGraphEdge(&graph, "", 8, 5, 0);
    AddGraphEdge(&graph, "P9", 7, 9, 4);
    AddGraphEdge(&graph, "P6", 5, 9, 7);

    CriticalPath(&graph);
    return 0;
}

