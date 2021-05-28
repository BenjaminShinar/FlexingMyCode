#include "specialized_moves.h"
#include "moves_stats_targeting.h"
#include "random_gen.h"
#include "stats/stats.h"
#include "mockmon_conditions/all_conditions.h"

#include <functional>
#include <utility>
#include <math.h>
#include <algorithm>


namespace mockmon::moves
{
    using namespace std::placeholders; //import this for _1,_2,
    void CompositeMove::Perform(Arena &arena, Mockmon &attacker, Mockmon &defender) const
    {
        const auto o = MoveChance(arena,attacker,defender);
        if (o.m_hit)
        {
            for (auto &mv : MoveComponenets)
            {
                const auto outomce = mv(arena, Identifier(), attacker, defender);
                std::cout << outomce.m_moveOutcomeDescrition << '\n';
            }
        }
        else
        {
            std::cout << attacker.GetName() << " missed with " << Identifier() << '\n';
        }
    }


    //this probably belongs somewhere else
    condition::pulser_uq_ptr MakeCondition(condition::ConditionId conditionid,Mockmon & effectedMockmon)
    {
        using namespace condition;
        switch (conditionid)
        {
        case ConditionId::Poison:
            return std::make_unique<PoisonCondition>(effectedMockmon, 16.0);
            break;
        case ConditionId::Sleep:
            return std::make_unique<SleepCondition>(effectedMockmon, 3);
            break;
        case ConditionId::Burn:
            return std::make_unique<BurnCondition>(effectedMockmon, 16.0);
            break;
        case ConditionId::Paralysis:

            break;
        case ConditionId::Confusion:

            break;
        case ConditionId::Freeze:

            break;
        case ConditionId::Flinch:

            break;
        case ConditionId::Reflect:
            return std::make_unique<ReflectCondition>(effectedMockmon);
            break;
        case ConditionId::LightScreen:
            return std::make_unique<LightScreenCondition>(effectedMockmon);
            break;
        default:
            break;
        }
        std::cerr << __FUNCTION__ << " should never have reached this location!\n";
        return std::make_unique<EmptyCondition>();
    }

    //here are some other attacks, will eventually need refactoring


#pragma region move success Chances
   
    MoveOutcome RegularAccuracyCheckMove(Arena &arena, Mockmon &attacker, Mockmon &defender,int attackingMoveBaseAccuracy, const MovesTargeting & movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
        const auto [attackstat,defencestat] = battle::Battle::GetStatsModifier(attacker,targetingPair.AttackerStat,defender,targetingPair.DefenderStat);
        const auto modifier = attackstat*defencestat;
        const auto percentage = std::clamp(static_cast<int>(std::round(attackingMoveBaseAccuracy*modifier)),0,100);
        if (random::Randomer::CheckPercentage(percentage))
        {
            return MoveOutcome{"",true};
        }
        else
        {
            return MoveOutcome{"",false};
        }
    }

    MoveOutcome SetChancesCheckMove(Arena &arena, Mockmon &attacker, Mockmon &defender,int setChances)
    {
        if (random::Randomer::CheckPercentage(setChances))
        {
            return MoveOutcome{"",true};
        }
        else
        {
            return MoveOutcome{"",false};
        }
    }

    MoveOutcome BypassAccuracyCheckMove(Arena &arena, Mockmon &attacker, Mockmon &defender)
    {
        return MoveOutcome{"",true};
    }

#pragma endregion

#pragma region attacks

    MoveOutcome WasteTurnMove(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        MoveOutcome o{AppendAll({attacker.GetName(), "is", Stringify(attackingMoveId), "for current turn"})};
        return o;
    }

    MoveOutcome RegularMove(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender,const MovesTargeting & movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
        auto damage = static_cast<int>(battle::Battle::ModifyAttack(attackingMoveId, attacker,targetingPair.AttackerStat, defender,targetingPair.DefenderStat));
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome RecoilDamageMove(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, double divisionFactor)
    {
        auto damage = std::max(1, static_cast<int>(battle::Battle::ModifyAttack(attackingMoveId, attacker,StatsTypes::Attack, attacker,StatsTypes::Defence) / divisionFactor));
        attacker.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "takes", std::to_string(damage), "recoil damage from", Stringify(attackingMoveId)})};
        return o;
    }

    MoveOutcome ChangeSelfStatMove(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  attacker.CurrentBattleStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used",Stringify(attackingMoveId), "and changed stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome ChangeOpponentStatMove(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  defender.CurrentBattleStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "and changed", defender.GetName(),"stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome DirectDamageByPassResistance(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, double damage)
    {
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByTargetCalculation(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const ExDamageByState & dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(defender));
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByAttackerCalculation(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const ExDamageByState & dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(attacker));
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome AddConditionStatus(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const StatusInflicment statusConditionInflicment)
    {
        if (defender.GetMockmonSpeciesData().IsSpeciesOfType(statusConditionInflicment.moveType))
        {
            MoveOutcome o{AppendAll({defender.GetName(), "cant be efflicted with", Stringify(statusConditionInflicment.AfflicteCondition),"by",Stringify(attackingMoveId) })};    
            return o;
        }
        if (defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.AfflicteCondition))
        {
            //already afflicted
            MoveOutcome o{AppendAll({defender.GetName(), "is already", Stringify(statusConditionInflicment.AfflicteCondition),".",Stringify(attackingMoveId), "failed!"})};    
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.ChanceToAfflictCondtion))
        {
            defender.m_currentCondtion.CauseCondition(MakeCondition(statusConditionInflicment.AfflicteCondition,defender));
            if (defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.AfflicteCondition))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "!", defender.GetName(),"is now", Stringify(statusConditionInflicment.AfflicteCondition)})};
                return o;    
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(),"tried to use",Stringify(attackingMoveId), "but it failed to inflict condition",Stringify(statusConditionInflicment.AfflicteCondition)})};    
        return o;
    }

    MoveOutcome AddSelfConditionStatus(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const StatusInflicment statusConditionInflicment)
    {

        if (attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.AfflicteCondition))
        {
            //already afflicted
            MoveOutcome o{AppendAll({attacker.GetName(), "is already", Stringify(statusConditionInflicment.AfflicteCondition),".",Stringify(attackingMoveId), "failed!"})};    
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.ChanceToAfflictCondtion))
        {
            attacker.m_currentCondtion.CauseCondition(MakeCondition(statusConditionInflicment.AfflicteCondition,attacker));
            if (attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.AfflicteCondition))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "!", attacker.GetName(),"is now", Stringify(statusConditionInflicment.AfflicteCondition)})};
                return o;    
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(),"tried to use",Stringify(attackingMoveId), "but it failed to inflict condition",Stringify(statusConditionInflicment.AfflicteCondition)})};    
        return o;
    }

    void ResetAllStatChanges(Mockmon &effectedMockmon)
    {
        effectedMockmon.m_currentCondtion.RemoveAllConditions();
        for (auto & statsPair : effectedMockmon.CurrentBattleStats.m_battleStats)
        {
            statsPair.second.ResetBoost();
        }
    }
    
    MoveOutcome ResetSelfAllConditions(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        ResetAllStatChanges(attacker);
        MoveOutcome o{AppendAll({attacker.GetName(),"used",Stringify(attackingMoveId), "to reset all it's stats!"})};    
        return o;
    }

    MoveOutcome ResetOpponenetAllConditions(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        ResetAllStatChanges(defender);
        MoveOutcome o{AppendAll({attacker.GetName(),"used",Stringify(attackingMoveId), "to reset all of",defender.GetName(),"stats!"})};    
        return o;
    }

    MoveOutcome StoreSelfChargedMove(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender,const moves::MoveId storedMoveId)
    {
        attacker.m_currentCondtion.StoreChargedMove(storedMoveId);
        MoveOutcome o{AppendAll({attacker.GetName(),"used",Stringify(attackingMoveId), "to charge",Stringify(storedMoveId),"for next turn"})};    
        return o;
    }


#pragma endregion

#pragma region expossed Chances
    ExMoveChanceCheck CreateNormalAccuracyCheck(int moveBaseAccuracy,const MovesTargeting movesTargeting)
    {
        auto bounded = std::bind(&RegularAccuracyCheckMove, _1, _2, _3, moveBaseAccuracy, movesTargeting);
        return bounded;
    }

    ExMoveChanceCheck CreateSetAccuracyCheck(int setchances)
    {
        auto bounded = std::bind(&SetChancesCheckMove, _1, _2, _3, setchances);
        return bounded;
    }

    ExMoveChanceCheck CreateByPassAccuracyCheck()
    {
        auto bounded = std::bind(&BypassAccuracyCheckMove, _1, _2, _3);
        return bounded;
    }

#pragma endregion

#pragma region exposed methods

    ExMove CreateSelfStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto bounded = std::bind(&ChangeSelfStatMove, _1, _2, _3, _4,effectedStat, modifer);
        return bounded;
    }

    ExMove CreateOpponentStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto bounded = std::bind(&ChangeOpponentStatMove, _1, _2, _3, _4, effectedStat, modifer);
        return bounded;
    }

    ExMove CreateNormalRecoilDamagingMove(const double divFactor)
    {
        auto bounded = std::bind(&RecoilDamageMove, _1, _2, _3, _4, divFactor);
        return bounded;
    }

    ExMove CreateDirectDamagingMoveByPassImmunity(const double setDamage)
    {
        auto bounded = std::bind(&DirectDamageByPassResistance, _1, _2, _3, _4,setDamage);
        return bounded;
    }

    
    ExMove CreateDirectDamagingMoveTargetStateByPassImmunity(const ExDamageByState & dmgByStateCalc)
    {
        auto bounded = std::bind(&DirectDamageByTargetCalculation, _1, _2, _3, _4,dmgByStateCalc);
        return bounded;
    }

    ExMove CreateDirectDamagingMoveAttackerStateByPassImmunity(const ExDamageByState & dmgByStateCalc)
    {
        auto bounded = std::bind(&DirectDamageByAttackerCalculation, _1, _2, _3, _4, dmgByStateCalc);
        return bounded;
    }

    ExMove CreateNormalDamagingMove(const MovesTargeting movesTargeting)
    {
        auto bounded = std::bind(&RegularMove, _1, _2, _3, _4,movesTargeting);
        return bounded;
    }


    ExMove CreateOpponentConditionMove(const StatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&AddConditionStatus, _1, _2, _3, _4,statusConditionInflicment);
        return bounded;
    }

    ExMove CreateSelfConditionMove(const StatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&AddSelfConditionStatus, _1, _2, _3, _4,statusConditionInflicment);
        return bounded;
    }

    ExMove CreateResetSelfConditionMove()
    {
        auto bounded = std::bind(&ResetSelfAllConditions, _1, _2, _3, _4);
        return bounded;
    }

    ExMove CreateResetOpponentConditionMove()
    {
        auto bounded = std::bind(&ResetOpponenetAllConditions, _1, _2, _3, _4);
        return bounded;
    }

/**
 * @brief Create a Stored Move for a later turn
 * 
 * @param storedMove 
 * @return ExMove 
 */
    ExMove CreateStoredMove(const moves::MoveId storedMove)
    {
        auto bounded = std::bind(&StoreSelfChargedMove, _1, _2, _3, _4,storedMove);
        return bounded;
    }

/**
 * @brief Create a Wasted Turn Move object
 * A turn that nothing happens in it!
 * @return ExMove 
 */
    ExMove CreateWastedTurnMove()
    {
        auto bounded = std::bind(&WasteTurnMove, _1, _2, _3, _4);
        return bounded;
    }
#pragma endregion

}