#pragma once

const int MAX_VERTEX = 10;
const int INFINITE = 108000; //ʮ���ǧ��

typedef struct
{
    int value;     
    bool is_in_t;  
}Dist_T;


typedef struct
{
    int vertexs;  //��Ŀ������ʵ�ʶ������
    int w[MAX_VERTEX][MAX_VERTEX]; //ͼ��Ȩ�ؾ��󣬱�ʾ�����ľ���
    int start_vertex;   //��ʼ����
}Problem_T;

typedef struct
{
    int vertexs;  //��Ŀ������ʵ�ʶ������
    int T[MAX_VERTEX];  //����T
    int tc; //��ǰT�ж������
    Dist_T dist[MAX_VERTEX];  //dist����
}Dijkstra_T;


void init_dijkstra(Dijkstra_T *dj, Problem_T *p_data);
void dijkstra(Dijkstra_T *dj, Problem_T *p_data);
