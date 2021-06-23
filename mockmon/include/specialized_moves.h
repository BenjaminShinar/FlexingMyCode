#pragma once

#include "identifiers/types_id.h"
#include "identifiers/stat_modifiers_id.h"
#include "identifiers/moves_stats_targeting_id.h"
#include "random_gen.h"
#include "moves.h"
#include "mockmon_data.h"
#include "Battle.h"
#include "arena.h"
#include <functional>
#include <initializer_list>
#include <map>
#include <set>
namespace mockmon::moves
{
    [[nodiscard]] condition::pulser_uq_ptr MakeCondition(condition::PulsingConditionId conditionid, Mockmon &effectedMockmon);

    //maybe this needs to be somewhere else
    //there are too many declerations dependencies in this file..
    struct StatusChanceTypes
    {
        const unsigned int ChanceToAfflictCondtion;
        const std::set<types::Types> ImmuneTypes;
        const std::set<types::Types> SuspectibleTypes;
    };

    //sfinae - i'm not sure why this needs to be static or why declearing the specializations inlines matters. but this works
    template <typename T>
    static void Efflict(T, Mockmon &);

    template <>
    inline void Efflict(condition::PulsingConditionId pulsingCondition, Mockmon &m)
    {
        m.m_currentCondtion.CausePulsingCondition(MakeCondition(pulsingCondition, m));
    }

    template <>
    inline void Efflict(condition::NonPulsingConditionId nonepulsingCondition, Mockmon &m)
    {
        m.m_currentCondtion.CauseNonPulsingCondition(nonepulsingCondition);
    }

    //not sure how to properly move this to .cpp file
    template <typename T>
    struct AbstractStatusInflicment
    {
        const types::Types moveType;
        const StatusChanceTypes Chance;
        const T effect;
        battle::MoveOutcome TryEfflict(moves::MoveId mv, Mockmon &attacker, Mockmon &defender) const
        {
            if (CanEfflict(defender))
            {
                if (AlwaysEfflict(defender) || random::Randomer::CheckPercentage(Chance.ChanceToAfflictCondtion))
                {
                    Efflict(effect, defender);
                    if (defender.m_currentCondtion.IsAffiliatedWithCondition(effect))
                    {
                        //success
                        battle::MoveOutcome o{true, AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(mv), "!", defender.GetName(), "is now", Stringify(effect)})};
                        return o;
                    }
                }
                //failed to afflict / missed
                battle::MoveOutcome o{false, AppendAll({attacker.GetName(), "tried to use", Stringify(mv), "but it failed to inflict condition", Stringify(effect)})};
                return o;
            }
            else
            {
                battle::MoveOutcome o{false, AppendAll({defender.GetName(), "cant be efflicted with", Stringify(effect), "by", Stringify(mv)})};
                return o;
            }
        }

    private:
        [[nodiscard]] std::vector<types::Types> GetMatchingTypes(const std::set<types::Types> &mockmonTypes, const std::set<types::Types> &innerTypes) const
        {
            std::vector<types::Types> matchingTypes(5);
            auto typesIter = std::set_intersection(std::begin(mockmonTypes), std::end(mockmonTypes), std::begin(innerTypes), std::end(innerTypes), std::begin(matchingTypes));
            matchingTypes.resize(typesIter - std::begin(matchingTypes));
            return matchingTypes;
        }
        [[nodiscard]] bool CanEfflict(const Mockmon &m) const
        {
            const auto matchingTypes = GetMatchingTypes(m.GetMockmonSpeciesData().SpeciesTypes, Chance.ImmuneTypes);
            return (matchingTypes.empty());
        }
        [[nodiscard]] bool AlwaysEfflict(const Mockmon &m) const
        {
            const auto matchingTypes = GetMatchingTypes(m.GetMockmonSpeciesData().SpeciesTypes, Chance.SuspectibleTypes);
            return (!matchingTypes.empty());
        }
    };

    using PulsingStatusInflicment = AbstractStatusInflicment<condition::PulsingConditionId>;
    using NonPulsingStatusInflicment = AbstractStatusInflicment<condition::NonPulsingConditionId>;
    using ExMove = std::function<battle::MoveOutcome(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)>;
    using ExMoveChanceCheck = std::function<battle::MoveOutcome(Arena &arena, Mockmon &attacker, Mockmon &defender)>;
    using ExDamageByState = std::function<double(const Mockmon &mockmonToChoose)>;
    using ChanceToInflict = std::function<bool()>;

    /**
     * @brief 
     * this should replace the BaseMoveclass
     * we need some outcome?
     * is it really describle<>?  
     */
    class CompositeMove : public DescribleModule<moves::MoveId>
    {
    public:
        explicit CompositeMove(moves::MoveId moveId, const ExMoveChanceCheck &movechance, const std::initializer_list<ExMove> &componenets) : DescribleModule(moveId),
                                                                                                                                              MoveChance(movechance),
                                                                                                                                              MoveComponenets(componenets)
        {
        }

        explicit CompositeMove(const CompositeMove &other) = default;
        CompositeMove(CompositeMove &&other) = default;

        std::vector<battle::MoveOutcome> Perform(Arena &arena, Mockmon &attacker, Mockmon &defender) const;
        ExMoveChanceCheck MoveChance;
        std::vector<ExMove> MoveComponenets;
        std::string Describe() const override
        {
            return "fix this";
        }

        static const std::map<moves::MoveId, CompositeMove> AllCompositeMoves;
        static const std::map<moves::MoveId, CompositeMove> AllChargedCompositeMoves; //this is for the 2nd turn of a composite move, or for effects like sleep, hit self, Freeze, parlysis..
    };

    [[nodiscard]] ExMoveChanceCheck CreateNormalAccuracyCheck(int moveBaseAccuracy, const MovesTargeting movesTargeting);
    [[nodiscard]] ExMoveChanceCheck CreateSetAccuracyCheck(int setchances);
    [[nodiscard]] ExMoveChanceCheck CreateByPassAccuracyCheck();
    [[nodiscard]] ExMoveChanceCheck CreateCheckSpeedThenNormalAccuracyCheck(int moveBaseAccuracy, const MovesTargeting movesTargeting);

    [[nodiscard]] ExMove CreateNormalDamagingMove(const MovesTargeting movesTargeting);
    [[nodiscard]] ExMove CreateNormalSelfDamagingMove(const MovesTargeting movesTargeting);

    [[nodiscard]] ExMove CreateNormalRecoilDamagingMove(const double divFactor);

    [[nodiscard]] ExMove CreateOHKOMove();

    [[nodiscard]] ExMove CreateSelfStatChangingMove(const ChanceToInflict &chanceToInflictFN, StatsTypes effectedStat, StatModifiersLevels modifer);
    [[nodiscard]] ExMove CreateOpponentStatChangingMove(const ChanceToInflict &chanceToInflictFN, StatsTypes effectedStat, StatModifiersLevels modifer);

    //pulsing
    [[nodiscard]] ExMove CreateOpponentPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);
    [[nodiscard]] ExMove CreateSelfPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);
    //none pulsing
    [[nodiscard]] ExMove CreateOpponentNonPulsingConditionMove(const NonPulsingStatusInflicment statusConditionInflicment);
    [[nodiscard]] ExMove CreateSelfNonPulsingConditionMove(const NonPulsingStatusInflicment statusConditionInflicment);

    //remove one spesific pulsing condition - freeze by burn
    [[nodiscard]] ExMove CreateRemoveOpponentPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);
    [[nodiscard]] ExMove CreateRemoveSelfPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);

    [[nodiscard]] ExMove CreateResetSelfConditionMove();
    [[nodiscard]] ExMove CreateResetOpponentConditionMove();

    [[nodiscard]] ExMove CreateDirectDamagingMoveByPassImmunity(const double setDamage);
    [[nodiscard]] ExMove CreateDirectDamagingMoveTargetStateByPassImmunity(const ExDamageByState &dmgByStateCalc);
    [[nodiscard]] ExMove CreateDirectDamagingMoveAttackerStateByPassImmunity(const ExDamageByState &dmgByStateCalc);

    [[nodiscard]] ExMove CreateStoredMove(const moves::MoveId storedMove);

    [[nodiscard]] ExMove CreateWastedTurnMove();

    [[nodiscard]] ChanceToInflict CreateAllwaysSameChance(bool sameValue);
    [[nodiscard]] ChanceToInflict CreatePercentageChance(int chance);
}