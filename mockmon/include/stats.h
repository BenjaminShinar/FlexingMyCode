#pragma once

#include "identifiers/moves_id.h"
#include "identifiers/stat_modifiers_id.h"
#include "identifiers/stats_id.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <map>

namespace mockmon
{

    struct SpeciesStats
    {
        explicit SpeciesStats(unsigned int attack, unsigned int defence, unsigned int special, unsigned int speed, unsigned health) : Attack(attack), Defence(defence), Special(special), Speed(speed), Health(health)
        {
        }

        const unsigned int Attack{1};
        const unsigned int Defence{1};
        const unsigned int Special{1};
        const unsigned int Speed{1};
        const unsigned int Health{1};
    };

    struct IndividualStats : public SpeciesStats
    {
    private:
        static unsigned int CalculateHealth(unsigned int attack, unsigned int defence, unsigned int special, unsigned int speed)
        {
            auto a1 = (attack & 0x1) << 0;
            auto a2 = (defence & 0x1) << 1;
            auto a3 = (speed & 0x1) << 2;
            auto a4 = (special & 0x1) << 3;

            return (a1 | a2 | a3 | a4);
        }

    public:
        explicit IndividualStats(unsigned int attack, unsigned int defence, unsigned int special, unsigned int speed) : SpeciesStats(attack, defence, special, speed, CalculateHealth(attack, defence, special, speed))
        {
        }

        //this is for enemies
        explicit IndividualStats() : SpeciesStats(9u, 8u, 8u, 8u, CalculateHealth(9u, 8u, 8u, 8u))
        {
        }
    };

    //think about how this should work
    struct Stats
    {
        // base, iv,evs
        explicit Stats() = default;
        explicit Stats(const SpeciesStats &baseStats, const IndividualStats &IVStats, const Stats &EVStats, unsigned int level);

        unsigned int Health{0};
        unsigned int Attack{0};
        unsigned int Defence{0};
        unsigned int Special{0};
        unsigned int Speed{0};

        Stats &operator+=(const SpeciesStats &);

    private:
        const unsigned int MaxStatValue = 65535;
        unsigned int ModifyStat(unsigned int base, unsigned int iv, unsigned int ev, unsigned int level);
    };

    template <typename T>
    class BattleSingleStat
    {
    public:
        BattleSingleStat(T statValue) : m_stat(statValue) {}
        T GetStat() const { return m_stat * m_currentBoost; };
        T GetBaseStat() const { m_currentBoost; };
        double GetBoost() const { return m_currentBoost; };
        void ResetBoost() 
        {
             m_currentBoost = 1.0;
             m_statModifer = StatModifiersLevels::Normal;
        }
        void ChangeStat(T statValue) { m_stat = statValue; }
        void AddModifier(StatModifiersLevels modifer)
        {
            auto m = static_cast<int>(m_statModifer) + static_cast<int>(modifer);
            m_statModifer = static_cast<StatModifiersLevels>(std::clamp<int>(m, static_cast<int>(StatModifiersLevels::Lowest), static_cast<int>(StatModifiersLevels::Highest)));
            m_currentBoost = GetBoostFromLevel(m_statModifer);
        }
        
        static double GetBoostFromLevel(StatModifiersLevels l)
        {
                switch (l)
                    {
                    case StatModifiersLevels::Lowest: return 0.25; break;
                    case StatModifiersLevels::DecresedEvenFurther: return 0.28; break;  //28/100
                    case StatModifiersLevels::DecreasedMuchFurther: return 0.33; break; // 33/100
                    case StatModifiersLevels::DecreasedSeverly: return 0.4; break;  //40/100
                    case StatModifiersLevels::GreatlyDecreased: return 0.5; break;   //50/100
                    case StatModifiersLevels::Decrese: return 0.66; break;          //66/100
                    case StatModifiersLevels::Normal: return 1.0; break;           //100/100
                    case StatModifiersLevels::Increase: return 1.5; break;              //150/100
                    case StatModifiersLevels::GreatlyIncrease: return 2.0; break;      //200/100
                    case StatModifiersLevels::IncreasedDrastically: return 2.5; break;  //250/100
                    case StatModifiersLevels::IncreasedMuchFurther : return 3.0; break;  //300/100
                    case StatModifiersLevels::IncreasedEvenFurther: return 3.5; break;  //350/100
                    case StatModifiersLevels::Highest: return 4.0; break;               //400/100           
                    default: return 1.0;break;
                    }
        }
    private:
                

        T m_stat;
        StatModifiersLevels m_statModifer;
        double m_currentBoost{1.0};
    };

    class HealthStat
    {
    public:
        HealthStat(int statValue) : m_max_stat(statValue), m_current_stat(statValue) {}
        int GetStat() const { return m_current_stat; }
        void RestStatToMax() { m_current_stat = m_max_stat; }
        void ChangeHealth(int statChange) { ChangeCurrentStat(m_current_stat + statChange); }
        void ChangeStatMax(int statValue) { m_max_stat = statValue; }

    private:
        void ChangeCurrentStat(int statChange) { m_current_stat = std::clamp(statChange, 0, m_max_stat); }
        int m_max_stat;
        int m_current_stat;
    };

    struct BattleStats
    {

        explicit BattleStats() = default;
        BattleStats(const Stats &stats) : Health(stats.Health)
        {
            m_battleStats.emplace((StatsTypes::Attack), BattleSingleStat<double>(stats.Attack));
            m_battleStats.emplace((StatsTypes::Defence), BattleSingleStat<double>(stats.Defence));

            m_battleStats.emplace((StatsTypes::Special), BattleSingleStat<double>(stats.Special));
            m_battleStats.emplace((StatsTypes::Speed), BattleSingleStat<double>(stats.Speed));
            m_battleStats.emplace((StatsTypes::Evasion), BattleSingleStat<double>(100.0));
            m_battleStats.emplace((StatsTypes::Accuracy), BattleSingleStat<double>(100.0));
        }

        void UpdateStats(const Stats &stats)
        {
            Health.ChangeStatMax(stats.Health);
            m_battleStats.at(StatsTypes::Attack).ChangeStat(stats.Attack);
            m_battleStats.at(StatsTypes::Defence).ChangeStat(stats.Defence);
            m_battleStats.at(StatsTypes::Special).ChangeStat(stats.Special);
            m_battleStats.at(StatsTypes::Speed).ChangeStat(stats.Speed);
        }

        std::map<StatsTypes, BattleSingleStat<double>> m_battleStats =
        {
            {StatsTypes::Attack, BattleSingleStat<double>(1.0)},
            {StatsTypes::Defence, BattleSingleStat<double>(1.0)},
            {StatsTypes::Special, BattleSingleStat<double>(1.0)},
            {StatsTypes::Speed, BattleSingleStat<double>(1.0)},
            {StatsTypes::Evasion, BattleSingleStat<double>(1.0)},
            {StatsTypes::Accuracy, BattleSingleStat<double>(1.0)},
        };
        HealthStat Health{1}; //this should be special
    };
}