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
    //some way to describe what happened
    struct MoveOutcome
    {   
        std::string m_moveOutcomeDescrition;
        bool m_hit{true};

    };

    struct StatusInflicment
    {   
        const types::Types moveType;
        const condition::ConditionId AfflicteCondition;
        const unsigned int ChanceToAfflictCondtion;
    };
    
    //this is a move typedef
    using ExMove = std::function<MoveOutcome(Arena & arena, const moves::SimpleMove & AttackingMove,Mockmon & attacker,Mockmon & defender)>;
    using ExMoveChanceCheck = std::function<MoveOutcome(Arena & arena, Mockmon & attacker,Mockmon & defender)>;
    using ExDamageByState= std::function<double(const Mockmon & mockmonToChoose)>;

    //this should replace the BaseMoveclass
    //we need some outcome?
    class CompositeMove : public DescribleModule<moves::MoveId>
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

    };

    ExMoveChanceCheck CreateNormalAccuracyCheck(int moveBaseAccuracy,const MovesTargeting movesTargeting);
    ExMoveChanceCheck CreateSetAccuracyCheck(int setchances);

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

}