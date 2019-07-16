// investment.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define MAX_N 32 // ���Ͷ����Ŀ��Ŀ 
#define MAX_M 128 // ���Ͷ��Ǯ��(����)

// ��i��Ͷ��j��Ԫ������ 1 <= i <= n, 1 <= j <= m 
int f[MAX_N][MAX_M] = 
{
    {0, 60, 80, 105, 115, 130, 150},
    {0, 65, 85, 110, 140, 160, 175},
    {0, 75, 100, 120, 135, 150, 180}
};

void print_result(int n, int m, int max[][MAX_M])
{
    int invesment[MAX_N] = { 0 };
    
    invesment[n - 1] = max[n - 1][m];
    for (int i = n - 2; i >= 0; --i) 
    {
        int t = 0;
        for (int j = n - 1; j > i; --j) 
        {
            t += invesment[j];
        }
        invesment[i] = max[i][m - t];
    }

    for (int x = 0; x < n; x++)
    {
        printf("Invest %d for project %d\n", invesment[x], x + 1);
    }
}

// n����Ŀ,Ͷ��m����Ԫ 
int investment(int n, int m, int d[][MAX_M], int max[][MAX_M])
{
    //��ʼ����Ҳ����ֻ��һ����Ŀ�������
    for (int x = 0; x <= m; x++)
    {
        d[0][x] = f[0][x];  // Ͷ�ʵ�һ����Ŀ 
        max[0][x] = x; //��Ǻ�����ʼ��
    }
    
    for(int i = 1; i < n; i++) // Ͷ��ǰi����Ŀ 
    { 
        for(int j = 0; j <= m; j++) // ǰ i ����Ŀ��Ͷ���Ǯ�� j 
        { 
            for(int k = 0; k <= j; k++) // Ͷ�ʵ�ǰ��Ŀ��Ǯ������ i ����Ŀ��
            { 
                int tmp = f[i][k] + d[i - 1][j-k]; 
                if(tmp > d[i][j]) //d[i][j]��ʼ������0
                { 
                    d[i][j] = tmp; // ���µ�ǰ�����Ž� 
                    max[i][j] = k; // ���±�Ǻ��� 
                } 
            } 
        } 
    } 

    return d[n - 1][m];
} 

    
int main()
{
    int d[MAX_N][MAX_M] = { { 0 } }; // Ͷ��ǰ i ����Ŀ j ������������
    int max[MAX_N][MAX_M] = { { 0 } }; // Ͷ�ʾ��߱��ֵ

    int benefit = investment(3, 6, d, max);
    printf("Total benefit : %d\n", benefit);
    print_result(3, 6, max); // ��ӡ��� 
    return 0;
}

