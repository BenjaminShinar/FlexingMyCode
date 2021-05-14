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

            default: return "Unknown condition!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const ConditionId &e)
    {
        os << Stringify(e);
        return os;
    }
}