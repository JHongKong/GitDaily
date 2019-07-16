// bucket.cpp 
//

#include "stdafx.h"
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_set>
#include <utility>
#include "bucket_state.h"
#include <functional>
#include <algorithm>

int b_capicity[BUCKETS_COUNT] = { 8, 5, 3 };
int b_init[BUCKETS_COUNT] = { 8, 0, 0 };
int b_final[BUCKETS_COUNT] = { 4, 4, 0 };

double sd = 200.9;



bool IsProcessedState(const std::deque<BucketsState>& states, const BucketsState& newState)
{
    auto it = find_if(states.begin(), states.end(), 
        [&newState](const BucketsState& item) {return (item.operator==(newState)); });

    return (it != states.end());
}

void PrintResult(const std::deque<BucketsState>& states)
{
    std::cout << "Find Result : " << std::endl;
    for (auto& x : states)
    {
        x.PrintStates();
    }
    std::cout << std::endl << std::endl;
}


bool IsFinalState(const BucketsState& state)
{
    for (int i = 0; i < BUCKETS_COUNT; ++i)
    {
        if (state.GetBucket(i).GetWater() != b_final[i])
            return false;
    }

    return true;
}

std::vector<std::pair<int, int>> action_table = { {0, 1}, {0, 2}, {1, 0}, {1, 2}, {2, 0}, {2, 1} };

void SearchState(std::deque<BucketsState>& states)
{
    BucketsState current = states.back(); /*ÿ�ζ��ӵ�ǰ״̬��ʼ*/
    if(IsFinalState(current)) //�ж��Ƿ񵽴�4,4,0״̬
    {
        PrintResult(states); //���һ����
        return;
    }

    for (const auto& act : action_table)
    {
        BucketsState next;
        /*��from��to��ˮ������ɹ���next���ص�ˮ���״̬*/
        if (current.TakeAction(act.first, act.second, next))
        {
            if (!IsProcessedState(states, next))
            {
                states.push_back(next);
                SearchState(states); //���µ�λ�ü�������
                states.pop_back();
            }
        }
    }
}

class FindName
{
public:
    FindName(const std::string& match) { m_match = match; }
    bool operator() (const std::string& item)
    {
        return (m_match == item);
    }
private:
    std::string m_match;
};


bool IsSameString(const std::string& str1, std::string str2)
{
    return (str1 == str2);
}


int main(int argc, char* argv[])
{
    int (*arr)[5] = new int[4][5];
    arr[2][3] = 56;

    std::list<std::string> strList = { "Tom", "Jim", "Jack", "Miss Fang" };
    std::list<std::string>::iterator it = std::find(strList.begin(), strList.end(), std::string("Jack"));

    FindName findJack("Jack");
    auto it2 = std::find_if(strList.begin(), strList.end(), findJack);
    auto it3 = std::find_if(strList.begin(), strList.end(), FindName("Jack"));

    std::string match = "Jack";
    auto it4 = std::find_if(strList.begin(), strList.end(),
        [&match](const std::string& item) {return (item == match); });

    auto it5 = std::find_if(strList.begin(), strList.end(),
        [](const std::string& item) {return (item == std::string("Jack")); });

    auto it6 = std::find_if(strList.begin(), strList.end(), std::bind1st(std::ptr_fun(IsSameString), "Jack"));

    std::vector<int> intArray = { 10, 20, 30, 40, 50 };

    //������������
    for (int x : intArray)
    {
        std::cout << x << std::endl;
    }

    int value = intArray.at(2); //value = 30
    intArray.at(2) = 31; //������Ԫ�ش�30���31

    //Ҳ������������
    for (std::size_t i = 0; i < intArray.size(); i++)
    {
        std::cout << intArray[i] << std::endl;
    }

    value = intArray[3]; //value = 40
    intArray[3] = 41; //���ĸ�Ԫ�ش�40���41
    intArray.insert(intArray.begin() + 3, 31);

    std::unordered_set<int> intSet = { 2, 3, 5, 6, 7, 9, 11 };
    intSet.insert(12); //���Ԫ��12
    intSet.erase(6); //ɾ��Ԫ��6
    int count = intSet.size(); //��ȡ����Ԫ�صĸ���
    intSet.clear();  //��ռ���Ԫ��
    if (!intSet.empty())  //�жϼ���Ԫ���Ƿ�Ϊ��
    {
        //...
    }

    std::unordered_set<int>::iterator it7 = intSet.find(9);
    if (it7 != intSet.end())
    {
        //...
    }

    std::map<std::string, int> siMap;

    siMap["Tom"] = 32;  //���keyΪTom��entry���ڣ�����value����Ϊ32����������ڣ������һ��entry("Tom", 32)
    siMap.insert({"Jack", 56}); //���һ��entry
    siMap.insert(std::make_pair("Mark", 43));  //��һ�����entry�ķ���
    int value2 = siMap.at("Tom");  //value = 32
    siMap.at("Jack") = 51; //entry{"Jack", 56}�޸ĳ�entry{"Jack", 51}
    int count2 = siMap.size(); //��ȡentry����Ŀ����
    if (!siMap.empty())
    {
        //map��Ϊ��
    }
    siMap.erase("Mark");  //ɾ��entry{"Mark", 43}
    std::map<std::string, int>::iterator it8 = siMap.find("Jack");
    if (it8 != siMap.end())
    {
        //�ҵ�entry{��Jack���� 51}
    }
    siMap.clear();  //ɾ��ȫ��entry

    /*
    std::list<std::string>::iterator it;
    for (it = strList.begin(); it != strList.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
    */
    for (auto x : strList)
    {
        std::cout << x << std::endl;
    }
    [](int x, int y) -> int { return x + y; };
    std::string title = "This is ";
    [&title](const std::string& x) {std::cout << title << x << std::endl; };
    std::map<int, double> mid;

    std::deque<BucketsState> states;
    BucketsState init = { { b_capicity[0], b_init[0] },
                         { b_capicity[1], b_init[1] },
                         { b_capicity[2], b_init[2] } };

    states.push_back(init); //�����ʼ״̬
    SearchState(states);  //�ӳ�ʼ״̬��ʼ����

    assert(states.size() == 1); /*��ٽ�����statesӦ�û���ֻ��һ����ʼ״̬*/

    return 0;
}
