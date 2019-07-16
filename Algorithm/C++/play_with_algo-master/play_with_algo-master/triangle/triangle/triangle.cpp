// triangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>   



const int INFINITE = 0x0FFFFFFF;
const int N = 6;     //͹����α���  

typedef struct
{
    int d[N][N];  //d[i][j]��ʾ�����{Vi - Vj}������Ȩֵ
    int k[N][N];  //k[i][j]��¼Vi��Vj���������ʷֵ��м��K
}RESULT;

//͹����ε�Ȩ  
int weight[N][N] = 
{
    { 0,2,2,3,1,4 },
    { 2,0,1,5,2,3 },
    { 2,1,0,2,1,4 },
    { 3,5,2,0,6,2 },
    { 1,2,1,6,0,1 },
    { 4,3,4,2,1,0 }
};

int triangle_weight(int a, int b, int c) //����������Ȩ��
{
    return weight[a][b] + weight[b][c] + weight[c][a];
}

void polygon_triangulation(RESULT *result)
{
    int min_d;

    //��ʼ���߽�ֵ
    for (int m = 1; m < N; m++)
    {
        result->d[m][m] = 0;
    }

    //��ʼ�滮
    for (int r = 2; r < N; r++) //�Ӷ���ι�ģ����
    {
        for (int i = 1; i < N - r + 1; i++) //�Ӷ���α�����ȷ����ʼ��Vi
        {
            int j = i + r - 1;  //ȷ��Vj,r���������ģ
            //������Vi��Vj�ĵ㣨������Vj��, ����СȨ��ֵ�ָ��k��
            min_d = INFINITE; 
            for (int k = i; k < j; k++)
            {
                //���Ƽ���
                result->d[i][j] = result->d[i][k] + result->d[k + 1][j] + triangle_weight(i - 1, k, j);
                if (result->d[i][j] < min_d) 
                {
                    min_d = result->d[i][j];
                    result->k[i][j] = k;  //��������ָ��
                }
            }
            result->d[i][j] = min_d;
        }
    }
}

void trace_result(RESULT *result, int i, int j)
{
    if (i == j)
    {
        return;
    }

    trace_result(result, i, result->k[i][j]);    //���һ���Ӷ���ε��ʷֽ��
    trace_result(result, result->k[i][j] + 1, j);    //�����һ���Ӷ���ε��ʷֽ��
    
    //�����ǰ�����Σ�k[i][j]�Ƕ�̬�滮ȥ���������м�¼�µ������ʷֵ�
    std::cout << "triangle: { V" << i - 1 << " V" << result->k[i][j] << " V" << j << " }" << std::endl;
}



int main()
{
    RESULT result = { 0 };
    polygon_triangulation(&result);
    std::cout << "result: " << result.d[1][N - 1] << std::endl;
    trace_result(&result, 1, N-1);
    return 0;
}
