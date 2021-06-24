#pragma once
#include "../../mockmon/include/mockmon_data.h"
#include <algorithm>

class MockmonTestUtils
{
public:
    static const auto mewSpeciesId = mockmon::MockmonSpeciesId::Mew;
    /**
     * @brief Create a Test Mockmon object
     * create a mockmon at a spesific level with a spesific name,
     * default is level 1 mew
     * @param extraName 
     * @param id 
     * @param requriedLevel 
     * @return mockmon::Mockmon 
     */
    [[nodiscard]] static mockmon::Mockmon CreateTestMockmon(std::string &&extraName, mockmon::MockmonSpeciesId id = mewSpeciesId, unsigned int requriedLevel = 1)
    {
        mockmon::Mockmon m(id, mockmon::AppendAll({Stringify(id), "level", std::to_string(requriedLevel), extraName}), true);
        BringMockmonToLevel(m, requriedLevel);
        return m;
    }

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

    [[nodiscard]] static auto XorredStats(const mockmon::Mockmon &m)
    {
        const auto &battleStats = m.CurrentBattleStats.m_battleStats;
        const auto xoredStats = std::accumulate(std::begin(battleStats), std::end(battleStats), 0, [](int xorred, const auto &p)
                                                { return xorred ^ static_cast<int>(p.second.GetBaseStat()); });
        return xoredStats;
    }

    /**
 * @brief Get the Move From Move Set object
 * teach a move to a mockmon
 * grab an iterator pointing to it as an equipped move so we can refill it's powerpoints
 * @param m 
 * @param mv 
 * @return auto 
 */
    [[nodiscard]] static auto TeachAndGetMoveFromMoveSet(mockmon::Mockmon &m, mockmon::moves::MoveId mv)
    {
        m.TeachMove(mv);
        auto &mvset = m.GetMoveSet();
        const auto pred{mockmon::MakePredicator<mockmon::moves::EquipedMove, mockmon::moves::MoveId>(mv)};
        auto match = std::find_if(std::begin(mvset), std::end(mvset), pred);
        return match;
    }

    [[nodiscard]] static const std::vector<double> JumpByOneStage()
    {
        return {1.5, 2.0, 2.5, 3.0, 3.5, 4.0};
    };

    [[nodiscard]] static const std::vector<double> JumpByTwoStages()
    {
        return {2.0, 3.0, 4.0};
    };

    [[nodiscard]] static const std::vector<double> FallByOneStage()
    {
        return {0.66, 0.50, 0.40, 0.33, 0.28, 0.25};
    };

    [[nodiscard]] static const std::vector<double> FallByTwoStages()
    {
        return {0.50, 0.33, 0.25};
    };
};