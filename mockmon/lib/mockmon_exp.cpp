#include "mockmon_exp.h"
#include <math.h>

namespace mockmon
{
    std::ostream& operator<<(std::ostream& os,const MockmonExp& mx)
    {
        os << "Level: " << mx.CurrentLevel << " Exp: " << mx.CurrentExperience;
        return os;
    }

    unsigned long MockmonExp::TotalExperinceForLevel(unsigned int level, LevelUpGroup levelUpGroup)
    {
        switch (levelUpGroup)
        {
            case LevelUpGroup::FastLevelUp: return FastLevelUpGroup(level);break;
            case LevelUpGroup::MediumFastLevelUp: return MediumFastLevelUpGroup(level);break;
            case LevelUpGroup::MediumSlowLevelUp: return MediumSlowLevelUpGroup(level);break;
            case LevelUpGroup::SlowLevelUp: return SlowLevelUpGroup(level);break;
            default:break;
        }
        return 150000000;
    }

    unsigned long MockmonExp::FastLevelUpGroup(unsigned int level)
    {
        return std::floor(4*(std::pow(level,3)/5));

    }
    unsigned long MockmonExp::MediumFastLevelUpGroup(unsigned int level)
    {
        return (std::pow(level,3));
    }
    unsigned long MockmonExp::MediumSlowLevelUpGroup(unsigned int level)
    {
        auto a = std::floor(6*(std::pow(level,3)/5));
        auto b = -15 * std::pow(level,2);
        auto c = 100*level;
        auto d = -140;
        auto xp = (a+b+c+d);
        return (std::max(xp,0.0));
    }
    unsigned long MockmonExp::SlowLevelUpGroup(unsigned int level)
    {
        return std::floor(5*(std::pow(level,3)/4));
    }
}