#include "identifiers/badges_id.h"
namespace mockmon::badges
{

    std::string Stringify(const IndigoBadge condition)
    {
        switch (condition)
        {
        case IndigoBadge::Boulder_Badge:
            return "Boulder Badge";
            break;
        case IndigoBadge::Cascage_Badge:
            return "Cascage Badge";
            break;
        case IndigoBadge::Thunder_Badge:
            return "Thunder Badge";
            break;
        case IndigoBadge::Rainbow_Badge:
            return "Rainbow Badge";
            break;
        case IndigoBadge::Soul_Badge:
            return "Soul Badge";
            break;
        case IndigoBadge::Marsh_Badge:
            return "Marsh Badge";
            break;
        case IndigoBadge::Volcano_Badge:
            return "Volcano Badge";
            break;
        case IndigoBadge::Earth_Badge:
            return "Earth Badge";
            break;

        default:
            return "Unknown Badge!";
            break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const IndigoBadge &e)
    {
        os << Stringify(e);
        return os;
    }
}
