// cal24.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <utility>

typedef struct
{
    double num;
    std::string num_str;
}Number;


std::function<bool (const Number&, const Number&, Number&)> acops[] = 
{
    [](const Number& d1, const Number& d2, Number& dr) 
    { 
        dr.num = d1.num + d2.num; 
        dr.num_str = '(' + d1.num_str + '+' + d2.num_str + ')';
        return true; 
    },
    [](const Number& d1, const Number& d2, Number& dr) 
    { 
        dr.num = d1.num - d2.num;
        dr.num_str = '(' + d1.num_str + '-' + d2.num_str + ')';
        return true;
    },
    [](const Number& d1, const Number& d2, Number& dr) 
    {
        dr.num = d1.num * d2.num;
        dr.num_str = '(' + d1.num_str + '*' + d2.num_str + ')';
        return true;
    },
    [](const Number& d1, const Number& d2, Number& dr) 
    {
        if (d2.num == 0)
            return false;
        dr.num = d1.num / d2.num;
        dr.num_str = '(' + d1.num_str + '/' + d2.num_str + ')';
        return true;
    }
};

void Calc24(const std::vector<Number>& nums)
{
    std::size_t count = nums.size();
    if (count == 1) //��ֻ��һ����ʱ��˵��������ɣ������жϽ����
    {
        if (nums[0].num == 24)
        {
            std::cout << nums[0].num_str << " = " << nums[0].num << std::endl;
        }
        return;
    }

    //����ѭ������numbers���������������
    for (std::size_t i = 0; i < count; i++)
    {
        for (std::size_t j = 0; j < count; j++)
        {
            if (i == j) //�ų���ͬ�����
                continue;

            for (auto& op : acops) //�������������ö��
            {
                Number new_num;
                //�������ʧ�ܣ����������0����������ټ������������������൱�ڼ�֦Ч��
                if (op(nums[i], nums[j], new_num))
                {
                    std::vector<Number> sub_nums;//����������
                    sub_nums.push_back(new_num);
                    //���˱�ѡ����������������ʣ�µ�������������
                    for (std::size_t k = 0; k < count; k++) 
                    {
                        if ((k != i) && (k != j))
                        {
                            sub_nums.push_back(nums[k]);
                        }
                    }
                    Calc24(sub_nums); //���������
                }
            }
        }
    }
}

int main()
{
    std::vector<Number> numbers = { { 3, "3" },{ 3, "3" },{ 7, "7" },{ 7, "7" } };
    //std::vector<Number> numbers = { { 1, "1" },{ 5, "5" },{ 5, "5" },{ 5, "5" } };
    //std::vector<Number> numbers = { { 1, "1" },{ 6, "6" },{ 8, "8" },{ 9, "9" } };
    //std::vector<Number> numbers = { { 2, "2" },{ 7, "7" },{ 6, "6" },{ 3, "3" } };

    Calc24(numbers);

    return 0;
}


std::vector<std::pair<int, int>> posArray = 
{
    { 0, 1 }, { 0, 2 }, { 0, 3 }, 
    { 1, 0 }, { 1, 2 }, { 1, 3 }, 
    { 2, 0 }, { 2, 1 }, { 2, 3 }, 
    { 3, 0 }, { 3, 1 }, { 3, 2 }
};

void sdsfdgdfh()
{
    std::vector<int> numArray = { 3, 3, 7 ,7 };
    for (auto& pos : posArray)
    {
        //��һ����������numArray[pos.first]
        //�ڶ�����������numArray[pos.second]
        int sum = numArray[pos.first] + numArray[pos.second];
    }
}