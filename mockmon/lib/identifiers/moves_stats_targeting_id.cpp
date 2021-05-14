#include "identifiers/moves_stats_targeting_id.h"

namespace mockmon::moves
{
    std::string Stringify(const MovesTargeting movesTargeting)
    {
        switch (movesTargeting)
        {
            case MovesTargeting::PurePhysical: return "pure phyical target";break;
            case MovesTargeting::PureSpecial: return "pure special target";break;
            
            default: return "Unknown targeting!"; break;
        }
    }
    std::ostream &operator<<(std::ostream &os, const MovesTargeting &e)
    {
        os << Stringify(e);
        return os;
    }

}