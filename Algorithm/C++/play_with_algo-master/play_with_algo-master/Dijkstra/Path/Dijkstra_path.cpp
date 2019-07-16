#include "Dijkstra_path.h"


void init_dijkstra(Dijkstra_T *dj, Problem_T *p_data)
{
    //��T��ʼ��Ϊֻ������ʼ��S��״̬����T{ S }
    dj->T[0] = p_data->start_vertex;
    dj->tc = 1;

    //��ʼ��dist�����ֵΪ��ʼ��S������Vx�ıߵ�Ȩ�أ���dist[Vx] = w(S, Vx)
    dj->vertexs = p_data->vertexs;
    for (int i = 0; i < dj->vertexs; i++)
    {
        dj->dist[i].is_in_t = false;
        dj->dist[i].pc = 0;
        dj->dist[i].value = p_data->w[p_data->start_vertex][i];
        if (dj->dist[i].value < INFINITE)
        {
            dj->dist[i].path[0] = p_data->start_vertex;
            dj->dist[i].pc = 1;
        }
    }

    dj->dist[dj->vertexs].is_in_t = true;  //��ʼ���Ѿ���T����
    dj->dist[dj->vertexs].value = 0; //������ʼ��S��������dist[S] = 0��
    dj->dist[dj->vertexs].pc = 0;
}

void dijkstra(Dijkstra_T *dj, Problem_T *p_data)
{
    while (dj->tc < dj->vertexs) //ֱ������T���������ж��㣬��5��������ѭ����ֹ����
    {
        //��3��
        //�������в����ڼ���T�Ķ���Vi����dist������Ѱ����Сֵdist[Vi]
        int min_dist = INFINITE;
        int min_vi = -1;
        for (int i = 0; i < dj->vertexs; i++)
        {
            if (!dj->dist[i].is_in_t && (dj->dist[i].value < min_dist))
            {
                min_dist = dj->dist[i].value;
                min_vi = i;
            }
        }

        //������Vi���뵽����T�У���ɵ�3��
        dj->T[dj->tc] = min_vi; //�¼��붥��min_vi
        dj->tc++;
        dj->dist[min_vi].is_in_t = true;

        //��4��
        //�����¼���Ķ���Vi���鿴Vi�ܹ���������ж���
        for (int j = 0; j < dj->vertexs; j++)
        {
            if (p_data->w[min_vi][j] < INFINITE) //��min_vi��ֱ�ӵ���j
            {
                int new_dist = dj->dist[min_vi].value + p_data->w[min_vi][j];
                //����㵽min_vi����С�������min_vi��j�ľ���֮��С�ڴ����ֱ�ӵ�j�ľ���
                if(new_dist < dj->dist[j].value)
                {
                    //�滻dist�����ж�Ӧ�����ֵ
                    dj->dist[j].value = new_dist;
                    //��min_vi����·����Ϣ
                    for (int k = 0; k < dj->dist[min_vi].pc; k++)
                    {
                        dj->dist[j].path[k] = dj->dist[min_vi].path[k];
                    }
                    dj->dist[j].pc = dj->dist[min_vi].pc;
                    //������·����Ϣ������min_vi��j��һ��
                    dj->dist[j].path[dj->dist[j].pc] = min_vi;
                    dj->dist[j].pc++;
                }
            }
        }
    }

}

