#pragma once
#include <string>
#include <iostream>
namespace mockmon::condition
{
    //think about a way to put all the enums somewhere else, maybe template their << operator
    /**
     * @brief 
     * conditions which have an effect that does something each turn.
     */
    enum class PulsingConditionId
    {
        Burn, 
        Sleep,
        Poison,
        Paralysis,
        Confusion,
        Flinch,
        Freeze
    };
    std::string Stringify(const PulsingConditionId condition);
    std::ostream &operator<<(std::ostream &os, const PulsingConditionId &e);

}