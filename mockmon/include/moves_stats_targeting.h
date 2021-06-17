#pragma once

#include "identifiers/moves_stats_targeting_id.h"
#include "identifiers/stats_id.h"
#include "interfaces.h"

#include <map>

namespace mockmon::moves
{
    //which moves target which stats to calculate damage
    struct MoveStatsTargeting : public IdentifiybleModule<MovesTargeting>
    {
        const StatsTypes AttackerStat;
        const StatsTypes DefenderStat;

        static const std::map<moves::MovesTargeting, MoveStatsTargeting> AllStatsTargeting;
        explicit MoveStatsTargeting(moves::MovesTargeting movesTargeting, StatsTypes attackerStat, StatsTypes defenederStat) : IdentifiybleModule(movesTargeting),
                                                                                                                               AttackerStat(attackerStat), DefenderStat(defenederStat)
        {
        }
    };
}