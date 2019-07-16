// MondriaanDream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

const int MAX_STATE = 32;  //2^N
const int MAX_M = 1000 + 2;  //M
const int MAX_N = 8;  //M

int bitMask[MAX_N] = {0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020, 0x00000040, 0x00000080};
#if 0
void dfs(int N, long long d[][MAX_STATE], int i, int j, int state, int next)
{
    if (j == N)
    {
        d[i + 1][next] += d[i][state];
        return;
    }
    //������λ���Ѿ�����һ����ռ��,ֱ������
    if ((bitMask[j] & state) > 0)
        dfs(N, d, i, j + 1, state, next);
    //������λ���ǿյģ����Է�һ��1*2��
    if ((bitMask[j] & state) == 0)
        dfs(N, d, i, j + 1, state, next | bitMask[j]);
    //������λ���Լ���һ��λ�ö��ǿյģ����Է�һ��2*1��
    if (j + 1 < N && (bitMask[j] & state) == 0 && (bitMask[j + 1] & state) == 0)
        dfs(N, d, i, j + 2, state, next);
}

long long MondriaanDream(int N, int M)
{
    long long d[MAX_M][MAX_STATE];
    
    memset(d, 0, sizeof(d));
    d[1][0] = 1;

    int totalState = (1 << N);
    for (int i = 1; i <= M; i++)
    {
        for (int state = 0; state < totalState; state++)
        {
            if (d[i][state] > 0)
            {
                dfs(N, d, i, 0, state, 0);
            }
        }
    }
    
    return d[M + 1][0];
}
#endif

void update(long long d[][MAX_STATE], int N, int cur, int a, int b)//a�ǰ���mλ1����������״̬��b�ǰ���m+1λ1����������״̬
{
    
    if (b & bitMask[N])
    {
        d[cur][b ^ bitMask[N]] += d[1 - cur][a];//ֻ������������λΪ1ʱ�Ÿ���
    }
}

long long MondriaanDream2(int N, int M)
{
    long long d[MAX_M][MAX_STATE];

    memset(d, 0, sizeof(d));

    int totalState = (1 << N);
    int cur = 0;
    d[cur][totalState - 1] = 1;
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cur ^= 1;
            memset(d[cur], 0, sizeof(d[cur]));
            for (int k = 0; k < totalState; k++)//k�Ķ�������ʽ��ʾǰһ�����ӵ�������״̬
            {
                update(d, N, cur, k, k << 1);//��ǰ�񲻷ţ�ֱ��k����һλ�ͱ�ʾ��m+1λ���������ߵ�״̬
                if (i && !(k&bitMask[N - 1])) update(d, N, cur, k, (k << 1) ^ bitMask[N] ^ 1);//�Ϸţ�Ҫ����������Ϊ0
                if (j && (!(k & 1))) update(d, N, cur, k, (k << 1) ^ 3);//��ţ�Ҫ��������β0����1
            }
        }
    }
    return d[cur][(1 << N) - 1];
}

//i���ڼ��У�j���ڼ��У� prev��i-1�е�״̬��state ��i�е�״̬
void state_dfs(int n, long long d[][MAX_STATE], int i, int j, int prev, int state)
{ 
    if (j == n) //j==n��ʾ�Ѿ�Խ���ˣ�����Ҫ�����ݹ���
    {
        d[i][state] += d[i - 1][prev]; //ǰi-1�е�prev״̬�����仯���ܹ����i�е�state״̬
        return;
    }

    //������λ���Ѿ�����һ����ռ��,ֱ������
    if ((bitMask[j] & state) > 0)
    {
        state_dfs(n, d, i, j + 1, prev, state);
    }
    //������λ���ǿյģ����Է�һ��1 x 2�ģ����ţ�
    if ((bitMask[j] & state) == 0)
    {
        state_dfs(n, d, i, j + 1, prev, state);
    }
    //������λ���Լ���һ��λ�ö��ǿյģ����Է�һ��2*1��
    if ((j < n - 1) && !(state & bitMask[j]) && !(state&bitMask[j + 1]))
    {
        state_dfs(n, d, i, j + 2, prev, state | bitMask[j] | bitMask[j + 1]);
    }
}

long long MondriaanDream(int n, int m)
{
    long long d[MAX_M][MAX_STATE];

    memset(d, 0, sizeof(d));

    int finalState = (1 << n) - 1;
   
    d[0][finalState] = 1;
    for (int i = 1; i <= m; ++i)
    {
        for (int state = 0; state < (1 << n); ++state)
        {
            if (d[i - 1][state] > 0)
            {
                state_dfs(n, d, i, 0, state, ~state & finalState);
            }
        }
    }
    return d[m][finalState];
}


int main()
{
    long long count = MondriaanDream(4, 11);
    count = MondriaanDream2(4, 11);

    count = MondriaanDream(2, 11);
    count = MondriaanDream2(2, 11);


    count = MondriaanDream(4, 2);
    count = MondriaanDream2(4, 2);

    std::cout << count << std::endl;
}

/*
1 2
1 3
1 4
2 2
2 3
2 4
2 11
4 11
0 0

Sample Output

1
0
1
2
3
5
144
51205
*/