#pragma once

#include <string>
#include <iostream>

namespace mockmon
{
    enum class LevelUpGroup
    {
        FastLevelUp,
        MediumFastLevelUp,
        MediumSlowLevelUp,
        SlowLevelUp
    };
    struct MockmonExp
    {      
        const long CurrentLevel;
        const long CurrentExperience;
        static unsigned long TotalExperinceForLevel(unsigned int level, LevelUpGroup LevelUpGroup);
        friend std::ostream& operator<<(std::ostream& os,const MockmonExp& mx);

        private:
        static unsigned long FastLevelUpGroup(unsigned int level);
        static unsigned long MediumFastLevelUpGroup(unsigned int level);
        static unsigned long MediumSlowLevelUpGroup(unsigned int level);
        static unsigned long SlowLevelUpGroup(unsigned int level);
    };
}