#include "moves.h"
#include "random_gen.h"

#include <string>
#include <iostream>
#include <sstream>

namespace mockmon::moves
{
    /*
    stats modifers (increase attck, decrease enemy defence, accuracy)
    status : confused, poison, paralyzed,etc
    moves that deal unique amount of damage (set amount, percent, bylevel)
    moves with recoil damage,
    */

    //
    std::string moveToStr(const MoveId baseMove)
    {
        switch (baseMove)
        {
            case MoveId::Struggle: return "Struggle"; break;
            case MoveId::Tackle: return "Tackle";break;
            case MoveId::TailWhip: return "Tail Whip"; break;
            case MoveId::QuickAttack: return "Quick Attack"; break;
            case MoveId::HyperFang: return "Hyper Fang"; break;
            case MoveId::FocusEnergy: return "Focus Energy"; break;
            case MoveId::SuperFang: return "Super Fang"; break;
            case MoveId::WaterGun: return "WaterGun";break;
            case MoveId::Slash: return "Slash";break;
            case MoveId::Guillotine: return "Guillotine";break;
            case MoveId::PoisonSting: return "Poison Sting";break;
            case MoveId::StringShot: return "String Shot";break;
            case MoveId::Ember: return "Ember";break;
            
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
        //id,{id,type,accuracy,power}
        {MoveId::Tackle, BaseMove(MoveId::Tackle,types::Types::Normal,95,35)},
        {MoveId::TailWhip,BaseMove(MoveId::TailWhip,types::Types::Normal,100,5)},
        {MoveId::QuickAttack,BaseMove(MoveId::QuickAttack,types::Types::Normal,100,40)},
        {MoveId::HyperFang,BaseMove(MoveId::HyperFang,types::Types::Normal,90,80)},
        {MoveId::FocusEnergy,BaseMove(MoveId::FocusEnergy,types::Types::Normal,100,5)},
        {MoveId::SuperFang,BaseMove(MoveId::SuperFang,types::Types::Normal,90,5)},
        {MoveId::WaterGun, BaseMove(MoveId::WaterGun,types::Types::Water,100,40)},
        {MoveId::Guillotine ,BaseMove(MoveId::Guillotine ,types::Types::Normal,30,200)},
        {MoveId::Slash ,BaseMove(MoveId::Slash ,types::Types::Normal,100,70)},
        {MoveId::PoisonSting ,BaseMove(MoveId::PoisonSting,types::Types::Poison ,100,15)}, //status
        {MoveId::StringShot ,BaseMove(MoveId::StringShot,types::Types::Bug,95,10)}, //status
        {MoveId::Ember ,BaseMove(MoveId::Ember,types::Types::Fire,100,40)},
        {MoveId::Struggle, BaseMove(MoveId::Struggle,types::Types::Typeless,50,30)},
    };

    const std::map<MoveId,ConstantMove> ConstantMove::AllMovesWrappers
    {
        //id,{id, base pp,max pp}
        {MoveId::Tackle, ConstantMove(MoveId::Tackle,35,56)},
        {MoveId::TailWhip,ConstantMove(MoveId::TailWhip,30,48)},
        {MoveId::QuickAttack,ConstantMove(MoveId::QuickAttack,30,48)},
        {MoveId::HyperFang,ConstantMove(MoveId::HyperFang,15,24)},
        {MoveId::FocusEnergy,ConstantMove(MoveId::FocusEnergy,30,48)},
        {MoveId::SuperFang,ConstantMove(MoveId::SuperFang,10,16)},
        {MoveId::WaterGun, ConstantMove(MoveId::WaterGun,25,40)},
        {MoveId::Guillotine ,ConstantMove(MoveId::Guillotine ,5,8)},
        {MoveId::Slash ,ConstantMove(MoveId::Slash ,20,32)},
        {MoveId::PoisonSting ,ConstantMove(MoveId::PoisonSting ,35,56)},
        {MoveId::StringShot ,ConstantMove(MoveId::StringShot ,40,64)},
        {MoveId::Ember ,ConstantMove(MoveId::Ember ,25,40)},
        {MoveId::Struggle, ConstantMove(MoveId::Struggle,500,1000)}, //probably not needed!
    };

    double BaseMove::CriticalChanceBoost() const
    {
        switch (Identifier())
        {
        //high critical Rate
        case MoveId::Slash :

        return 8.0; break;
        
        default:
        return 1.0;
            break;
        }
    }
    bool CheckMoveAccuracy(const BaseMove & attack)
    {
        return (attack.BaseAccuracy > random::Randomer::GetRandom());
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
        description.append(moveToStr(Identifier())).append(" it has ").append(std::to_string(RemainningPowerPoints())).append(" power points left");
      return description;
    }
}