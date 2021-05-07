#pragma once
#include <string>
#include <iostream>

namespace mockmon
{
    enum class StatModifiersLevels : int
    {
        Lowest = -6,               //25./100
        DecresedEvenFurther = -5,  //28/100
        DecreasedMuchFurther = -4, // 33/100
        DecreasedSeverly = -3,     //40/100
        GreatlyDecreased = -2,     //50/100
        Decrese = -1,              //66/100
        Normal = 0,                //100/100
        Increase = 1,              //150/100
        GreatlyIncrease = 2,       //200/100
        IncreasedDrastically = 3,  //250/100
        IncreasedMuchFurther = 4,  //300/100
        IncreasedEvenFurther = 5,  //350/100
        Highest = 6,               //400/100
    };

    std::string Stringify(const StatModifiersLevels statModifiersLevels);
        std::ostream &operator<<(std::ostream &os, const StatModifiersLevels &e);

}