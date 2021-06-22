#pragma once

#include "identifiers/level_up_groups_id.h"
#include <string>
#include <iostream>

namespace mockmon
{
    struct MockmonExp
    {
        const long CurrentLevel;
        const long CurrentExperience;
        [[nodiscard]] static unsigned long TotalExperinceForLevel(unsigned int level, LevelUpGroup LevelUpGroup);
        friend std::ostream &operator<<(std::ostream &os, const MockmonExp &mx);

    private:
        [[nodiscard]] static unsigned long FastLevelUpGroup(unsigned int level);
        [[nodiscard]] static unsigned long MediumFastLevelUpGroup(unsigned int level);
        [[nodiscard]] static unsigned long MediumSlowLevelUpGroup(unsigned int level);
        [[nodiscard]] static unsigned long SlowLevelUpGroup(unsigned int level);
    };
}