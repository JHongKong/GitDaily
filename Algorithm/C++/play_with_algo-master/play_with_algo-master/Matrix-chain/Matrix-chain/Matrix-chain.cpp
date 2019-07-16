// Matrix-chain.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <climits>

const int M = 32;

void matrix_chain_order(int *p, int n, int f[][M], int s[][M])
{
    for (int i = 1; i <= n; i++) /*��ʼ��Ĭ��ֵ*/
    {
        f[i][i] = 0;
    }

    for (int size = 2; size <= n; size++) 	/* �������ĳ��� */
    {
        for (int i = 1; i <= n - size + 1; i++) /*�������������ʼλ��*/
        {
            int j = i + size - 1;         /* ���������������λ�� */
            f[i][j] = INT_MAX;
            for (int k = i; k < j; k++)  /*�ָ��k�ı���*/
            {
                int q = f[i][k] + f[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < f[i][j])
                {
                    f[i][j] = q;
                    s[i][j] = k; //��¼f[i,j]�����ŷָ��λ��
                }
            }
        }
    }
}

void print_optimal_parens(int s[][M], int i, int j)
{
    if (i == j)
    {
        std::cout << "A" << i;
        return;
    }

    int k = s[i][j]; //�����������ѷָ��
    std::cout << "(";
    print_optimal_parens(s, i, k);
    print_optimal_parens(s, k + 1, j);
    std::cout << ")";
}

int main()
{
    int p[M] = { 30,35,15,5,10,20,25 };
    int f[M][M], s[M][M];

    matrix_chain_order(p, 6, f, s);
    std::cout << "The minimal product times:    " << f[1][6] << std::endl;
    std::cout << "Result��   ";
    print_optimal_parens(s, 1, 6);

    return 0;
}

