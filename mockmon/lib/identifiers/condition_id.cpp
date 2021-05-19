#include "identifiers\condition_id.h"
namespace mockmon::condition
{

       
    std::string Stringify(const ConditionId condition)
    {
        switch (condition)
        {
             case ConditionId::Burn: return "Burn condition";break;
             case ConditionId::Sleep: return "Sleep condition";break;
             case ConditionId::Poison: return "Poison condition";break;
             case ConditionId::Freeze: return "Freeze condition";break;
             case ConditionId::Paralysis: return "Paralysis condition";break;
             case ConditionId::Flinch: return "Flinch condition";break;
             case ConditionId::Reflect: return "Reflect";break;
             case ConditionId::LightScreen: return "Light Screen";break;

            default: return "Unknown condition!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const ConditionId &e)
    {
        os << Stringify(e);
        return os;
    }
}