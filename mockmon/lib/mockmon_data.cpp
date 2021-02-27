#include "mockmon_data.h"

namespace mockmon
{
    void Mockmon::GrantExperiencePoints(long points)
    {
        //if (points == 0) return;
        auto neededToNextLevel =((level*2 -1 ) *100) - experience_points;
        auto reminder = points - neededToNextLevel;

        if (points < neededToNextLevel)
        {
            experience_points += points;
            
        }
        else
        {
            experience_points += neededToNextLevel;
            LevelUp();
            GrantExperiencePoints(reminder);
        }
    }

    //level 1: 0 -100
    //level 2: 100-200
    //level 3: 200 - 400
    //level 4: 400 - 700
    //level 5: 700 - 1100
    //level 6: 1100 - 1600
    //level 7: 1600 - 2200
    //level 8: 2200 - 2900
    //level 9: 2900 - 3700
    //level 10: 3700 - 4600
    //level 10: 4600 - 5600
    //level 10: 5600 - 6700
    void Mockmon::LevelUp()
    {
        auto nextLevel = level+1;
        std::cout << m_name << " level increase! [" << level << " -> " << nextLevel << "]"<<'\n';
        ++level;
        //evolve?

    }

    void Mockmon::ChangeName(const std::string & newName)
    {
        m_name = newName;
    }

    std::ostream& operator<<(std::ostream& os,const MockmonExp& mx)
    {
        os << "Level: " << mx.CurrentLevel << " Exp: " << mx.CurrentExperience;
        return os;
    }
}