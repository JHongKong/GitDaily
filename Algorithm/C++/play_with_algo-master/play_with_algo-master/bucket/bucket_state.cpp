// bucket_state.cpp
//

#include "stdafx.h"
#include "bucket_state.h"



void Bucket::AddWater(int water)
{
    int space = m_capicity - m_water;
    if (space > 0)
    {
        m_water += ((space > water) ? water : space);
    }
}

void Bucket::DumpWater(int water)
{
    if (m_water >= water)
    {
        m_water -= water;
    }
    else
    {
        m_water = 0;
    }
}

BucketsState::BucketsState(const std::initializer_list<Bucket>& il)
{
    for (auto it = il.begin(); it != il.end(); ++it)
    {
        m_buckets.push_back(*it);
    }
    SetAction(8, -1, 0);
}

void BucketsState::SetAction(int w, int f, int t)
{
    m_curAction.water = w;
    m_curAction.from  = f;
    m_curAction.to    = t;
}

void BucketsState::PrintStates() const
{
    std::cout << "Dump " << m_curAction.water << " water from "
         << m_curAction.from + 1 << " to " << m_curAction.to + 1 << ", ";
    std::cout << "buckets water states is : ";

    for(const auto x : m_buckets)
    {
        std::cout << x.GetWater() << " ";
    }
    std::cout << std::endl;
}

bool BucketsState::operator == (const BucketsState& state) const
{
    for (std::size_t i = 0; i < m_buckets.size(); i++)
    {
        if (m_buckets[i].GetWater() != state.m_buckets[i].GetWater())
            return false;
    }

    return true;
}

/*��from��to��ˮ�����سɹ����õ��µ�״̬next*/
bool BucketsState::TakeAction(int from, int to, BucketsState& next)
{
    next = *this; //���Ƶ�ǰ״̬

    Bucket& bfrom = next.GetBucket(from);
    Bucket& bto = next.GetBucket(to);
    if (bfrom.HasWater() && !bto.IsFull())
    {
        //�ܵ���ˮ����fromʣ��ˮ����toʣ�Ŀռ����
        int dump_water = (bfrom.GetWater() > bto.GetSpace()) ? bto.GetSpace() : bfrom.GetWater();
        bto.AddWater(dump_water);
        bfrom.DumpWater(dump_water);
        next.SetAction(dump_water, from, to); //��¼��ǰ��ˮ��������������Ҫ��

        return true;
    }

    return false;
}