#include "identifiers\condition_id.h"
namespace mockmon::condition
{

       
    std::string Stringify(const PulsingConditionId condition)
    {
        switch (condition)
        {
             case PulsingConditionId::Burn: return "Burn condition";break;
             case PulsingConditionId::Sleep: return "Sleep condition";break;
             case PulsingConditionId::Poison: return "Poison condition";break;
             case PulsingConditionId::Freeze: return "Freeze condition";break;
             case PulsingConditionId::Paralysis: return "Paralysis condition";break;
             case PulsingConditionId::Flinch: return "Flinch condition";break;
             case PulsingConditionId::Reflect: return "Reflect";break;
             case PulsingConditionId::LightScreen: return "Light Screen";break;

            default: return "Unknown condition!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const PulsingConditionId &e)
    {
        os << Stringify(e);
        return os;
    }
}