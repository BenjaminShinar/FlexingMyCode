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

SCENARIO("Battle test", "[MockmonTest][BattleTest]")
{
    const auto speciesId = MockmonSpeciesId::Mew;
    GIVEN("two mews mockmon engaging in a battle")
    {
        Mockmon ma(speciesId, "mew A");
        Mockmon mb(speciesId, "mew B");
        WHEN("they engage in battle")
        {
            battle::Battle::DoBattle(TrainerAI::RandomChoice, ma, TrainerAI::RandomChoice, mb);
            THEN("One must fall")
            {
                REQUIRE(ma.IsAbleToBattle() ^ mb.IsAbleToBattle());
            }
        }
    }
}

SCENARIO("damage ranges test", "[MockmonTest][BattleTest][!mayfail]")
{
    using std::make_tuple;
    const auto speciesId = MockmonSpeciesId::Mew;

    const auto [usedMove, movesTargeting, requiredLevel, expectedValuesCount, minDamage, maxDamage] = GENERATE(
        make_tuple(moves::MoveId::Slash, moves::MovesTargeting::PurePhysical, 100, 16u, 98, 116),
        make_tuple(moves::MoveId::KarateChop, moves::MovesTargeting::PurePhysical, 100, 8u, 37, 44),
        make_tuple(moves::MoveId::RazorLeaf, moves::MovesTargeting::PureSpecial, 100, 16u, 78, 92),
        make_tuple(moves::MoveId::Crabhammer, moves::MovesTargeting::PureSpecial, 100, 16u, 126, 149));

    const auto attempts = 100000;

    GIVEN("two mews mockmon engaging in a battle")
    {
        Mockmon ma(speciesId, "mew A");
        Mockmon mb(speciesId, "mew B");
        MockmonTestUtils::BringMockmonToLevel(ma, requiredLevel);
        MockmonTestUtils::BringMockmonToLevel(mb, requiredLevel);

        WHEN(std::string("we calculate damage 10000 times for ") + Stringify(usedMove))
        {
            std::set<int> damageRanges;
            const auto targetingPair{moves::MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
            for (auto i = 0; i < attempts; ++i)
            {
                auto damage = static_cast<int>(battle::ModifyAttack(usedMove, ma, targetingPair.AttackerStat, mb, targetingPair.DefenderStat));

                damageRanges.insert(damage);
            }
            THEN("there must be the correct amounts possible damage values")
            {
                const auto mnmx = std::minmax_element(std::begin(damageRanges), std::end(damageRanges));
                CHECK(damageRanges.size() == expectedValuesCount);
                //TODO: fix damage ranges?
                CHECK(*mnmx.first == minDamage);
                CHECK(*mnmx.second == maxDamage);
            }
        }
    }
}

SCENARIO("Self Boosting Stat Modifier moves", "[MockmonTest][BattleTest][StatModifiers]")
{
    using std::make_tuple;

    const auto speciesId = MockmonSpeciesId::Mew;
    const auto requiredLevel{50};
    const auto [boostingMove, effectedStat, expectedDifferncesFactors] = GENERATE(
        make_tuple(moves::MoveId::Sharpen, StatsTypes::Attack, MockmonTestUtils::JumpByOneStage()),
        make_tuple(moves::MoveId::SwordsDance, StatsTypes::Attack, MockmonTestUtils::JumpByTwoStages()),
        make_tuple(moves::MoveId::DefenseCurl, StatsTypes::Defence, MockmonTestUtils::JumpByOneStage()),
        make_tuple(moves::MoveId::Harden, StatsTypes::Defence, MockmonTestUtils::JumpByOneStage()),
        make_tuple(moves::MoveId::AcidArmor, StatsTypes::Defence, MockmonTestUtils::JumpByTwoStages()),
        make_tuple(moves::MoveId::Barrier, StatsTypes::Defence, MockmonTestUtils::JumpByTwoStages()),
        make_tuple(moves::MoveId::Withdraw, StatsTypes::Defence, MockmonTestUtils::JumpByTwoStages()),
        make_tuple(moves::MoveId::Agility, StatsTypes::Speed, MockmonTestUtils::JumpByTwoStages()),
        make_tuple(moves::MoveId::Growth, StatsTypes::Special, MockmonTestUtils::JumpByOneStage()),
        make_tuple(moves::MoveId::Amnesia, StatsTypes::Special, MockmonTestUtils::JumpByTwoStages()),
        make_tuple(moves::MoveId::DoubleTeam, StatsTypes::Evasion, MockmonTestUtils::JumpByOneStage()),
        make_tuple(moves::MoveId::Minimize, StatsTypes::Evasion, MockmonTestUtils::JumpByOneStage()));

    const auto boostingMoveName{Stringify(boostingMove)};
    const auto effectedStatName{Stringify(effectedStat)};
    GIVEN("two mockmon engaging in a battle")
    {
        Arena arena{true};
        Mockmon ma(speciesId, "mew A");
        ma.TeachMove(boostingMove);
        MockmonTestUtils::BringMockmonToLevel(ma, requiredLevel);

        Mockmon mb(speciesId, "mew B");
        MockmonTestUtils::BringMockmonToLevel(mb, requiredLevel);

        const auto [statBeforeBoost, _] = arena.GetStatsModifier(ma, effectedStat, ma, effectedStat);

        WHEN(AppendAll({"the attacker uses", boostingMoveName, "to increas it's", effectedStatName}))
        {
            battle::AttackWith(arena, boostingMove, ma, mb);

            THEN(AppendAll({"The", effectedStatName, "of the attacker Should be multiply by a factor of"}))
            {
                const auto [statAfterBoost, _] = arena.GetStatsModifier(ma, effectedStat, ma, effectedStat);
                REQUIRE(statAfterBoost == Approx(statBeforeBoost * expectedDifferncesFactors.front()));
            }
        }
    }
}

SCENARIO("One Hit Ko Moves", "[MockmonTest][BattleTest]")
{
    using std::make_tuple;
    const auto attackerSpeciesId = MockmonSpeciesId::Mew;

    const auto [attackerLevel, ohkoMove, targetedSpeices] = GENERATE(
        make_tuple(50, moves::MoveId::Fissure, MockmonSpeciesId::Mew),
        make_tuple(50, moves::MoveId::Guillotine, MockmonSpeciesId::Mew),
        make_tuple(50, moves::MoveId::HornDrill, MockmonSpeciesId::Mew));
    const auto [expectedEnemyLevel, shouldSurvive, nAttempts] = GENERATE(
        make_tuple(25, false, 50),  //success
        make_tuple(75, true, 500)); //always fail

    const auto attackerTypeName{Stringify(attackerSpeciesId)};

    const auto enemyTypeName{Stringify(targetedSpeices)};
    const auto ohkoMoveName{Stringify(ohkoMove)};
    GIVEN(AppendAll({"an enemy mockmon of type", enemyTypeName}))
    {
        Arena a{true};
        Mockmon ma(attackerSpeciesId, AppendAll({"attacker", attackerTypeName, "level", std::to_string(attackerLevel)}));
        MockmonTestUtils::BringMockmonToLevel(ma, attackerLevel);

        ma.TeachMove(ohkoMove);
        Mockmon mb(targetedSpeices, AppendAll({"defender", enemyTypeName, "level", std::to_string(expectedEnemyLevel)}));
        MockmonTestUtils::BringMockmonToLevel(mb, expectedEnemyLevel);

        auto &mvset = ma.GetMoveSet();
        const auto pred{MakePredicator<moves::EquipedMove, moves::MoveId>(ohkoMove)};
        auto match = std::find_if(std::begin(mvset), std::end(mvset), pred);
        WHEN(AppendAll({"it's attacked by", ohkoMoveName}))
        {
            bool enemySurvived{true}; //enemy was not effected

            for (auto i = 0; i < nAttempts && enemySurvived; ++i)
            {
                battle::AttackWith(a, ohkoMove, ma, mb);

                enemySurvived = mb.IsAbleToBattle();
                ma.FullRestore();
                mb.FullRestore();
                match->RefillPowerPoints();
            }
            std::string shouldStr;
            if (shouldSurvive)
            {
                shouldStr = "it should survive";
            }
            else
            {
                shouldStr = "it should be KOed";
            }
            THEN(shouldStr)
            {
                REQUIRE(enemySurvived == shouldSurvive);
            }
        }
    }
}