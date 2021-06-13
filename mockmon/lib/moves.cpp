#include "moves.h"
#include "random_gen.h"

#include <string>
#include <iostream>
#include <sstream>
#include <interfaces.h>

namespace mockmon::moves
{

    types::Types GetMoveType(moves::MoveId mvId)
    {
        return SimpleMove::AllMoves.at(mvId).Type;
    }
    
    //move this elsewhere?
    double CriticalChanceBoost(moves::MoveId mvId)
    {
        switch (mvId)
        {
        //high critical Rate
        case MoveId::Slash:
        case MoveId::Crabhammer:
        case MoveId::KarateChop:
        case MoveId::RazorLeaf:
        return 8.0; break;
        
        default:
        return 1.0;
            break;
        }
    }

    //move this elsewhere?
    Priority GetMovePriority(moves::MoveId mvId)
    {
        switch (mvId)
        {
            case moves::MoveId::QuickAttack:       
            return Priority::PositivePriority; break;
            case moves::MoveId::Counter:       
            return Priority::NegativePriority; break;
            default: return Priority::Normal;break;
        }
    }


    unsigned int EquipedMove::RemainningPowerPoints() const
    {
        return m_currentPowerPoints;
    }
    
    std::optional<moves::MoveId> EquipedMove::UseMove()
    {
        if (0 < RemainningPowerPoints())
        {
            --m_currentPowerPoints;
            return Identifier();
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
        description.append(Stringify(Identifier())).append(" it has ").append(std::to_string(RemainningPowerPoints())).append(" power points left");
      return description;
    }
}