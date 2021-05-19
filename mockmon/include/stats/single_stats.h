#pragma once

#include "stats.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <map>

namespace mockmon::stats
{

    double BoostFromStatModifierLevel(StatModifiersLevels l);
    class BattleSingleStat
    {
    public:
        
        BattleSingleStat(StatsTypes statTypeIdentifier, double statValue) :StatTypeIdentifier(statTypeIdentifier), m_stat(statValue) {}
        double GetStat() const { return m_stat * m_currentBoost; };
        double GetBaseStat() const {return m_stat; };

        double GetBoost() const { return m_currentBoost; };
        void ResetBoost() 
        {
             m_currentBoost = 1.0;
             m_statModifer = StatModifiersLevels::Normal;
        }
        void ChangeStat(double statValue) { m_stat = statValue; }
        void AddModifier(StatModifiersLevels modifer)
        {
            auto m = static_cast<int>(m_statModifer) + static_cast<int>(modifer);
            m_statModifer = static_cast<StatModifiersLevels>(std::clamp<int>(m, static_cast<int>(StatModifiersLevels::Lowest), static_cast<int>(StatModifiersLevels::Highest)));
            m_currentBoost = BoostFromStatModifierLevel(m_statModifer);
        }
        
        const StatsTypes StatTypeIdentifier;

    private:               
        double m_stat;
        StatModifiersLevels m_statModifer;
        
        double m_currentBoost{1.0};
    };

    class HealthStat
    {
    public:
        HealthStat(int statValue) : m_max_stat(statValue), m_current_stat(statValue) {}
        int GetStat() const { return m_current_stat; }
        int GetMaxStat() const { return m_max_stat; }

        void RestStatToMax() { m_current_stat = m_max_stat; }
        void ChangeHealth(int statChange) { ChangeCurrentStat(m_current_stat + statChange); }
        void ChangeStatMax(int statValue) { m_max_stat = statValue; }

    private:
        void ChangeCurrentStat(int statChange) { m_current_stat = std::clamp(statChange, 0, m_max_stat); }
        int m_max_stat;
        int m_current_stat;
    };
}