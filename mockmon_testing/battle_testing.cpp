#include <catch2/catch.hpp>
#include "../mockmon/include/mockmon_data.h"
#include "../mockmon/include/battle.h"
#include "../mockmon/include/specialized_moves.h"
#include <cmath>
#include <algorithm>


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

SCENARIO( "damaging conditions", "[MockmonTest]" ) 
{
    using namespace::mockmon;
    using std::make_pair;
    const auto speciesId = MockmonSpeciesId::Mew;
    const auto testedCondition =GENERATE(condition::PulsingConditionId::Burn,condition::PulsingConditionId::Poison);
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

SCENARIO( "pulsing conditions change stats", "[MockmonTest]" ) 
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

SCENARIO( "light screen and reflect conditions", "[MockmonTest]" ) 
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