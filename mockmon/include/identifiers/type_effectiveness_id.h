#pragma once
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
    std::ostream& operator<<(std::ostream& os,const TypeEffectivenessModifier& typeEffectivenessModifier);
}