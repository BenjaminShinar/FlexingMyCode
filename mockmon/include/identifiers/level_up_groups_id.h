#pragma once
#include <string>
#include <iostream>

namespace mockmon
{
    enum class LevelUpGroup
    {
        FastLevelUp,
        MediumFastLevelUp,
        MediumSlowLevelUp,
        SlowLevelUp
    };

    std::string Stringify( const LevelUpGroup levelUpGroup); 
    std::ostream &operator<<(std::ostream &os, const LevelUpGroup &e);

}