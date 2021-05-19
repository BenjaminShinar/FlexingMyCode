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

        std::map<StatsTypes, BattleSingleStat<double>> m_battleStats =
        {
            {StatsTypes::Attack,              BattleSingleStat<double>(StatsTypes::Attack,1.0)},
            {StatsTypes::Defence,             BattleSingleStat<double>(StatsTypes::Defence,1.0)},
            {StatsTypes::Special,             BattleSingleStat<double>(StatsTypes::Special,1.0)},
            {StatsTypes::Speed,               BattleSingleStat<double>(StatsTypes::Speed,1.0)},
            {StatsTypes::Evasion,             BattleSingleStat<double>(StatsTypes::Evasion,100.0)},
            {StatsTypes::Accuracy,            BattleSingleStat<double>(StatsTypes::Accuracy,100.0)},
        };
        HealthStat Health{1}; //this should be special
    };
}