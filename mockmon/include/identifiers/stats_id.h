#pragma once
#include <string>
#include <iostream>
namespace mockmon
{
    enum class StatsTypes
    {
        Attack,
        Defence,
        Special,
        Speed,
        Accuracy,
        Evasion,
        HealthPoints, //special!
        CriticalHitChance, //special
    };
    std::string Stringify(const StatsTypes statType);
    std::ostream &operator<<(std::ostream &os, const StatsTypes &e);

}