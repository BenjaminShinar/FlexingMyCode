#pragma once

#include "identifiers/types_id.h"
#include "identifiers/stat_modifiers_id.h"
#include "identifiers/moves_stats_targeting_id.h"
#include "moves.h"
#include "mockmon_data.h"
#include "Battle.h"
#include "arena.h"
#include <functional>
#include <initializer_list>
#include <map>
namespace mockmon::moves
{
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

    struct StatusInflicment
    {   
        const types::Types moveType;
        const condition::PulsingConditionId AfflicteCondition;
        const unsigned int ChanceToAfflictCondtion;
    };
    
    using ExMove = std::function<MoveOutcome(Arena & arena, const moves::MoveId attackingMoveId,Mockmon & attacker,Mockmon & defender)>;
    using ExMoveChanceCheck = std::function<MoveOutcome(Arena & arena, Mockmon & attacker,Mockmon & defender)>;
    using ExDamageByState= std::function<double(const Mockmon & mockmonToChoose)>;

    /**
     * @brief 
     * this should replace the BaseMoveclass
     * we need some outcome?
     * is it really describle<>?  
     */
    class  CompositeMove : public DescribleModule<moves::MoveId>
    {
        public:

        explicit CompositeMove(moves::MoveId moveId,const ExMoveChanceCheck & movechance,const std::initializer_list<ExMove> & componenets):
        DescribleModule(moveId),
        MoveChance(movechance),
        MoveComponenets(componenets)
        {
        }
     
        explicit CompositeMove(const CompositeMove & other ) = default;
        CompositeMove(CompositeMove && other ) = default;

        void Perform(Arena & arena, Mockmon & attacker,Mockmon & defender) const;
        ExMoveChanceCheck MoveChance;
        std::vector<ExMove> MoveComponenets;
        std::string Describe() const override
        {
            return "ss";
        }

        static const std::map<moves::MoveId,CompositeMove> AllCompositeMoves;
        static const std::map<moves::MoveId,CompositeMove> AllChargedCompositeMoves; //this is for the 2nd turn of a composite move, or for effects like sleep, hit self, Freeze, parlysis..
    };


    condition::pulser_uq_ptr MakeCondition(condition::PulsingConditionId conditionid,Mockmon & effectedMockmon);


    ExMoveChanceCheck CreateNormalAccuracyCheck(int moveBaseAccuracy,const MovesTargeting movesTargeting);
    ExMoveChanceCheck CreateSetAccuracyCheck(int setchances);
    ExMoveChanceCheck CreateByPassAccuracyCheck();

    ExMove CreateNormalDamagingMove(const MovesTargeting movesTargeting);
    ExMove CreateNormalRecoilDamagingMove(const double divFactor);
    ExMove CreateSelfStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer);
    ExMove CreateOpponentStatChangingMove(StatsTypes effectedStat, StatModifiersLevels modifer);
    ExMove CreateOpponentConditionMove(const StatusInflicment statusConditionInflicment);
    ExMove CreateSelfConditionMove(const StatusInflicment statusConditionInflicment);

    ExMove CreateResetSelfConditionMove();
    ExMove CreateResetOpponentConditionMove();

    ExMove CreateDirectDamagingMoveByPassImmunity(const double setDamage);
    ExMove CreateDirectDamagingMoveTargetStateByPassImmunity(const ExDamageByState & dmgByStateCalc);
    ExMove CreateDirectDamagingMoveAttackerStateByPassImmunity(const ExDamageByState & dmgByStateCalc);

    ExMove CreateStoredMove(const moves::MoveId storedMove);

    ExMove CreateWastedTurnMove();
}