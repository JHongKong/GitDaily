// jitutonglong.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

/*��ͷ�ĸ�������ö�٣�Ȼ����ŵĸ���ȷ���Ƿ��Ƿ��������Ľ�*/
void Jitutonglong(int tou, int jiao)
{
    for (int ji = 0; ji < tou; ji++)
    {
        int tu = tou - ji;
        if ((ji * 2 + tu * 4) == jiao)
        {
            std::cout << "����" << ji << "    "
                      << "�ã�" << tu << std::endl;
        }
    }
}

int main()
{
    //Jitutonglong(50, 120);
    Jitutonglong(35, 94);
    return 0;
}

