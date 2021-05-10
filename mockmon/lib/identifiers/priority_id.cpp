#include "identifiers/priority_id.h"

namespace mockmon::moves
{
    std::string Stringify(const Priority priority)
    {
        switch (priority)
        {
            case Priority::NegativePriority: return "Negative priority";break;
            case Priority::Normal: return "no priority";break;
            case Priority::PositivePriority: return "PositivePriority"; break;
            default: return "Unknown priority!"; break;
        }
    }
    std::ostream &operator<<(std::ostream &os, const Priority &e)
    {
        os << Stringify(e);
        return os;
    }

}