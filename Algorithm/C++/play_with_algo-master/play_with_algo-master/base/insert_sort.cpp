#include "stdafx.h"

/*
int ls[9] = { 0, 12, 45, 21, 78, 84, 7, 13, 65};
insert_sort(ls, 8);

int ls2[8] = { 12, 45, 21, 78, 84, 7, 13, 65};
insert_sort2(ls2, 8);

*/

//���ڱ�λ�Ĳ�������ls[0]���ڱ�λ
void insert_sort(int *ls, int n)
{
    for (int i = 2; i <= n; ++i)
    {
        if (ls[i] < ls[i - 1])
        {
            ls[0] = ls[i];//iλ�õ��������ڱ�λ����Ϊiλ�ûᱻ������ƶ����ݲ�������
            int j = i;
            while (ls[j - 1] > ls[0])//�������ж�j�Ƿ�Խ�磬ֱ���жϵ�ǰλ�õ�ֵ�Ƿ�����ڱ�λ
            {
                ls[j] = ls[j - 1];
                j--;
            }
            ls[j] = ls[0];
        }
    }
}

//�����ڱ�λ�Ĳ�������
void insert_sort2(int *ls, int n)
{
    for (int i = 1; i < n; ++i)
    {
        if (ls[i] < ls[i - 1])
        {
            int cur = ls[i];//��Ҫ��ʱ�ռ��iλ�õ�ֵ
            int j = i;
            while ((j > 0) && (ls[j - 1] > cur))//��Ҫ���������ж�j�Ƿ�Խ��
            {
                ls[j] = ls[j - 1];
                j--;
            }
            ls[j] = cur;
        }
    }
}
