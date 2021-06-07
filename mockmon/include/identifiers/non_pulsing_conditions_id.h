#pragma once
#include <string>
#include <iostream>
namespace mockmon::condition
{
    /**
     * @brief 
     * conditions that simple exist, without anyeffect.
     */
    enum class NonPulsingConditionId
    {
        Reflect, //not actually a condition, but that's how i'm gonna use it.
        LightScreen, //not actually a condition, but that's how i'm gonna use it.
        FocusEnergy, //not actually a condition, but that's how i'm gonna use it.
    };
    std::string Stringify(const NonPulsingConditionId condition);
    std::ostream &operator<<(std::ostream &os, const NonPulsingConditionId &e);

}