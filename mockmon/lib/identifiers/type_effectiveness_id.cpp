#include "identifiers/type_effectiveness_id.h"

namespace mockmon::types
{

    std::string TypeEffectivenessToStr(const TypeEffectivenessModifier typeEffectivenessModifier)
    {
        switch (typeEffectivenessModifier)
        {
            case TypeEffectivenessModifier::NotEffective: return "No effect"; break;
            case TypeEffectivenessModifier::VeryNotEffective: return "Very not effective"; break;
            case TypeEffectivenessModifier::NotVeryEffective: return "Not very effective"; break;
            case TypeEffectivenessModifier::NormalEffective: return "Normal effective"; break;
            case TypeEffectivenessModifier::VeryEffective: return "Very effective"; break;
            case TypeEffectivenessModifier::SuperEffective: return "Super effective"; break;
            default: return "Unknown effect Modifier!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const TypeEffectivenessModifier & typeEffectivenessModifier)
    {
        os << TypeEffectivenessToStr(typeEffectivenessModifier);
        return os;
    }
}