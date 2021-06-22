#pragma once
#include "../../mockmon/include/mockmon_data.h"
#include <algorithm>

class MockmonTestUtils
{
public:
    /**
     * @brief 
     * bring a mockmon to a required level
     * @param m 
     * @param requiredLevel 
     */
    static void BringMockmonToLevel(mockmon::Mockmon &m, int requiredLevel)
    {
        const auto levelUpGroup = m.GetMockmonSpeciesData().SpeciesLevelUpGroup;
        auto needefForLevel = mockmon::MockmonExp::TotalExperinceForLevel(requiredLevel, levelUpGroup);
        auto currentXp = m.CheckExperiencePoints().CurrentExperience;
        const auto neededxp = needefForLevel - currentXp;
        if (neededxp > 0)
        {
            m.GrantExperiencePoints(neededxp);
        }
        m.FullRestore();
    }

    static auto XorredStats(const mockmon::Mockmon &m)
    {
        const auto &battleStats = m.CurrentBattleStats.m_battleStats;
        const auto xoredStats = std::accumulate(std::begin(battleStats), std::end(battleStats), 0, [](int xorred, const auto &p)
                                                { return xorred ^ static_cast<int>(p.second.GetBaseStat()); });
        return xoredStats;
    }

    [[nodiscard]] static const std::vector<double> JumpByOneStage()
    {
        return {1.5, 2.0, 2.5, 3.0, 3.5, 4.0};
    };

    [[nodiscard]] static const std::vector<double> JumpByTwoStages()
    {
        return {2.0, 3.0, 4.0};
    };
};