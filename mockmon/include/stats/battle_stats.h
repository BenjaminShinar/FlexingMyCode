#pragma once

#include "stats.h"
#include "single_stats.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <array>

namespace mockmon::stats
{
    struct BattleStats
    {

        explicit BattleStats() = default;

        //this happenes at Level Up, at creation, and maybe at pokemon center / when taking vitamins?
        void UpdateStats(const MockmonStats &mockmonStats)
        {
            Health.ChangeStatMax(mockmonStats.Stats.Health);
            m_battleStats.at(StatsTypes::Attack).ChangeStat(mockmonStats.Stats.Attack);
            m_battleStats.at(StatsTypes::Defence).ChangeStat(mockmonStats.Stats.Defence);
            m_battleStats.at(StatsTypes::Special).ChangeStat(mockmonStats.Stats.Special);
            m_battleStats.at(StatsTypes::Speed).ChangeStat(mockmonStats.Stats.Speed);
        }

        // std::array<BattleSingleStat<double>,6> m_battle_stats = 
        // {
        //     BattleSingleStat<double>(StatsTypes::Attack,1.0),
        //     BattleSingleStat<double>(StatsTypes::Defence,1.0),
        //     BattleSingleStat<double>(StatsTypes::Special,1.0),
        //     BattleSingleStat<double>(StatsTypes::Speed,1.0),
        //     BattleSingleStat<double>(StatsTypes::Evasion,1.0),
        //     BattleSingleStat<double>(StatsTypes::Accuracy,1.0),
        // };

        std::map<StatsTypes, BattleSingleStat> m_battleStats =
        {
            {StatsTypes::Attack,              BattleSingleStat(StatsTypes::Attack,1)},
            {StatsTypes::Defence,             BattleSingleStat(StatsTypes::Defence,1)},
            {StatsTypes::Special,             BattleSingleStat(StatsTypes::Special,1)},
            {StatsTypes::Speed,               BattleSingleStat(StatsTypes::Speed,1)},
            {StatsTypes::Evasion,             BattleSingleStat(StatsTypes::Evasion,100)},
            {StatsTypes::Accuracy,            BattleSingleStat(StatsTypes::Accuracy,100)},
        };
        HealthStat Health{1}; //this should be special
    };
}