#pragma once
//#include <string_view>
#include <string>
#include <iostream>
#include <map>
#include "types.h"

namespace mockmon::moves
{

    enum class MoveId
    {      
        Tackle,
        WaterGun,
    };

    std::ostream& operator<<(std::ostream& os,const MoveId& moveId);

    struct BaseMove
    {
        const moves::MoveId MoveId;
        const types::Types Type;
        const unsigned int Accuracy;
        const unsigned int Power;
        const unsigned int BasePowerPoints;
        const unsigned int MaxPowerPoints;
        static const std::map<moves::MoveId,BaseMove> AllMoves;
        private:
        explicit BaseMove(moves::MoveId moveId, types::Types type, unsigned int accuracy, unsigned int power,unsigned int basePP, unsigned int maxPP):
        MoveId(moveId),Type(type),Accuracy(accuracy),Power(power), BasePowerPoints(basePP),MaxPowerPoints(maxPP)
        {}
        

    };
}
