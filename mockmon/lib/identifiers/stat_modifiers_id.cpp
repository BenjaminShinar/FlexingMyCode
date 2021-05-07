#include "identifiers/stat_modifiers_id.h"
namespace mockmon
{

    std::string Stringify(const StatModifiersLevels statModifierLevel)
    {
        switch (statModifierLevel)
        {
            case StatModifiersLevels::Decrese: return "Decrease";break;
            case StatModifiersLevels::Normal: return "Did not change";break;
            case StatModifiersLevels::Increase: return "Increase";break;
           
            default: return "Unknown effect!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const StatModifiersLevels &e)
    {
        os << Stringify(e);
        return os;
    }
}