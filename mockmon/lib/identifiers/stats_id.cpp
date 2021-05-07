#include "identifiers/stats_id.h"
namespace mockmon
{

    std::string Stringify(const StatsTypes statType)
    {
        switch (statType)
        {
            case StatsTypes::Attack : return "Attack";break;
            case StatsTypes::Defence : return "Defence";break;
            case StatsTypes::Special : return "Special";break;
            case StatsTypes::Speed : return "Speed";break;
            case StatsTypes::Evasion : return "Evasion";break;
            case StatsTypes::Accuracy : return "Accuracy";break;
            case StatsTypes::HealthPoints : return "Health Points";break;
            default: return "Unknown Stat!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const StatsTypes &e)
    {
        os << Stringify(e);
        return os;
    }
}