#include "moves.h"
#include "random_gen.h"

#include <string>
#include <iostream>
#include <sstream>

namespace mockmon::moves
{
    std::string moveToStr(const MoveId baseMove)
    {
        switch (baseMove)
        {
        case MoveId::Tackle : return "Tackle";break;
        case MoveId::WaterGun : return "WaterGun";break;
        case MoveId::Guillotine: return "Guillotine";break;
        case MoveId::Struggle: return "Struggle"; break;
        default: return "Unknown move!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const MoveId& type)
    {
        os << moveToStr(type);
        return os;
    }

    const std::map<MoveId,BaseMove> BaseMove::AllMoves
    {
        //id,{id,type,accuracy,power, base pp,max pp}
        {MoveId::Tackle, BaseMove(MoveId::Tackle,types::Types::Normal,95,35,35,46)},
        {MoveId::WaterGun, BaseMove(MoveId::WaterGun,types::Types::Water,100,40,25,40)},
        {MoveId::Guillotine ,BaseMove(MoveId::Guillotine ,types::Types::Normal,30,200,5,8)},
        {MoveId::Struggle, BaseMove(MoveId::Struggle,types::Types::Typeless,50,30,500,1000)},
    };

    moves::MoveId BaseMove::Identifier() const
    {
        return MoveId;
    }

    bool BaseMove::UseMove() const
    {
        return (BaseAccuracy > random::Randomer::GetRandom());
    }



    unsigned int EquipedMove::RemainningPowerPoints() const
    {
        return m_currentPowerPoints;
    }
    bool EquipedMove::UseMove()
    {
        if (0 < RemainningPowerPoints())
        {
            --m_currentPowerPoints;
            if (BaseMoveStats.BaseAccuracy > random::Randomer::GetRandom())
            {
                return true;
            }
        }
        return false;;
    }

    void EquipedMove::RefillPowerPoints()
    {
        m_currentPowerPoints = m_fullPowerPoints;
    }
    
    bool EquipedMove::IncreasePowerPoints()
    {
        auto possible = m_fullPowerPoints < BaseMoveStats.BaseMaxPowerPoints;
        if (possible)
        {
            ++m_fullPowerPoints;
        }
        return possible;
    }
    std::string EquipedMove::Describe() const
    {
      std::string description("move is ");
        description.append(moveToStr(Identifier())).append(" it has ").append(std::to_string(RemainningPowerPoints())).append(" power points left");
      return description;
    }

    moves::MoveId EquipedMove::Identifier() const
    {
        return BaseMoveStats.MoveId;
    }


}