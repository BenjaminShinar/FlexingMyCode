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
    const auto [testedBadge, testedStat, x] = GENERATE(
        make_tuple(badges::IndigoBadge::Boulder_Badge, StatsTypes::Attack, 0.0),
        make_tuple(badges::IndigoBadge::Thunder_Badge, StatsTypes::Defence, 0.0),
        make_tuple(badges::IndigoBadge::Soul_Badge, StatsTypes::Speed, 0.0),
        make_tuple(badges::IndigoBadge::Volcano_Badge, StatsTypes::Special, 0.0));

    const auto badgeName{Stringify(testedBadge)};
    const auto statName{Stringify(testedStat)};

    GIVEN("an mockom belonging to a trainer")
    {
        Trainer t{"check"};
        Arena a{true};
        a.SetBadgeBoosts(t);

        THEN(AppendAll({"the trainer should not have the", badgeName, "badge", "or a boost to the", statName, "stat"}))
        {
            REQUIRE_FALSE(t.CheckBadge(testedBadge));
            const auto arenaBadgeBoost = a.GetBadgeBoost(t, testedStat);
            REQUIRE(arenaBadgeBoost == Approx(1.0).epsilon(0.001));
        }
        WHEN(AppendAll({"we give the trainer the", badgeName, "badge"}))
        {

            t.GiveBadge(testedBadge);
            THEN(AppendAll({"the trainer should have the", badgeName, "badge"}))
            {
                REQUIRE(t.CheckBadge(testedBadge));
                AND_THEN(AppendAll({"we should see differnce in the", statName, "stat"}))
                {
                    a.SetBadgeBoosts(t);
                    const auto arenaBadgeBoost = a.GetBadgeBoost(t, testedStat);
                    REQUIRE(arenaBadgeBoost == Approx(1.125).epsilon(0.001));
                    FAIL_CHECK("not implemnted to the entirely");
                }
            }
        }
    }
}

SCENARIO("Badge Boost Glitch", "[MockmonTest][Badge Boost][Gen 1 Glitch][!mayfail]")
{
    FAIL_CHECK("not implemnted");
}

SCENARIO("Badge Boost Glitch Reset at Level Up", "[MockmonTest][Badge Boost][Gen 1 Glitch][!mayfail]")
{
    FAIL_CHECK("not implemnted");
}

SCENARIO("Badge Boost Glitch Haze glitch", "[MockmonTest][Badge Boost][Gen 1 Glitch][!mayfail]")
{
    FAIL_CHECK("not implemnted");
}