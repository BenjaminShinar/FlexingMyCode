#include "identifiers\level_up_groups_id.h"
namespace mockmon
{
    std::string Stringify(const LevelUpGroup levelUpGroup)
    {
        switch (levelUpGroup)
        {
            case LevelUpGroup::FastLevelUp : return "Fast Level Up Group";break;
            case LevelUpGroup::MediumSlowLevelUp : return "Medium Slow Level Up Group";break;
            case LevelUpGroup::MediumFastLevelUp: return "Medium Fast Level Up Group"; break;
            case LevelUpGroup::SlowLevelUp : return "Slow Level Up Group";break;

            default: return "Unknown Group!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const LevelUpGroup &e)
    {
        os << Stringify(e);
        return os;
    }
}