#include "moves_stats_targeting.h"
#include "interfaces.h"

namespace mockmon::moves
{
   
    const std::map<MovesTargeting,MoveStatsTargeting> moves::MoveStatsTargeting::AllStatsTargeting
    {
        //id,{id,AtackingStat,DefendingStat}
        MakeDictionaryPair<MoveStatsTargeting>(MovesTargeting::PurePhysical,StatsTypes::Attack,StatsTypes::Defence),
        MakeDictionaryPair<MoveStatsTargeting>(MovesTargeting::PureSpecial,StatsTypes::Special,StatsTypes::Special),
        MakeDictionaryPair<MoveStatsTargeting>(MovesTargeting::AccuracyEvasion,StatsTypes::Accuracy,StatsTypes::Evasion),
        // MakeDictionaryPair<SimpleMove>(MoveId::TailWhip,types::Types::Normal,100,5),
        // MakeDictionaryPair<SimpleMove>(MoveId::QuickAttack,types::Types::Normal,100,40),
        // MakeDictionaryPair<SimpleMove>(MoveId::HyperFang,types::Types::Normal,90,80),
        // MakeDictionaryPair<SimpleMove>(MoveId::FocusEnergy,types::Types::Normal,100,5),
    };
} 