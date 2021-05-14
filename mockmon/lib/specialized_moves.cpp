#include "specialized_moves.h"
#include "moves_stats_targeting.h"
#include "random_gen.h"
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
        MoveOutcome o{AppendAll({attacker.GetName(), "used", "with",Stringify(AttackingMove.Identifier()), "and changed stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome ChangeOpponentStatMove(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  defender.CurrentStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", "with", Stringify(AttackingMove.Identifier()), "and changed", defender.GetName(),"stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome DirectDamageByPassResistance(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, double damage)
    {
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), " damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByTargetCalculation(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, const ExDamageByState & dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(defender));
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), " damage!"})};
        return o;
    }

        MoveOutcome DirectDamageByAttackerCalculation(Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, const ExDamageByState & dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(attacker));
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), " damage!"})};
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

#pragma endregion
    // double SeisemeticToss(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    // {
    //     return attacker.GetCurrentLevel();
    // }

    // double NightShade(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    // {
    //     return attacker.GetCurrentLevel();
    // }

    // double DragonRage(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    // {
    //     auto typeMofider{defender.GetTypeEffectivenessModifer(AttackingMove)}; //typeResistancs and weakness
    //     if (typeMofider == types::TypeEffectivenessModifier::NotEffective)
    //         return 0.0;

    //     return 40.0;
    // }

    // double SuperFang(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    // {

    //     //always does half
    //     return std::max(1, defender.CurrentStats.Health.GetStat());
    // }

    // double SonicBoom(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    // {
    //     //always does half
    //     return std::max(1, defender.CurrentStats.Health.GetStat());
    // }

}