#pragma once
#include <iostream>
namespace mockmon::types
{
    enum class Types
    {      
        Typeless,
        Normal,
        Fire,
        Water,
        Electric,
        Grass,
        Ice,
        Fighting,
        Poison,
        Ground,
        Flying,
        Psychic,
        Bug,
        Rock,
        Ghost,
        Dragon,
        Dark,
        Steel,
        Fairy
    };
    std::ostream& operator<<(std::ostream& os,const Types& type);
}