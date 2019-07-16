// hanoi.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

//��һ������from���Ƶ�to�������Ǵ�ӡ�ƶ�����
void move(int from, int to)
{
    std::cout << "move: " << from << " ----> " << to << std::endl;
}

void hanoi(int n, int s1, int s2, int s3)
{
    if (n == 1)
    {
        move(s1, s3);
        return;
    }

    hanoi(n - 1, s1, s3, s2);//����1 �ѵ�1�����������n-1��������3�Ÿ������Ƶ�2��������
    move(s1, s3);             //����2 ��1������ʣ�µģ����ģ�һ�������Ƶ�3��������
    hanoi(n - 1, s2, s1, s3);//����3 ����֮ǰ�Ƶ�2�������ϵ�n-1��������1�������Ƶ�3��������
}

#if 0
void hanoi(int n, int s1, int s2, int s3)
{
    if (n == 1)
    {
        move(s1, s3);
    }
    else
    {
        hanoi(n - 1, s1, s3, s2);//����1 �ѵ�1�����������n-1��������3�Ÿ������Ƶ�2��������
        move(s1, s3);             //����2 ��1������ʣ�µģ����ģ�һ�������Ƶ�3��������
        hanoi(n - 1, s2, s1, s3);//����3 ����֮ǰ�Ƶ�2�������ϵ�n-1��������1�������Ƶ�3��������
    }
}
#endif

int main()
{
    hanoi(3, 1, 2, 3);
    return 0;
}

