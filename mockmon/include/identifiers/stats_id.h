#pragma once
#include <string>
#include <iostream>
namespace mockmon
{
    enum class StatsTypes
    {
        HealthPoints, //special!
        Attack,
        Defence,
        Special,
        Speed,
        Accuracy,
        Evasion,
    };
    std::string Stringify(const StatsTypes statType);
    std::ostream &operator<<(std::ostream &os, const StatsTypes &e);

}