#include <catch2/catch.hpp>
#include "mockmon_test_utils.h"
#include "../mockmon/include/battle.h"
#include "../mockmon/include/specialized_moves.h"
#include "../mockmon/include/moves_stats_targeting.h"
#include "../mockmon/include/interfaces.h"

#include <cmath>
#include <algorithm>
#include <set>

using namespace ::mockmon;
using std::make_tuple;
const auto mewSpeciesName{Stringify(MockmonTestUtils::mewSpeciesId)};

/**
 * @brief 
 * verify that conditions can't be afflicted against certien types
 * can't burn file
 * cant freeze ice
 * electric shock cant electric
 * electric shock cant paralyze ground
 * lick cant paralyze ghost
 * normal body slam cant paralyze normal mockmons
 * cant poison poision types
 * cant poison steel types with poison attacks, but can with bug?
 * cant leechseeed grass mockmon
 * we need an attacking mockmon with the correct attack
 * it needs to attack a mockmon that can either be effected or cant be
 * we verify afterwards the effect is in place
 * move(which causes status) x target  = status?
 * it might be best if the defending mockmon is at a high level so it won't faint
 * 
 * 
 */
SCENARIO("Conditions Immunities", "[MockmonTest][BattleTest][Condition]")
{
    const auto expectedEnemyLevel{50};

    const auto [testedCondition, statusMove, targetedSpeices, shouldBeEffected, nAttempts] = GENERATE(
        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::ThunderWave, MockmonSpeciesId::Weedle, true, 5),
        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::ThunderWave, MockmonSpeciesId::Pikachu, false, 5),
        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::ThunderWave, MockmonSpeciesId::Geodude, false, 5),

        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::BodySlam, MockmonSpeciesId::Geodude, true, 500),
        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::BodySlam, MockmonSpeciesId::Rattata, false, 500),

        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::Lick, MockmonSpeciesId::Rattata, true, 500),
        make_tuple(condition::PulsingConditionId::Paralysis, moves::MoveId::Lick, MockmonSpeciesId::Gastly, false, 500),

        make_tuple(condition::PulsingConditionId::Freeze, moves::MoveId::IceBeam, MockmonSpeciesId::Rattata, true, 500),
        make_tuple(condition::PulsingConditionId::Freeze, moves::MoveId::IceBeam, MockmonSpeciesId::Lapras, false, 500),
        make_tuple(condition::PulsingConditionId::Burn, moves::MoveId::Ember, MockmonSpeciesId::Rattata, true, 500),
        make_tuple(condition::PulsingConditionId::Burn, moves::MoveId::Ember, MockmonSpeciesId::Vulpix, false, 500),
        make_tuple(condition::PulsingConditionId::Poison, moves::MoveId::PoisonPowder, MockmonSpeciesId::Mew, true, 5),
        make_tuple(condition::PulsingConditionId::Poison, moves::MoveId::PoisonPowder, MockmonSpeciesId::Weedle, false, 5));

    GIVEN(AppendAll({"an enemy mockmon of type", Stringify(targetedSpeices)}))
    {
        Arena a{true};
        auto ma{MockmonTestUtils::CreateTestMockmon("attacker")};

        auto mb{MockmonTestUtils::CreateTestMockmon("defender", targetedSpeices, expectedEnemyLevel)};
        auto match = MockmonTestUtils::TeachAndGetMoveFromMoveSet(ma, statusMove);
        WHEN(AppendAll({"it's attacked by", Stringify(statusMove), "to inflict", Stringify(testedCondition)}))
        {
            bool currentlyEffected{false}; //enemy was not effected

            for (auto i = 0; i < nAttempts && !currentlyEffected; ++i)
            {
                battle::AttackWith(a, statusMove, ma, mb);

                currentlyEffected |= mb.m_currentCondtion.IsAffiliatedWithCondition(testedCondition);
                ma.FullRestore();
                mb.FullRestore();
                match->RefillPowerPoints();
            }
            std::string shouldStr;
            if (shouldBeEffected)
            {
                shouldStr = "it should be effected";
            }
            else
            {
                shouldStr = "it should not be effected";
            }
            THEN(shouldStr)
            {
                REQUIRE(currentlyEffected == shouldBeEffected);
            }
        }
    }
}

SCENARIO("damaging conditions", "[MockmonTest][Condition]")
{
    const auto testedCondition = GENERATE(condition::PulsingConditionId::Burn, condition::PulsingConditionId::Poison);
    const auto [expectedLevel, expectedMaxHP, turnToLast] = GENERATE(
        make_tuple(1u, 13, 12),
        make_tuple(3u, 19, 18),
        make_tuple(15, 55, 18),
        make_tuple(90u, 282, 16));
    const auto conditionName{Stringify(testedCondition)};
    GIVEN(AppendAll({"A Normal Healthy level", std::to_string(expectedLevel), mewSpeciesName}))
    {
        auto ma{MockmonTestUtils::CreateTestMockmon(Stringify(testedCondition), MockmonTestUtils::mewSpeciesId, expectedLevel)};
        THEN(AppendAll({"it must be healthy and have", std::to_string(expectedMaxHP), "max hp"}))
        {
            REQUIRE(ma.IsAbleToBattle());
            REQUIRE(ma.GetCurrentLevel() == expectedLevel);
            auto maxHealth = ma.CurrentBattleStats.Health.GetMaxStat();
            auto currentHealth = ma.CurrentBattleStats.Health.GetStat();
            REQUIRE(maxHealth == currentHealth);
            REQUIRE(maxHealth == expectedMaxHP);

            AND_WHEN("It's effected by" + conditionName)
            {
                ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition, ma));
                THEN("it must be effected by" + conditionName)
                {
                    REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                    AND_WHEN("turns pass")
                    {
                        for (auto i = 0; i < turnToLast; ++i)
                        {
                            ma.m_currentCondtion.PulseBeforeTurn();
                            ma.m_currentCondtion.PulseAfterTurn();
                        }
                        THEN("it must still be alive")
                        {
                            REQUIRE(ma.IsAbleToBattle());
                            AND_WHEN("one more turn passes")
                            {
                                ma.m_currentCondtion.PulseBeforeTurn();
                                ma.m_currentCondtion.PulseAfterTurn();

                                THEN("it should be fainted")
                                {
                                    REQUIRE(ma.CurrentBattleStats.Health.GetStat() == 0);
                                    REQUIRE_FALSE(ma.IsAbleToBattle());
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

SCENARIO("pulsing conditions change stats", "[MockmonTest][Condition][StatModifiers]")
{
    const auto [testedCondition, effectedStat, factor] = GENERATE(
        make_tuple(condition::PulsingConditionId::Burn, StatsTypes::Attack, 0.5),
        make_tuple(condition::PulsingConditionId::Paralysis, StatsTypes::Speed, 0.25));
    GIVEN("A Normal Healthy mockmon")
    {
        Arena arena{true};
        auto ma{MockmonTestUtils::CreateTestMockmon(Stringify(testedCondition), MockmonTestUtils::mewSpeciesId)};
        const auto [baseAttackStat, baseDefencestat] = arena.GetStatsModifier(ma, effectedStat, ma, effectedStat);

        THEN("it must be the same stats")
        {
            REQUIRE_FALSE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
            REQUIRE(baseAttackStat == Approx(baseDefencestat));
        }
        WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition, ma));
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));

                AND_THEN("it must have it's stats change")
                {
                    const auto [attackstat, defencestat] = arena.GetStatsModifier(ma, effectedStat, ma, effectedStat);
                    REQUIRE(attackstat == Approx(baseAttackStat * factor));
                }
            }
        }
    }
}

SCENARIO("pulsing conditions must go away on thier own a max amount of turn", "[MockmonTest][condition]")
{

    const auto [testedCondition, maxTurns] = GENERATE(
        make_tuple(condition::PulsingConditionId::Sleep, 10),
        make_tuple(condition::PulsingConditionId::Confusion, 10));
    GIVEN("A Normal Healthy mockmon")
    {
        auto ma{MockmonTestUtils::CreateTestMockmon(Stringify(testedCondition), MockmonTestUtils::mewSpeciesId)};

        WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition, ma));
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_WHEN("turns pass")
                {
                    for (auto i = 0; i < maxTurns; ++i)
                    {
                        ma.m_currentCondtion.PulseBeforeTurn();
                        ma.m_currentCondtion.PulseAfterTurn();
                    }
                    THEN("it must be free of the condition")
                    {
                        REQUIRE_FALSE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                    }
                }
            }
        }
    }
}

SCENARIO("pulsing conditions go away on thier own in a random matter", "[MockmonTest][Condition]")
{
    const auto loops{50000}; //how many times each
    const auto [testedCondition, maxTurns, expectedRecovery, expectedMargin] = GENERATE(
        make_tuple(condition::PulsingConditionId::Sleep, 1, 0.2, 0.1),
        make_tuple(condition::PulsingConditionId::Sleep, 2, 0.4, 0.1),
        make_tuple(condition::PulsingConditionId::Sleep, 3, 0.6, 0.1),
        make_tuple(condition::PulsingConditionId::Sleep, 4, 0.8, 0.1),
        make_tuple(condition::PulsingConditionId::Sleep, 5, 0.9, 0.05),
        make_tuple(condition::PulsingConditionId::Sleep, 6, 0.95, 0.05),
        make_tuple(condition::PulsingConditionId::Sleep, 7, 0.975, 0.025),
        make_tuple(condition::PulsingConditionId::Sleep, 8, 1.0, 0.01));
    GIVEN("A Normal Healthy mockmon")
    {
        auto ma{MockmonTestUtils::CreateTestMockmon(Stringify(testedCondition), MockmonTestUtils::mewSpeciesId)};
        WHEN("It's effected by the condition many times")
        {
            auto timesRecovered{0.0};
            for (auto l = 0; (l < loops); ++l)
            {
                ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition, ma));
                for (auto x = 0; x < maxTurns; ++x)
                {
                    ma.m_currentCondtion.PulseBeforeTurn();
                    ma.m_currentCondtion.PulseAfterTurn();
                }
                if (!ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition))
                {
                    ++timesRecovered;
                }
                ma.m_currentCondtion.RemovePulsingCondition(testedCondition);
            }
            THEN("it have spontanously recovered about ")
            {
                REQUIRE_THAT((timesRecovered / loops), Catch::Matchers::WithinAbs(expectedRecovery, expectedMargin));
            }
        }
    }
}

SCENARIO("light screen and reflect conditions", "[MockmonTest][Condition][StatModifiers]")
{
    const auto [testedCondition, effectedStat, factor] = GENERATE(
        make_tuple(condition::NonPulsingConditionId::Reflect, StatsTypes::Defence, 2.0),
        make_tuple(condition::NonPulsingConditionId::LightScreen, StatsTypes::Special, 2.0));
    GIVEN("A Normal Healthy mockmon")
    {
        Arena arena{true};
        auto ma{MockmonTestUtils::CreateTestMockmon(Stringify(testedCondition), MockmonTestUtils::mewSpeciesId)};
        const auto [baseAttackStat, baseDefencestat] = arena.GetStatsModifier(ma, effectedStat, ma, effectedStat);

        THEN("it must be the same stats")
        {
            REQUIRE_FALSE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
            REQUIRE(baseAttackStat == Approx(baseDefencestat));
        }
        AND_WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CauseNonPulsingCondition(testedCondition);
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_THEN("it must have it's stats change")
                {
                    const auto [attackstat, defencestat] = arena.GetStatsModifier(ma, effectedStat, ma, effectedStat);
                    REQUIRE_FALSE(attackstat == Approx(defencestat));
                    REQUIRE(defencestat == Approx(baseDefencestat * factor));
                }
            }
        }
    }
}

SCENARIO("confusion", "[MockmonTest][Condition]")
{

    const auto testedCondition = GENERATE(condition::PulsingConditionId::Confusion);
    const auto expectedLevel = GENERATE(1u, 20u, 30u);
    const auto attempts{50};
    GIVEN("A Normal Healthy mockmon")
    {

        auto ma{MockmonTestUtils::CreateTestMockmon("confused attacker", MockmonTestUtils::mewSpeciesId, expectedLevel)};
        auto mb{MockmonTestUtils::CreateTestMockmon("target", MockmonTestUtils::mewSpeciesId, expectedLevel)};
        const auto maxHealth = ma.CurrentBattleStats.Health.GetMaxStat();

        THEN("it must be healthy")
        {
            REQUIRE(ma.IsAbleToBattle());
            REQUIRE(ma.GetCurrentLevel() == expectedLevel);
            auto currentHealth = ma.CurrentBattleStats.Health.GetStat();
            REQUIRE(maxHealth == currentHealth);
        }
        WHEN("It's effected by the condition")
        {

            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition, ma));
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_WHEN("it attackes the enemy several times")
                {
                    Arena arena{true};
                    const auto attackingmove{moves::MoveId::Swift};
                    auto match = MockmonTestUtils::TeachAndGetMoveFromMoveSet(ma, attackingmove);
                    for (auto i = 0; i < attempts && ma.IsAbleToBattle(); ++i)
                    {
                        battle::AttackWith(arena, attackingmove, ma, mb);
                        match->RefillPowerPoints();
                        mb.FullRestore();
                        if (!ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition))
                        {
                            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition, ma));
                        }
                    }
                    THEN("it should have hit itself in confusion at least once")
                    {
                        auto health = ma.CurrentBattleStats.Health.GetStat();
                        REQUIRE(health < maxHealth);
                    }
                }
            }
        }
    }
}