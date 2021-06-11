#include <catch2/catch.hpp>
#include "mockmon_test_utils.h"
#include "../mockmon/include/battle.h"
#include "../mockmon/include/specialized_moves.h"
#include "../mockmon/include/moves_stats_targeting.h"

#include <cmath>
#include <algorithm>
#include <set>


SCENARIO( "Battle test", "[MockmonTest]" ) 
{
    using namespace::mockmon;
    const auto speciesId = MockmonSpeciesId::Mew;
    GIVEN("two mews mockmon engaging in a battle")
    {
        Mockmon ma(speciesId,"mew A");
        Mockmon mb(speciesId,"mew B");
        WHEN("they engage in battle")
        {
            battle::Battle::DoBattle(ma,mb);
            THEN("One must fall")
            {
                REQUIRE(ma.IsAbleToBattle() ^ mb.IsAbleToBattle());
            }
        }

    }
}

SCENARIO( "damage ranges test", "[MockmonTest][!mayfail]" ) 
{
    using namespace::mockmon;
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
        Mockmon ma(speciesId,"mew A");
        Mockmon mb(speciesId,"mew B");
        MockmonTestUtils::BringMockmonToLevel(ma,requiredLevel);
        MockmonTestUtils::BringMockmonToLevel(mb,requiredLevel);


        WHEN(std::string("we calculate damage 10000 times for ")+Stringify(usedMove))
        {
            std::set<int> damageRanges;
            const auto targetingPair{moves::MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
            for (auto i =0;i<attempts; ++i)
            {
                auto damage = static_cast<int>(battle::Battle::ModifyAttack(usedMove, ma,targetingPair.AttackerStat, mb,targetingPair.DefenderStat));

                damageRanges.insert(damage);
            }
            THEN("there must be the correct amounts possible damage values")
            {
                const auto mnmx = std::minmax_element(std::begin(damageRanges),std::end(damageRanges));
                CHECK(damageRanges.size() == expectedValuesCount);
                //TODO: fix damage ranges?
                CHECK(*mnmx.first == minDamage); 
                CHECK(*mnmx.second == maxDamage);
            }
        }

    }
}

SCENARIO( "damaging conditions", "[MockmonTest][condition]" ) 
{
    using namespace::mockmon;
    using std::make_pair;
    const auto speciesId = MockmonSpeciesId::Mew;
    const auto testedCondition = GENERATE(condition::PulsingConditionId::Burn, condition::PulsingConditionId::Poison);
    const auto [expectedLevel, turnToLast] = GENERATE(
        make_pair(1u, 12),
        make_pair(3u, 14),
        make_pair(90u, 16));
    GIVEN("A Normal Healthy mockmon")
    {
        
        Mockmon ma(speciesId,AppendAll({Stringify(speciesId),"level",std::to_string(expectedLevel)}));
        MockmonTestUtils::BringMockmonToLevel(ma,expectedLevel);
        THEN("it must be healthy")
        {
            REQUIRE(ma.IsAbleToBattle());
            REQUIRE(ma.GetCurrentLevel()==expectedLevel);
            auto maxHealth = ma.CurrentBattleStats.Health.GetMaxStat();
            auto currentHealth = ma.CurrentBattleStats.Health.GetStat();
            REQUIRE(maxHealth==currentHealth);
        }
        WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition,ma));
            THEN("it must be effected by the conditions")
            {
              REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_WHEN("turns pass")
                {
                    for (auto i=0;i<turnToLast;++i)
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
                            REQUIRE(ma.CurrentBattleStats.Health.GetStat()==0);
                            REQUIRE_FALSE(ma.IsAbleToBattle());
                        }
                    }
                    }
                    
                }
            }
        }

    }
}

SCENARIO( "pulsing conditions change stats", "[MockmonTest][condition]" ) 
{
    using namespace::mockmon;
    using std::make_tuple;
    const auto speciesId = MockmonSpeciesId::Mew;
    const auto [testedCondition,effectedStat,factor] = GENERATE(make_tuple(condition::PulsingConditionId::Burn,StatsTypes::Attack,0.5),
                    make_tuple(condition::PulsingConditionId::Paralysis,StatsTypes::Speed,0.25));
    GIVEN("A Normal Healthy mockmon")
    {
        Mockmon ma(speciesId,AppendAll({Stringify(speciesId),"condition",Stringify(testedCondition)}));
        const auto [baseAttackStat,baseDefencestat] = battle::Battle::GetStatsModifier(ma,effectedStat,ma,effectedStat);

        THEN("it must be the same stats")
        {
                REQUIRE_FALSE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                REQUIRE(baseAttackStat ==  Approx(baseDefencestat));
        }
        WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition,ma));
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));

                AND_THEN("it must have it's stats change")
                {
                const auto [attackstat,defencestat] = battle::Battle::GetStatsModifier(ma,effectedStat,ma,effectedStat);
                REQUIRE(attackstat == Approx(baseAttackStat*factor));
                }
            }
        }
    }
}

SCENARIO( "pulsing conditions must go away on thier own a max amount of turn", "[MockmonTest][condition]" )
{
    using namespace ::mockmon;
    using std::make_tuple;
    const auto speciesId = MockmonSpeciesId::Mew;
    const auto [testedCondition, maxTurns] = GENERATE(
        make_tuple(condition::PulsingConditionId::Sleep, 10),
        make_tuple(condition::PulsingConditionId::Confusion, 10));
    GIVEN("A Normal Healthy mockmon")
    {
        Mockmon ma(speciesId,AppendAll({Stringify(speciesId),"condition",Stringify(testedCondition)}));

        WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition,ma));
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_WHEN("turns pass")
                {
                    for (auto i=0;i<maxTurns;++i)
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

SCENARIO( "pulsing conditions go away on thier own in a random matter", "[MockmonTest][condition]" ) 
{
    using namespace::mockmon;
    using std::make_tuple;
    const auto speciesId = MockmonSpeciesId::Mew;
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
        Mockmon ma(speciesId,AppendAll({Stringify(speciesId),"condition",Stringify(testedCondition)}));

        WHEN("It's effected by the condition many times")
        {
            auto timesRecovered {0.0};
            for (auto l=0; (l<loops); ++l)
            {
                ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition,ma));
                for (auto x=0;x<maxTurns;++x)
                {
                    ma.m_currentCondtion.PulseBeforeTurn();
                    ma.m_currentCondtion.PulseAfterTurn();                }
                if (!ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition))
                {
                    ++timesRecovered;
                }
                ma.m_currentCondtion.RemovePulsingCondition(testedCondition);

            }
            THEN("it have spontanously recovered about ")
            {
                REQUIRE_THAT((timesRecovered/loops),Catch::Matchers::WithinAbs(expectedRecovery,expectedMargin));
            }
        }
    }
}

SCENARIO( "light screen and reflect conditions", "[MockmonTest][condition]" ) 
{
    using namespace::mockmon;
    using std::make_tuple;
    const auto speciesId = MockmonSpeciesId::Mew;
    const auto [testedCondition,effectedStat,factor]  = GENERATE(make_tuple(condition::NonPulsingConditionId::Reflect,StatsTypes::Defence,2.0),make_tuple(condition::NonPulsingConditionId::LightScreen,StatsTypes::Special,2.0));
    GIVEN("A Normal Healthy mockmon")
    {
        Mockmon ma(speciesId,AppendAll({Stringify(speciesId),"condition",Stringify(testedCondition)}));
        const auto [baseAttackStat,baseDefencestat] = battle::Battle::GetStatsModifier(ma,effectedStat,ma,effectedStat);

        THEN("it must be the same stats")
        {
                REQUIRE_FALSE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                REQUIRE(baseAttackStat ==  Approx(baseDefencestat));
        }
        AND_WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CauseNonPulsingCondition(testedCondition);
            THEN("it must be effected by the conditions")
            {
                REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_THEN("it must have it's stats change")
                {
                    const auto [attackstat,defencestat] = battle::Battle::GetStatsModifier(ma,effectedStat,ma,effectedStat);
                    REQUIRE_FALSE(attackstat == Approx(defencestat));
                    REQUIRE(defencestat == Approx(baseDefencestat*factor));
                }
            }
        }
    }
}

/*
SCENARIO( "confusion", "[MockmonTest][condition]" ) 
{
    using namespace::mockmon;
    using std::make_pair;
    const auto speciesId = MockmonSpeciesId::Mew;
    const auto testedCondition =GENERATE(condition::PulsingConditionId::Confusion);
    const auto [expectedLevel,turnToLast]  = GENERATE(make_pair(1u,12),make_pair(3u,14),make_pair(90u,16));
    GIVEN("A Normal Healthy mockmon")
    {
        
        Mockmon ma(speciesId,AppendAll({Stringify(speciesId),"level",std::to_string(expectedLevel)}));
        const auto levelUpGroup = ma.GetMockmonSpeciesData().SpeciesLevelUpGroup;
        ma.GrantExperiencePoints(MockmonExp::TotalExperinceForLevel(expectedLevel,levelUpGroup));
        ma.FullRestore();
        THEN("it must be healthy")
        {
            REQUIRE(ma.IsAbleToBattle());
            REQUIRE(ma.GetCurrentLevel()==expectedLevel);
            auto maxHealth = ma.CurrentBattleStats.Health.GetMaxStat();
            auto currentHealth = ma.CurrentBattleStats.Health.GetStat();
            REQUIRE(maxHealth==currentHealth);
        }
        WHEN("It's effected by the condition")
        {
            ma.m_currentCondtion.CausePulsingCondition(moves::MakeCondition(testedCondition,ma));
            THEN("it must be effected by the conditions")
            {
              REQUIRE(ma.m_currentCondtion.IsAffiliatedWithCondition(testedCondition));
                AND_WHEN("turns pass")
                {
                    for (auto i=0;i<turnToLast;++i)
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
                                REQUIRE(ma.CurrentBattleStats.Health.GetStat()==0);
                                REQUIRE_FALSE(ma.IsAbleToBattle());
                            }
                        }
                    }
                }
            }
        }

    }
}
*/