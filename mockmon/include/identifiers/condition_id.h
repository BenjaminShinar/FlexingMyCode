#pragma once
#include <string>
#include <iostream>
namespace mockmon::condition
{
    //think about a way to put all the enums somewhere else, maybe template their << operator
    enum class PulsingConditionId
    {
        Burn, 
        Sleep,
        Poison,
        Paralysis,
        Confusion,
        Flinch,
        Freeze,
        Reflect, //not actually a condition, but that's how i'm gonna use it.
        LightScreen, //not actually a condition, but that's how i'm gonna use it.

        //maybe the defence halfing effect of self destruct and explosion should come here? maybe rage?
        //        Exoloded, //not actually a condition, but that's how i'm gonna use it.
        //

    };
    std::string Stringify(const PulsingConditionId condition);
    std::ostream &operator<<(std::ostream &os, const PulsingConditionId &e);

}