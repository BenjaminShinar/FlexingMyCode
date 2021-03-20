#include "moves.h"

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
        {MoveId::WaterGun, BaseMove(MoveId::WaterGun,types::Types::Water,100,40,25,40)}
    };

    unsigned int EquipedMove::RemainningPowerPoints() const
    {
        return m_currentPowerPoints;
    }
    std::optional<int> EquipedMove::UseMove()
    {
        if (0 < RemainningPowerPoints())
        {
            --m_currentPowerPoints;
            if (BaseMoveStats.BaseAccuracy >90)
            {
                return BaseMoveStats.BasePower;
            }
        }
        return {};
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
        description.append( "some name ").append(" it has ").append(std::to_string(RemainningPowerPoints())).append(" power points left");
      return description;
    }

    moves::MoveId EquipedMove::Identifier() const
    {
        return BaseMoveStats.MoveId;
    }


}