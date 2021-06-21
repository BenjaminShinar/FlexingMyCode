#include "specialized_moves.h"
#include "moves_stats_targeting.h"
#include "random_gen.h"
#include "stats/stats.h"
#include "mockmon_conditions/all_conditions.h"
#include "interfaces.h"

#include <functional>
#include <utility>
#include <math.h>
#include <algorithm>

namespace mockmon::moves
{
    using namespace std::placeholders; //import this for _1,_2,

    /**
     * @brief 
     * perform all the parts of the move
     * @param arena 
     * @param attacker 
     * @param defender 
     */
    void CompositeMove::Perform(Arena &arena, Mockmon &attacker, Mockmon &defender) const
    {
        const auto o = MoveChance(arena, attacker, defender);
        if (o.m_hit)
        {
            for (auto &mv : MoveComponenets)
            {
                const auto outomce = mv(arena, Identifier(), attacker, defender);
                if (!arena.Silent)
                {
                    std::cout << outomce.m_moveOutcomeDescrition << '\n';
                }
            }
        }
        else
        {
            if (!arena.Silent)
            {
                std::cout << attacker.GetName() << " missed with " << Identifier() << '\n';
            }
        }
    }

    /**
     * @brief 
     * create a condition on a different mockmon
     * this probably belongs somewhere else 
     * @param conditionid 
     * @param effectedMockmon 
     * @return condition::pulser_uq_ptr 
     */
    condition::pulser_uq_ptr MakeCondition(condition::PulsingConditionId conditionid, Mockmon &effectedMockmon)
    {
        using namespace condition;
        switch (conditionid)
        {
        case PulsingConditionId::Poison:
            return std::make_unique<PoisonCondition>(effectedMockmon, 16.0);
            break;
        case PulsingConditionId::Sleep:
            return std::make_unique<SleepCondition>(effectedMockmon, random::Randomer::GetRandom(7) + 1);
            break;
        case PulsingConditionId::Burn:
            return std::make_unique<BurnCondition>(effectedMockmon, 16.0);
            break;
        case PulsingConditionId::Paralysis:
            return std::make_unique<ParalysisCondition>(effectedMockmon);

            break;
        case PulsingConditionId::Confusion:
            return std::make_unique<ConfusionCondition>(effectedMockmon, random::Randomer::GetRandom(4) + 2);

            break;
        case PulsingConditionId::Freeze:
            return std::make_unique<FreezeCondition>(effectedMockmon);
            break;
        case PulsingConditionId::Flinch:
            return std::make_unique<FlinchCondition>(effectedMockmon);
            break;
        default:
            break;
        }
        std::cerr << __FUNCTION__ << " should never have reached this location!\n";
        exit(1);
        return std::make_unique<EmptyCondition>();
    }

#pragma region move success Chances

    /**
    * @brief 
    * determine if an attack hits the opponent. uses noraml accuracy check
    * @param arena 
    * @param attacker attacking mon
    * @param defender defending mon
    * @param attackingMoveBaseAccuracy accuracy from 0 to 100
    * @param movesTargeting which stats are used to calculate modifiers to the chance
    * @return MoveOutcome 
    */
    MoveOutcome RegularAccuracyCheckMove([[maybe_unused]] Arena &arena, Mockmon &attacker, Mockmon &defender, int attackingMoveBaseAccuracy, const MovesTargeting &movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
        const auto [attackstat, defencestat] = arena.GetStatsModifier(attacker, targetingPair.AttackerStat, defender, targetingPair.DefenderStat);
        const auto modifier = attackstat * defencestat;
        const auto percentage = std::clamp(static_cast<int>(std::round(attackingMoveBaseAccuracy * modifier)), 0, 100);
        if (random::Randomer::CheckPercentage(percentage))
        {
            return MoveOutcome{"", true};
        }
        else
        {
            return MoveOutcome{"", false};
        }
    }

    /**
     * @brief Set the Chances Check Move object
     * set chance for moves to succeed or fail.
     * mostly for self boosting moves?
     * im not sure its relevnet
     * @param arena 
     * @param attacker 
     * @param defender 
     * @param setChances 
     * @return MoveOutcome 
     */
    MoveOutcome SetChancesCheckMove([[maybe_unused]] Arena &arena, [[maybe_unused]] Mockmon &attacker, [[maybe_unused]] Mockmon &defender, int setChances)
    {
        if (random::Randomer::CheckPercentage(setChances))
        {
            return MoveOutcome{"", true};
        }
        else
        {
            return MoveOutcome{"", false};
        }
    }
    /**
     * @brief 
     * moves that cant miss
     * mostly used for self boosting moves
     * or swift
     * @param arena 
     * @param attacker 
     * @param defender 
     * @return MoveOutcome 
     */
    MoveOutcome BypassAccuracyCheckMove([[maybe_unused]] Arena &arena, [[maybe_unused]] Mockmon &attacker, [[maybe_unused]] Mockmon &defender)
    {
        return MoveOutcome{"", true};
    }

    /**
    * @brief 
    * determine if an attack hits the opponent.
    * first check speeds, if attacker speed >= defender, use normal accuracy,
    * else, move misses
    * @param arena 
    * @param attacker attacking mon
    * @param defender defending mon
    * @param attackingMoveBaseAccuracy accuracy from 0 to 100
    * @param movesTargeting which stats are used to calculate modifiers to the chance
    * @return MoveOutcome 
    */
    MoveOutcome CheckSpeedAndThenAccuracyCheckMove(Arena &arena, Mockmon &attacker, Mockmon &defender, int attackingMoveBaseAccuracy, const MovesTargeting &movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(MovesTargeting::SpeedRace)};
        const auto [attackerSpeed, defenderSpeed] = arena.GetStatsModifier(attacker, targetingPair.AttackerStat, defender, targetingPair.DefenderStat);
        if (attackerSpeed >= defenderSpeed)
        {
            return RegularAccuracyCheckMove(arena, attacker, defender, attackingMoveBaseAccuracy, movesTargeting);
        }
        else
        {
            return MoveOutcome{"", false};
        }
    }
#pragma endregion

#pragma region attacks

    MoveOutcome WasteTurnMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        MoveOutcome o{AppendAll({attacker.GetName(), "is", Stringify(attackingMoveId), "for current turn"})};
        return o;
    }

    MoveOutcome RegularMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const MovesTargeting &movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
        auto damage = static_cast<int>(battle::ModifyAttack(attackingMoveId, attacker, targetingPair.AttackerStat, defender, targetingPair.DefenderStat));
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome RegularSelfMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const MovesTargeting &movesTargeting)
    {
        const auto targetingPair{MoveStatsTargeting::AllStatsTargeting.at(movesTargeting)};
        auto damage = static_cast<int>(battle::ModifyAttack(attackingMoveId, attacker, targetingPair.AttackerStat, attacker, targetingPair.DefenderStat));
        attacker.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit itself with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome RecoilDamageMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, double divisionFactor)
    {
        auto damage = std::max(1, static_cast<int>(battle::ModifyAttack(attackingMoveId, attacker, StatsTypes::Attack, attacker, StatsTypes::Defence) / divisionFactor));
        attacker.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "takes", std::to_string(damage), "recoil damage from", Stringify(attackingMoveId)})};
        return o;
    }

#pragma region stats boosting and hexing
    MoveOutcome ChangeSelfStatMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto &statRef = attacker.CurrentBattleStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "and changed stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome ChangeOpponentStatMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto &statRef = defender.CurrentBattleStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "and changed", defender.GetName(), "stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

#pragma endregion

    MoveOutcome DirectDamageByPassResistance([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, double damage)
    {
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByTargetCalculation([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const ExDamageByState &dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(defender));
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome DirectDamageByAttackerCalculation([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const ExDamageByState &dmgByStateCalc)
    {
        const auto damage = std::round(dmgByStateCalc(attacker));
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "for", std::to_string(damage), "damage!"})};
        return o;
    }

    MoveOutcome OneHitKO([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        const auto defenderMaxHealth = defender.CurrentBattleStats.Health.GetMaxStat();
        defender.CurrentBattleStats.Health.ChangeHealth(-1 * defenderMaxHealth);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "it's a One-Hit KO!"})};
        return o;
    }

#pragma region conditions

    //TODO: find a way to remove this whole mess
    MoveOutcome AddOpponentPulsingConditionStatus([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const PulsingStatusInflicment statusConditionInflicment)
    {
        if (defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
        {
            //already afflicted
            MoveOutcome o{AppendAll({defender.GetName(), "is already", Stringify(statusConditionInflicment.effect), ".", Stringify(attackingMoveId), "failed!"})};
            return o;
        }

        return statusConditionInflicment.TryEfflict(attackingMoveId, attacker, defender);
    }

    MoveOutcome AddSelfPulsingConditionStatus([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const PulsingStatusInflicment statusConditionInflicment)
    {

        if (attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
        {
            //already afflicted
            MoveOutcome o{AppendAll({attacker.GetName(), "is already", Stringify(statusConditionInflicment.effect), ".", Stringify(attackingMoveId), "failed!"})};
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.Chance.ChanceToAfflictCondtion))
        {
            attacker.m_currentCondtion.CausePulsingCondition(MakeCondition(statusConditionInflicment.effect, attacker));
            if (attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "!", attacker.GetName(), "is now", Stringify(statusConditionInflicment.effect)})};
                return o;
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(), "tried to use", Stringify(attackingMoveId), "but it failed to inflict condition", Stringify(statusConditionInflicment.effect)})};
        return o;
    }

    MoveOutcome RemoveOpponentPulsingConditionStatus([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const PulsingStatusInflicment statusConditionInflicment)
    {

        if (!defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
        {
            //not afflicted
            MoveOutcome o{AppendAll({defender.GetName(), "is not", Stringify(statusConditionInflicment.effect), ".", Stringify(attackingMoveId), "failed!"})};
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.Chance.ChanceToAfflictCondtion))
        {
            defender.m_currentCondtion.RemovePulsingCondition(statusConditionInflicment.effect);
            if (!defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(attackingMoveId), "!", defender.GetName(), "is no longer", Stringify(statusConditionInflicment.effect)})};
                return o;
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(), "tried to use", Stringify(attackingMoveId), "but it failed to remove condition", Stringify(statusConditionInflicment.effect)})};
        return o;
    }

    MoveOutcome RemoveSelfPulsingConditionStatus([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const PulsingStatusInflicment statusConditionInflicment)
    {
        if (!attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
        {
            //not afflicted
            MoveOutcome o{AppendAll({attacker.GetName(), "is not", Stringify(statusConditionInflicment.effect), ".", Stringify(attackingMoveId), "failed!"})};
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.Chance.ChanceToAfflictCondtion))
        {
            attacker.m_currentCondtion.RemovePulsingCondition(statusConditionInflicment.effect);
            if (!attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "!", attacker.GetName(), "is no longer", Stringify(statusConditionInflicment.effect)})};
                return o;
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(), "tried to use", Stringify(attackingMoveId), "but it failed to remove condition", Stringify(statusConditionInflicment.effect)})};
        return o;
    }

    MoveOutcome AddOpponentNonePulsingConditionStatus([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const NonPulsingStatusInflicment statusConditionInflicment)
    {
        if (defender.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
        {
            //already afflicted
            MoveOutcome o{AppendAll({defender.GetName(), "is already", Stringify(statusConditionInflicment.effect), ".", Stringify(attackingMoveId), "failed!"})};
            return o;
        }

        return statusConditionInflicment.TryEfflict(attackingMoveId, attacker, defender);
    }

    MoveOutcome AddSelfNonePulsingConditionStatus([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const NonPulsingStatusInflicment statusConditionInflicment)
    {

        if (attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
        {
            //already afflicted
            MoveOutcome o{AppendAll({attacker.GetName(), "is already", Stringify(statusConditionInflicment.effect), ".", Stringify(attackingMoveId), "failed!"})};
            return o;
        }
        if (random::Randomer::CheckPercentage(statusConditionInflicment.Chance.ChanceToAfflictCondtion))
        {
            attacker.m_currentCondtion.CauseNonPulsingCondition(statusConditionInflicment.effect);
            if (attacker.m_currentCondtion.IsAffiliatedWithCondition(statusConditionInflicment.effect))
            {
                //success
                MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "!", attacker.GetName(), "is now", Stringify(statusConditionInflicment.effect)})};
                return o;
            }
        }

        //failed to afflict / missed
        MoveOutcome o{AppendAll({attacker.GetName(), "tried to use", Stringify(attackingMoveId), "but it failed to inflict condition", Stringify(statusConditionInflicment.effect)})};
        return o;
    }

#pragma endregion

#pragma region reset stats and condition

    void ResetAllStatsAndConditionsChanges(Mockmon &effectedMockmon)
    {
        effectedMockmon.m_currentCondtion.RemoveAllConditions();
        for (auto &statsPair : effectedMockmon.CurrentBattleStats.m_battleStats)
        {
            statsPair.second.ResetBoost();
        }
    }

    MoveOutcome ResetSelfAllConditions([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        ResetAllStatsAndConditionsChanges(attacker);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "to reset all it's stats!"})};
        return o;
    }

    MoveOutcome ResetOpponenetAllConditions([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)
    {
        ResetAllStatsAndConditionsChanges(defender);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "to reset all of", defender.GetName(), "stats!"})};
        return o;
    }

#pragma endregion

    MoveOutcome StoreSelfChargedMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const moves::MoveId storedMoveId)
    {
        attacker.m_currentCondtion.StoreChargedMove(storedMoveId);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "to charge", Stringify(storedMoveId), "for next turn"})};
        return o;
    }

    MoveOutcome StoreOppenentChargedMove([[maybe_unused]] Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender, const moves::MoveId storedMoveId)
    {
        defender.m_currentCondtion.StoreChargedMove(storedMoveId);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", Stringify(attackingMoveId), "to charge", Stringify(storedMoveId), "in", defender.GetName(), "for next turn"})};
        return o;
    }

#pragma endregion

#pragma region expossed Chances
    ExMoveChanceCheck CreateNormalAccuracyCheck(int moveBaseAccuracy, const MovesTargeting movesTargeting)
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

    ExMoveChanceCheck CreateCheckSpeedThenNormalAccuracyCheck(int moveBaseAccuracy, const MovesTargeting movesTargeting)
    {
        auto bounded = std::bind(&CheckSpeedAndThenAccuracyCheckMove, _1, _2, _3, moveBaseAccuracy, movesTargeting);
        return bounded;
    }

#pragma endregion

#pragma region exposed methods

    ExMove CreateSelfStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto bounded = std::bind(&ChangeSelfStatMove, _1, _2, _3, _4, effectedStat, modifer);
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
        auto bounded = std::bind(&DirectDamageByPassResistance, _1, _2, _3, _4, setDamage);
        return bounded;
    }

    ExMove CreateDirectDamagingMoveTargetStateByPassImmunity(const ExDamageByState &dmgByStateCalc)
    {
        auto bounded = std::bind(&DirectDamageByTargetCalculation, _1, _2, _3, _4, dmgByStateCalc);
        return bounded;
    }

    ExMove CreateDirectDamagingMoveAttackerStateByPassImmunity(const ExDamageByState &dmgByStateCalc)
    {
        auto bounded = std::bind(&DirectDamageByAttackerCalculation, _1, _2, _3, _4, dmgByStateCalc);
        return bounded;
    }

    ExMove CreateNormalDamagingMove(const MovesTargeting movesTargeting)
    {
        auto bounded = std::bind(&RegularMove, _1, _2, _3, _4, movesTargeting);
        return bounded;
    }
    ExMove CreateNormalSelfDamagingMove(const MovesTargeting movesTargeting)
    {
        auto bounded = std::bind(&RegularSelfMove, _1, _2, _3, _4, movesTargeting);
        return bounded;
    }

    ExMove CreateOpponentPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&AddOpponentPulsingConditionStatus, _1, _2, _3, _4, statusConditionInflicment);
        return bounded;
    }

    ExMove CreateSelfPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&AddSelfPulsingConditionStatus, _1, _2, _3, _4, statusConditionInflicment);
        return bounded;
    }

    ExMove CreateOpponentNonPulsingConditionMove(const NonPulsingStatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&AddOpponentNonePulsingConditionStatus, _1, _2, _3, _4, statusConditionInflicment);
        return bounded;
    }

    ExMove CreateSelfNonPulsingConditionMove(const NonPulsingStatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&AddSelfNonePulsingConditionStatus, _1, _2, _3, _4, statusConditionInflicment);
        return bounded;
    }

    ExMove CreateRemoveOpponentPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&RemoveOpponentPulsingConditionStatus, _1, _2, _3, _4, statusConditionInflicment);
        return bounded;
    }

    ExMove CreateRemoveSelfPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment)
    {
        auto bounded = std::bind(&RemoveSelfPulsingConditionStatus, _1, _2, _3, _4, statusConditionInflicment);
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

    ExMove CreateOHKOMove()
    {
        auto bounded = std::bind(&OneHitKO, _1, _2, _3, _4);
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
        auto bounded = std::bind(&StoreSelfChargedMove, _1, _2, _3, _4, storedMove);
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