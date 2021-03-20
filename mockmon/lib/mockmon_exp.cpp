#include "mockmon_exp.h"

namespace mockmon
{
    std::ostream& operator<<(std::ostream& os,const MockmonExp& mx)
    {
        os << "Level: " << mx.CurrentLevel << " Exp: " << mx.CurrentExperience;
        return os;
    }
}