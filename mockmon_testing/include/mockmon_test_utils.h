#pragma once
#include "../../mockmon/include/mockmon_data.h"
#include <algorithm>

class MockmonTestUtils
{
    public:
    template<typename V,typename T>
    static auto MakePredicator(T t)
    {
        return ([t](const V & el){return el.IsSameAs(t);});
    }

    /**
     * @brief 
     * bring a mockmon to a required level
     * @param m 
     * @param requiredLevel 
     */
    static void BringMockmonToLevel(mockmon::Mockmon & m, int requiredLevel)
    {
        const auto levelUpGroup = m.GetMockmonSpeciesData().SpeciesLevelUpGroup;
        auto needefForLevel = mockmon::MockmonExp::TotalExperinceForLevel(requiredLevel,levelUpGroup);
        auto currentXp = m.CheckExperiencePoints().CurrentExperience;
        const auto neededxp = needefForLevel - currentXp;
        if (neededxp>0)
        {
            m.GrantExperiencePoints(neededxp);
        }
        m.FullRestore();
    }
};