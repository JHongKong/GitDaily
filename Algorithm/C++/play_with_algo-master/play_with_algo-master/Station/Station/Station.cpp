// Station.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>



#define  STATIONS         6
#define  LINES                2


typedef struct 
{
    int assemble_time[LINES][STATIONS];
    int transport_time[LINES][STATIONS];
    int enter_time[LINES];
    int exit_time[LINES];
}Program_T;

typedef struct
{
    int line[STATIONS];  //���������еĵ�ǰ�����¼
    int fs;
    int fline[STATIONS];  //��ǰ��֪�����Ž��
    int ffs;
}Result_T;

void search_stations_sequence(Result_T *rt, Program_T *para, int line, int station)
{
    if (station == (STATIONS - 1)) //1. ���װ�䣬����һ�ν�����˳���ǰ�ݹ��ӽṹ
    {
        rt->fs += para->assemble_time[line][station];
        rt->fs += para->exit_time[line];
        rt->line[station] = line;
        if (rt->fs < rt->ffs) /*��ǰ��ٵ���·��ʱ�俪����С*/
        {
            rt->ffs = rt->fs;
            memmove(rt->fline, rt->line, STATIONS * sizeof(int));
        }
        return;
    }

    //2. ��¼�м�����line������
    int curCost = rt->fs + para->assemble_time[line][station];
    rt->line[station] = line;

    //3. ����line��station��������ɵݹ��ӽṹ�Ķ���
    /*ѡ��װ���ߵ���һ��װ��վ���������Բ���*/
    rt->fs = curCost;
    search_stations_sequence(rt, para, line, station + 1);

    /*ѡ����һ��װ���ߵ���һ��װ��վ����Ҫ����ת�ƿ���*/
    rt->fs = curCost;
    rt->fs += para->transport_time[line][station + 1];
    int nextline = (line + 1) % LINES;
    search_stations_sequence(rt, para, nextline, station + 1);
}

void init_result(Result_T *rt)
{
    for (int i = 0; i < STATIONS; i++)
    {
        rt->line[i] = 0;
        rt->fline[i] = 0;
    }

    rt->fs = 0;
    rt->ffs = 0x0FFFFFFF;
}

void print_result(Result_T *rt)
{
    std::cout << "Total Time " << rt->ffs << std::endl;
    for (int i = 0; i < STATIONS; i++)
    {
        std::cout << "Station " << i + 1 << " on Line " << rt->fline[i] + 1 << std::endl;
    }
}


//��������
Program_T pd = 
{
    { //a
        { 7, 9, 3, 4, 8, 4 },
        { 8, 5, 6, 4, 5, 7 }
    },
    { //t
        { 0, 2, 3, 1, 3, 4 },
        { 0, 2, 1, 2, 2, 1 }
    },
    { 2, 4 }, //e
    { 3, 2 } //x
};

int main()
{

    Result_T result;

    init_result(&result);

    result.fs = pd.enter_time[0];  //װ����1�Ľ��뿪��
    search_stations_sequence(&result, &pd, 0, 0); //�ӵ�һ��װ���߿�ʼ
    result.fs = pd.enter_time[1];  //װ����2�Ľ��뿪��
    search_stations_sequence(&result, &pd, 1, 0); //�ӵڶ���װ���߿�ʼ

    print_result(&result);

    return 0;
}

