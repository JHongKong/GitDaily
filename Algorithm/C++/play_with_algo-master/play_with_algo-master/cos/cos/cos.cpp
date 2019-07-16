// cos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <cmath>

const int VN = 11;

const char *base_words[] = 
{
    "����", "�ڵ�", "���", "����", "����", "�ھ�", "�Ȼ���", "��׼", "������", "����", "Ŀ��"
};

//�ھ�Ϊ155���׵����ڣ��ڵ�����̳���40����ڵ���������Ŀ��ĵ�����һ��������
//��ھ�������̺�Զ�ҵ����������ڵ�ͨ��������ֱ�Ӷ���Ŀ����׼�����Ǽ���������ߵ�������һ�������Ǻͷ������ڵ�
//���Ǳ���ͳһ�ھ����ֵ����˷���������ڵ��Ľ���
//
double CosSimilarity(double *va, double *vb, int vn)
{
    double cossu = 0.0;
    double cossda = 0.0;
    double cossdb = 0.0;

    for (int i = 0; i < vn; i++)
    {
        cossu += va[i] * vb[i];
        cossda += va[i] * va[i];
        cossdb += vb[i] * vb[i];
    }


    return cossu / (std::sqrt(cossda) * std::sqrt(cossdb));
}

int main()
{
    double v1[] = { 0, 2, 1, 1, 1, 1, 0, 0, 0, 1, 1 };
    double v2[] = { 0, 2, 1, 1, 1, 1, 0, 1, 0, 2, 1 };
    double v3[] = { 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0 };

    double s1 = CosSimilarity(v1, v2, VN);
    double s2 = CosSimilarity(v1, v3, VN);
    double s3 = CosSimilarity(v2, v3, VN);

    return 0;
}

