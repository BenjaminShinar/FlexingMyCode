#pragma once
#include <string>
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
    std::string Stringify(const Types type);
    std::ostream &operator<<(std::ostream &os, const Types &type);

}