#include "identifiers/non_pulsing_conditions_id.h"
namespace mockmon::condition
{
       
    std::string Stringify(const NonPulsingConditionId condition)
    {
        switch (condition)
        {
            case NonPulsingConditionId::Reflect: return "Reflect";break;
            case NonPulsingConditionId::LightScreen: return "Light Screen";break;
            case NonPulsingConditionId::FocusEnergy: return "Focus Energy";break;

            default: return "Unknown condition!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const NonPulsingConditionId &e)
    {
        os << Stringify(e);
        return os;
    }
}