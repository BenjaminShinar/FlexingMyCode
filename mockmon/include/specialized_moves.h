#pragma once

#include "moves.h"
#include "mockmon_data.h"
#include "Battle.h"
#include "arena.h"
#include <initializer_list>
#include <functional>

namespace mockmon::moves
{
    //some way to describe what happened
    struct MoveOutcome
    {   
        std::string m_moveOutcomeDescrition;

    };
    
    //this is a move typedef
    using ExMove = std::function<MoveOutcome(Battle& battle,Arena & arena, const moves::SimpleMove & AttackingMove,Mockmon & attacker,Mockmon & defender)>;

    //this should replace the BaseMoveclass
    //we need some outcome?
    class CompositeMove : public DescribleModule<moves::MoveId>
    {
        public:

        explicit CompositeMove(moves::MoveId moveId,const std::initializer_list<ExMove> & componenets):
        DescribleModule(moveId)
        ,MoveComponenets(componenets)
        {
        }
     
        explicit CompositeMove(const CompositeMove & other ) = default;
        CompositeMove(CompositeMove && other ) = default;

        void Perform(Battle& battle,Arena & arena, Mockmon & attacker,Mockmon & defender) const;

        std::vector<ExMove> MoveComponenets;
        std::string Describe() const override
        {
            return "ss";
        }

        static const std::map<moves::MoveId,CompositeMove> AllCompositeMoves;

    };

    ExMove CreateNormalDamagingMove();
    ExMove CreateNormalRecoilDamagingMove(const double divFactor);
    ExMove CreateAttackBoostingMove(const double attackBoost);
    ExMove CreateDirectDamagingMoveByPassImmunity(const double setDamage);

}