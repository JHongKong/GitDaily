// buychick.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

void Buy()
{
    int count = 0;

    for (int roosters = 0; roosters <= 20; roosters++)   //ö�ٴ󹫼�����
    {
        for (int hens = 0; hens <= 33; hens++) //ö��ĸ������
        {
            int chicks = 100 - roosters - hens;  //ʣ�µľ���С������
            if (((chicks % 3) == 0) //С������Ӧ����3�������������Ǹ�СС�ļ�֦
                && ((5 * roosters + 3 * hens + chicks / 3) == 100)) //�Ƿ�չ�100��Ǯ
            {
                count++;
                std::cout << "�� " << count << "������ " << roosters
                                              << ", ĸ�� " << hens
                                              << ", С�� " << chicks << std::endl;
            }
        }
    }

    std::cout << "���� " << count << " ����" << std::endl;
}

int main()
{
    Buy();
    return 0;
}

