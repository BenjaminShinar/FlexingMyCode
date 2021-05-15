#include "specialized_moves.h"
#include "moves_stats_targeting.h"
#include "random_gen.h"
#include "mockmon_conditions/poison_conditon_pulse.h"
#include "mockmon_conditions/sleep_condition_pulse.h"
#include <functional>
#include <utility>
#include <math.h>


namespace mockmon::moves
{
    using namespace std::placeholders; //import this for _1,_2,

    void CompositeMove::Perform(Arena &arena, Mockmon &attacker, Mockmon &defender) const
    {
        const auto simpleAttackingMove = SimpleMove::AllMoves.at(Identifier());

        if (moves::CheckMoveAccuracy(simpleAttackingMove))
        {
            for (auto &mv : MoveComponenets)
            {
                const auto outomce = mv(arena, simpleAttackingMove, attacker, defender);
                std::cout << outomce.m_moveOutcomeDescrition << '\n';
            }
        }
        else
        {
            std::cout << attacker.GetName() << " missed with " << simpleAttackingMove.Identifier() << '\n';
        }
    }


    condition::pulser_uq_ptr MakeCondition(condition::ConditionId conditionid,Mockmon & enemy)
    {
        using namespace condition;
        switch (conditionid)
        {
        case ConditionId::Poison:
            return std::make_unique<PoisonCondition>(enemy, 16.0);
            break;
        case ConditionId::Sleep:
                    return std::make_unique<SleepCondition>(enemy, 3);

        default:
            break;
        }
        return std::make_unique<PoisonCondition>(enemy, 16.0);
    }

    //here are some other attacks, will eventually need refactoring
#pragma region attacks

    MoveOutcome RegularMove(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender,const MovesTargeting & movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
        auto damage = static_cast<int>(Battle::ModifyAttack(AttackingMove, attacker,targetingPair.AttackerStat, defender,targetingPair.DefenderStat));
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), " damage!"})};
        return o;
    }

    MoveOutcome RecoilDamageMove(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, double divisionFactor)
    {
        auto damage = std::max(1, static_cast<int>(Battle::ModifyAttack(AttackingMove, attacker,StatsTypes::Attack, attacker,StatsTypes::Defence) / divisionFactor));
        attacker.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "takes", std::to_string(damage), "recoil damage from", Stringify(AttackingMove.Identifier())})};
        return o;
    }

    MoveOutcome ChangeSelfStatMove(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  attacker.CurrentStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used",Stringify(AttackingMove.Identifier()), "and changed stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome ChangeOpponentStatMove(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  defender.CurrentStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(AttackingMove.Identifier()), "and changed", defender.GetName(),"stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome DirectDamageByPassResistance(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, double damage)
    {
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByTargetCalculation(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, const ExDamageByState & dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(defender));
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByAttackerCalculation(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, const ExDamageByState & dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(attacker));
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome AddConditionStatus(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, const StatusInflicment statusConditionInflicment)
    {
        if (defender.GetMockmonSpeciesData().IsSpeciesOfType(statusConditionInflicment.moveType))
        {
            MoveOutcome o{AppendAll({defender.GetName(), "cant be efflicted with", Stringify(statusConditionInflicment.AfflicteCondition),"by",Stringify(AttackingMove.Identifier()) })};    
            return o;
        }
        if (defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.AfflicteCondition))
        {
            //already afflicted
            MoveOutcome o{AppendAll({defender.GetName(), "is already", Stringify(statusConditionInflicment.AfflicteCondition),".",Stringify(AttackingMove.Identifier()), "failed!"})};    
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.ChanceToAfflictCondtion))
        {
            defender.m_currentCondtion.CauseCondition(MakeCondition(statusConditionInflicment.AfflicteCondition,defender));
            if (defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.AfflicteCondition))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "!", defender.GetName(),"is now", Stringify(statusConditionInflicment.AfflicteCondition)})};
                return o;    
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(),"tried to use",Stringify(AttackingMove.Identifier()), "but it failed to inflict condition",Stringify(statusConditionInflicment.AfflicteCondition)})};    
        return o;
            

        
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

#pragma endregion

}