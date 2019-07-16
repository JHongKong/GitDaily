// blocks.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

const int MAX_SEG = 16;

int color[] = { 0, 1, 2, 3, 1 };
int len[] = { 0, 1, 4, 3, 1 };
int d[MAX_SEG][MAX_SEG][MAX_SEG];


int dp(int i, int j, int k)
{ 
    if (i == j)
    {
        d[i][j][k] = (len[j] + k)*(len[j] + k);
        return d[i][j][k];
    }

    //����¼״̬��ѯ
    if (d[i][j][k] > 0)
    {
        return d[i][j][k];
    }
    
    //��ʱ��ȡ��һ�ַ�ʽ�Ľ����Ϊd[i][j][len]��ֵ
    d[i][j][k] = dp(i, j - 1, 0) + (len[j] + k) * (len[j] + k);
    
    //���յڶ��ַ�ʽ���㣬�������������d[i][j][len]��ֵ
    for (int p = i; p < j; p++)
    {
        if (color[p] == color[j])
        {
            int tmp = dp(i, p, len[j] + k) + dp(p + 1, j - 1, 0);
            if (tmp > d[i][j][k])
            {
                d[i][j][k] = tmp;
            }
        }
    }

    return d[i][j][k]; 
}

int main()
{
    memset(d, 0, sizeof(d));

    int score = dp(1, 4, 0);

    return 0;
}

