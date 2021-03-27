#pragma once
//#include <string_view>
#include <string>
#include <string_view>
#include <iostream>
#include <map>
#include "types.h"

namespace mockmon::moves
{

    enum class MoveId
    {      
        Tackle,
        WaterGun,
        Guillotine,
        Struggle,
    };

    std::ostream& operator<<(std::ostream& os,const MoveId& moveId);

    struct BaseMove
    {
        const moves::MoveId MoveId;
        const types::Types Type;
        const unsigned int BaseAccuracy;
        const unsigned int BasePower;
        const unsigned int BaseStartingPowerPoints;
        const unsigned int BaseMaxPowerPoints;
        static const std::map<moves::MoveId,BaseMove> AllMoves;
        
        private:
        explicit BaseMove(moves::MoveId moveId, types::Types type, unsigned int accuracy, unsigned int power,unsigned int basePP, unsigned int maxPP):
        MoveId(moveId),Type(type),BaseAccuracy(accuracy),BasePower(power), BaseStartingPowerPoints(basePP),BaseMaxPowerPoints(maxPP)
        {}

    };
    
    std::ostream& operator<<(std::ostream& os,const MoveId& type);

    //this is the move when it's on a pokemon
    class EquipedMove 
    {
        public:
        explicit EquipedMove(const BaseMove & baseMove):BaseMoveStats(baseMove), m_fullPowerPoints(baseMove.BaseStartingPowerPoints),
            m_currentPowerPoints(baseMove.BaseStartingPowerPoints)
        {
        }

        const BaseMove & BaseMoveStats; //what move it refers to, constant db of moves;
        std::string Describe() const;
        moves::MoveId Identifier() const;
        unsigned int RemainningPowerPoints() const;
        std::optional<int> UseMove();
        static constexpr std::size_t MaxMoves= 4;    
        private:
        unsigned int m_fullPowerPoints;
        unsigned int m_currentPowerPoints;
        //these probably belong with a friend class;
        void RefillPowerPoints(); 
        bool IncreasePowerPoints();

    };
}
