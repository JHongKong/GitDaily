#pragma once

#define  STATIONS             6
#define  LINES                2


typedef struct
{
    int a[LINES][STATIONS];
    int t[LINES][STATIONS];
    int e[LINES];
    int x[LINES];
}Program_T;

typedef struct
{
    int line[LINES][STATIONS];  //���������е����ž���
    int ls;
    int f[LINES][STATIONS];  //��ǰ��֪�ľ���״̬
    int fs;   //���Ž��ֵ
}Result_T;



void fast_station_sequence(Program_T *para, Result_T *result);

