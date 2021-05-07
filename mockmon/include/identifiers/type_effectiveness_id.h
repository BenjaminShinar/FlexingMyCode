#pragma once
#include <string>
#include <iostream>

namespace mockmon::types
{
    enum class TypeEffectivenessModifier
    {   
        NotEffective,
        VeryNotEffective, 
        NotVeryEffective,
        NormalEffective,
        VeryEffective,
        SuperEffective, //4.0
    };
    std::string Stringify(const TypeEffectivenessModifier typeEffectivenessModifier);
        std::ostream &operator<<(std::ostream &os, const TypeEffectivenessModifier &e);

}