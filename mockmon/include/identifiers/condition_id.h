#pragma once
#include <string>
#include <iostream>
namespace mockmon::condition
{
    //think about a way to put all the enums somewhere else, maybe template their << operator
    enum class ConditionId
    {
        Burn,
        Sleep,
        Poison,
    };
    std::string Stringify(const ConditionId condition);
    std::ostream &operator<<(std::ostream &os, const ConditionId &e);

}