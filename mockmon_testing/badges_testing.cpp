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

SCENARIO("Base Badge Boost", "[MockmonTest][Badge Boost]")
{
    using std::make_tuple;
    const auto [testedBadge, testedStat, otherStat, expectedBoost] = GENERATE(
        make_tuple(badges::IndigoBadge::Boulder_Badge, StatsTypes::Attack, StatsTypes::Special, 1.125),
        make_tuple(badges::IndigoBadge::Thunder_Badge, StatsTypes::Defence, StatsTypes::Attack, 1.125),
        make_tuple(badges::IndigoBadge::Soul_Badge, StatsTypes::Speed, StatsTypes::Defence, 1.125),
        make_tuple(badges::IndigoBadge::Volcano_Badge, StatsTypes::Special, StatsTypes::Speed, 1.125));

    const auto badgeName{Stringify(testedBadge)};
    const auto statName{Stringify(testedStat)};

    GIVEN("an mockom belonging to a trainer")
    {
        Trainer t{"check"};
        Arena arena{true};
        arena.SetBadgeBoosts(t);
        Mockmon m{MockmonSpeciesId::Mew, "test mockmon"};
        MockmonTestUtils::BringMockmonToLevel(m, 50);
        m.SetCurrentTrainer(t.UniqueTrainerID);

        THEN(AppendAll({"the trainer should not have the", badgeName, "badge", "or a boost to the", statName, "stat"}))
        {
            REQUIRE_FALSE(t.CheckBadge(testedBadge));
            const auto arenaBadgeBoost = arena.GetBadgeBoost(t, testedStat);
            REQUIRE(arenaBadgeBoost == Approx(1.0).epsilon(0.001));
        }
        WHEN(AppendAll({"we give the trainer the", badgeName, "badge"}))
        {
            const auto [statBeforeBadge, otherStatBeforeBoost] = arena.GetStatsModifier(m, testedStat, m, otherStat);
            t.GiveBadge(testedBadge);
            THEN(AppendAll({"the trainer should have the", badgeName, "badge"}))
            {
                REQUIRE(t.CheckBadge(testedBadge));
                AND_THEN(AppendAll({"we should see differnce in the", statName, "stat"}))
                {
                    arena.SetBadgeBoosts(t);
                    const auto [statAfterBoost, otherStatAfterBoost] = arena.GetStatsModifier(m, testedStat, m, otherStat);
                    const auto arenaBadgeBoostAfter = arena.GetBadgeBoost(t, testedStat);
                    REQUIRE(arenaBadgeBoostAfter == Approx(expectedBoost).epsilon(0.001));
                    REQUIRE(statAfterBoost == Approx(expectedBoost * statBeforeBadge));
                    REQUIRE(otherStatAfterBoost == Approx(otherStatBeforeBoost));
                }
            }
        }
    }
}

SCENARIO("Badge Boost Glitch", "[MockmonTest][Badge Boost][StatModifiers][Gen 1 Glitch]")
{

    using std::make_tuple;
    const auto [testedBadge, testedStat, otherStat, expectedBoost] = GENERATE(
        make_tuple(badges::IndigoBadge::Boulder_Badge, StatsTypes::Attack, StatsTypes::Special, 1.125),
        make_tuple(badges::IndigoBadge::Thunder_Badge, StatsTypes::Defence, StatsTypes::Attack, 1.125),
        make_tuple(badges::IndigoBadge::Soul_Badge, StatsTypes::Speed, StatsTypes::Defence, 1.125),
        make_tuple(badges::IndigoBadge::Volcano_Badge, StatsTypes::Special, StatsTypes::Speed, 1.125));

    const auto boostingMove{moves::MoveId::DoubleTeam};

    const auto badgeName{Stringify(testedBadge)};
    const auto statName{Stringify(testedStat)};
    const auto boostingMoveName{Stringify(boostingMove)};

    GIVEN("an mockom belonging to a trainer")
    {
        Trainer t{"check"};
        Arena arena{true};
        arena.SetBadgeBoosts(t);
        Mockmon ma{MockmonSpeciesId::Mew, "test mockmon"};
        Mockmon mb{MockmonSpeciesId::Mew, "other test mockmon"};
        MockmonTestUtils::BringMockmonToLevel(ma, 50);
        ma.SetCurrentTrainer(t.UniqueTrainerID);
        ma.TeachMove(boostingMove);

        WHEN(AppendAll({"we give the trainer the", badgeName, "badge", "and the mockmon uses", boostingMoveName, "to boost a different stat"}))
        {
            const auto [statBeforeBadge, otherStatBeforeBoost] = arena.GetStatsModifier(ma, testedStat, ma, otherStat);
            t.GiveBadge(testedBadge);
            arena.SetBadgeBoosts(t);
            battle::AttackWith(arena, boostingMove, ma, mb);

            THEN(AppendAll({"the mockmon", statName, "should have been boosted beyond the normal boost"}))
            {
                const auto [statAfterBoost, otherStatAfterBoost] = arena.GetStatsModifier(ma, testedStat, ma, otherStat);
                REQUIRE(statAfterBoost == Approx(expectedBoost * expectedBoost * statBeforeBadge));
                REQUIRE(otherStatAfterBoost == Approx(otherStatBeforeBoost));
            }
        }
    }
}

SCENARIO("Badge Boost Glitch Reset at Level Up", "[MockmonTest][Badge Boost][StatModifiers][Gen 1 Glitch][!mayfail]")
{
    FAIL_CHECK("not implemnted");
}

SCENARIO("Badge Boost Glitch Haze glitch", "[MockmonTest][Badge Boost][StatModifiers][Gen 1 Glitch][!mayfail]")
{
    FAIL_CHECK("not implemnted");
}