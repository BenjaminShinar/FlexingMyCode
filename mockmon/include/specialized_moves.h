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
    condition::pulser_uq_ptr MakeCondition(condition::PulsingConditionId conditionid, Mockmon &effectedMockmon);

    /**
     * @brief 
     * how we expose the outcome of a move
     * mostly text for now, but we should use the success flat more often
     */
    struct MoveOutcome
    {
        std::string m_moveOutcomeDescrition;
        bool m_hit{true};
    };

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
        MoveOutcome TryEfflict(moves::MoveId mv, Mockmon &attacker, Mockmon &defender) const
        {
            if (CanEfflict(defender))
            {
                if (AlwaysEfflict(defender) || random::Randomer::CheckPercentage(Chance.ChanceToAfflictCondtion))
                {
                    Efflict(effect, defender);
                    if (defender.m_currentCondtion.IsAffiliatedWithCondition(effect))
                    {
                        //success
                        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(mv), "!", defender.GetName(), "is now", Stringify(effect)})};
                        return o;
                    }
                }
                //failed to afflict / missed
                MoveOutcome o{AppendAll({attacker.GetName(), "tried to use", Stringify(mv), "but it failed to inflict condition", Stringify(effect)})};
                return o;
            }
            else
            {
                MoveOutcome o{AppendAll({defender.GetName(), "cant be efflicted with", Stringify(effect), "by", Stringify(mv)})};
                return o;
            }
        }

    private:
        std::vector<types::Types> GetMatchingTypes(const std::set<types::Types> &mockmonTypes, const std::set<types::Types> &innerTypes) const
        {
            std::vector<types::Types> matchingTypes(5);
            auto typesIter = std::set_intersection(std::begin(mockmonTypes), std::end(mockmonTypes), std::begin(innerTypes), std::end(innerTypes), std::begin(matchingTypes));
            matchingTypes.resize(typesIter - std::begin(matchingTypes));
            return matchingTypes;
        }
        bool CanEfflict(const Mockmon &m) const
        {
            const auto matchingTypes = GetMatchingTypes(m.GetMockmonSpeciesData().SpeciesTypes, Chance.ImmuneTypes);
            return (matchingTypes.empty());
        }
        bool AlwaysEfflict(const Mockmon &m) const
        {
            const auto matchingTypes = GetMatchingTypes(m.GetMockmonSpeciesData().SpeciesTypes, Chance.SuspectibleTypes);
            return (!matchingTypes.empty());
        }
    };

    using PulsingStatusInflicment = AbstractStatusInflicment<condition::PulsingConditionId>;
    using NonPulsingStatusInflicment = AbstractStatusInflicment<condition::NonPulsingConditionId>;
    using ExMove = std::function<MoveOutcome(Arena &arena, const moves::MoveId attackingMoveId, Mockmon &attacker, Mockmon &defender)>;
    using ExMoveChanceCheck = std::function<MoveOutcome(Arena &arena, Mockmon &attacker, Mockmon &defender)>;
    using ExDamageByState = std::function<double(const Mockmon &mockmonToChoose)>;

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

        void Perform(Arena &arena, Mockmon &attacker, Mockmon &defender) const;
        ExMoveChanceCheck MoveChance;
        std::vector<ExMove> MoveComponenets;
        std::string Describe() const override
        {
            return "ss";
        }

        static const std::map<moves::MoveId, CompositeMove> AllCompositeMoves;
        static const std::map<moves::MoveId, CompositeMove> AllChargedCompositeMoves; //this is for the 2nd turn of a composite move, or for effects like sleep, hit self, Freeze, parlysis..
    };

    ExMoveChanceCheck CreateNormalAccuracyCheck(int moveBaseAccuracy, const MovesTargeting movesTargeting);
    ExMoveChanceCheck CreateSetAccuracyCheck(int setchances);
    ExMoveChanceCheck CreateByPassAccuracyCheck();
    ExMoveChanceCheck CreateCheckSpeedThenNormalAccuracyCheck(int moveBaseAccuracy, const MovesTargeting movesTargeting);

    ExMove CreateNormalDamagingMove(const MovesTargeting movesTargeting);
    ExMove CreateNormalSelfDamagingMove(const MovesTargeting movesTargeting);

    ExMove CreateNormalRecoilDamagingMove(const double divFactor);

    ExMove CreateOHKOMove();

    ExMove CreateSelfStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer);
    ExMove CreateOpponentStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer);

    //pulsing
    ExMove CreateOpponentPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);
    ExMove CreateSelfPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);
    //none pulsing
    ExMove CreateOpponentNonPulsingConditionMove(const NonPulsingStatusInflicment statusConditionInflicment);
    ExMove CreateSelfNonPulsingConditionMove(const NonPulsingStatusInflicment statusConditionInflicment);

    //remove one spesific pulsing condition - freeze by burn
    ExMove CreateRemoveOpponentPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);
    ExMove CreateRemoveSelfPulsingConditionMove(const PulsingStatusInflicment statusConditionInflicment);

    ExMove CreateResetSelfConditionMove();
    ExMove CreateResetOpponentConditionMove();

    ExMove CreateDirectDamagingMoveByPassImmunity(const double setDamage);
    ExMove CreateDirectDamagingMoveTargetStateByPassImmunity(const ExDamageByState &dmgByStateCalc);
    ExMove CreateDirectDamagingMoveAttackerStateByPassImmunity(const ExDamageByState &dmgByStateCalc);

    ExMove CreateStoredMove(const moves::MoveId storedMove);

    ExMove CreateWastedTurnMove();
}