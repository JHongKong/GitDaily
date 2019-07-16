#include "stdafx.h"
#include "BoxGame.h"
#include "AStar.h"



//std::vector<Direction> dirs = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };


bool BoxGame::InitMap(char *map, int row, int col)
{
    if ((row < 0) || (row >= MAX_MAP_ROW))
    {
        return false;
    }

    if ((col < 0) && (col >= MAX_MAP_COL))
    {
        return false;
    }

    m_map = new BoxGameMap(map, row, col);
    GameState *state = new GameState(map, row, col);
    m_states.push_back(state);
    m_map->PrintMap();
    return (m_map != nullptr);
}

bool BoxGame::ResolveGame()
{
    int index = 0;
    while (index < static_cast<int>(m_states.size()))
    {
        GameState *state = m_states[index];
        if (IsFinalState(state))
        {
            m_result++;
            PrintMoveRecords(state);
        }
        else
        {
            SearchNewGameStates(state);
        }

        index++;
        if ((index % 1000) == 0)
            std::cout << "index " << index << std::endl;
    }

    return (m_result > 0);
}

bool BoxGame::CanPushBox(GameState *state, const MapPos& man, int row_offset, int col_offset)
{
    bool canMove = false;

    MapPos box = { man.row + row_offset, man.col + col_offset }; //С�˵��ƶ�����������
    MapPos boxTo = { box.row + row_offset, box.col + col_offset }; //���ӵ���λ������

    MapNode& node = m_map->Get(boxTo.row, boxTo.col);
    if (node.isDead)
    {
        return false; //���λ��������
    }
    if ((node.value == MAP_V_BOARD) || state->IsBox(boxTo.row, boxTo.col))
    {
        return false; //���λ�����ϰ������������
    }

    return true;
}

void BoxGame::SearchNewGameStates(GameState *state)
{
    Direction dirs[] = { { -1, 0 },{ 0, 1 },{ 1, 0 },{ 0, -1 } };

    for (int i = 0; i < state->GetBoxCount(); i++)
    {
        //���ÿһ��������Χ�ĸ������Ƿ��п�λ�ã����Խ�С���ƶ�����
        MapPos box = state->GetBox(i);
        for (auto& dir : dirs)
        {
            MapPos newMan = { box.row + dir.row_offset, box.col + dir.col_offset };
            //ֻҪ����ǽ�����ӣ��ͳ����ܷ�С���ƶ������ӱ���
            if (!m_map->IsWall(newMan.row, newMan.col) && !state->IsBox(newMan.row, newMan.col))
            {
                AStar astar(m_map, state);
                std::vector<MapPos> path;
                if (astar.FindPath(state->GetMan(), newMan, path)) //��·�����Ե�����ط�
                {
                    //�Ƶķ�����С�˵�������λ�õķ�����
                    Direction push = { -dir.row_offset, -dir.col_offset };
                    MoveToNewState(state, newMan, path, push);//���������λ��������
                }
            }
        }
    }
}

void BoxGame::MoveToNewState(GameState *parent, const MapPos& man, std::vector<MapPos>& path, const Direction& push)
{
    if (CanPushBox(parent, man, push.row_offset, push.col_offset))
    {
        GameState *state = new GameState(parent);
        state->SetActionPath(path);
        state->MoveMan(man.row, man.col, push.row_offset, push.col_offset);
        if (!AddNewState(state))
        {
            delete state;
        }
    }
}

bool BoxGame::IsFinalState(const GameState *state)
{
    for (int i = 0; i < state->GetBoxCount(); i++)
    {
        MapPos box = state->GetBox(i);
        MapNode node = m_map->Get(box.row, box.col);
        if (!node.isDest)
            return false;
    }

    return true;
}

bool BoxGame::AddNewState(GameState *state)
{

    for (auto& item : m_states)
    {
        if (item->IsSameState(state))
        {
            return false;
        }
    }

    m_states.push_back(state);
    return true;
}

void BoxGame::PrintMoveRecords(GameState *state)
{
    std::cout << "Find result "<< m_result << ": " << std::endl;
    
    GameState *parent = state;
    while (parent != nullptr)
    {
        const std::vector<MapPos>& path = parent->GetActionPath();

        std::cout << "Step x:" << std::endl;
        if (!path.empty())
        {
            std::cout << "Man Move :";
            for (auto& item : path)
            {
                std::cout << "[" << item.row << " , " << item.col << "] ";
            }
            std::cout << std::endl;
        }
        MapPos man = parent->GetMan();

        std::cout << "Man push [ "<< man.row << " , "<< man.col << " ]" << std::endl;

        parent = parent->GetParent();
    }

    std::cout << std::endl;
}
