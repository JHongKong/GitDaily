// pnn.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <utility>

//std::string::value_type
void Swap(std::string& chList, int pos1, int pos2)
{
    if (pos1 != pos2)
    {
        auto tmp = chList[pos1]; 
        chList[pos1] = chList[pos2];
        chList[pos2] = tmp;
    }
}

//���ַ���[begin, end]������Ӵ�ȫ����
void Permutation(std::string& chList, int begin, int end)
{
    if (begin == end)
    {
        std::cout << chList << std::endl;
    }

    for (int i = begin; i <= end; i++)
    {
        Swap(chList, begin, i); //�ѵ�i���ַ�����beginλ�ã���begin+1λ�ÿ����µ��Ӵ�
        Permutation(chList, begin + 1, end); //���������
        Swap(chList, begin, i); //������
    }
}

int main()
{
    std::string cl = "abc";
    //std::string cl = "abcd";

    Permutation(cl, 0, cl.length() - 1);

    return 0;
}

