#include "specialized_moves.h"
#include "interfaces.h"

namespace mockmon::moves
{
    using v_cx = vector_type_T<ExMove>;
    
    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllCompositeMoves{
        //how this works?
        MakeDictionaryPair<CompositeMove>(MoveId::Tackle, v_cx{CreateNormalDamagingMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::Struggle, v_cx{CreateNormalDamagingMove(), CreateNormalRecoilDamagingMove(2.0)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SwordsDance, v_cx{CreateSelfStatChangingMove(StatsTypes::Attack,StatModifiersLevels::GreatlyIncrease)}),
        MakeDictionaryPair<CompositeMove>(MoveId::TailWhip, v_cx{CreateOpponentStatChangingMove(StatsTypes::Defence,StatModifiersLevels::Decrese)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SonicBoom, v_cx{CreateDirectDamagingMoveByPassImmunity(20)}),
        MakeDictionaryPair<CompositeMove>(MoveId::QuickAttack, v_cx{CreateNormalDamagingMove()})
        // {MoveId::TailWhip,SimpleMove(MoveId::TailWhip,types::Types::Normal,100,5)),
        // {MoveId::QuickAttack,SimpleMove(MoveId::QuickAttack,types::Types::Normal,100,40)),
        // {MoveId::HyperFang,SimpleMove(MoveId::HyperFang,types::Types::Normal,90,80)),
        // {MoveId::FocusEnergy,SimpleMove(MoveId::FocusEnergy,types::Types::Normal,100,5)),
        // {MoveId::SuperFang,SimpleMove(MoveId::SuperFang,types::Types::Normal,90,5)),
        // {MoveId::WaterGun, SimpleMove(MoveId::WaterGun,types::Types::Water,100,40)),
        // {MoveId::Guillotine ,SimpleMove(MoveId::Guillotine ,types::Types::Normal,30,200)),
        // {MoveId::Slash ,SimpleMove(MoveId::Slash ,types::Types::Normal,100,70)),
        // {MoveId::PoisonSting ,SimpleMove(MoveId::PoisonSting,types::Types::Poison ,100,15)), //status
        // {MoveId::StringShot ,SimpleMove(MoveId::StringShot,types::Types::Bug,95,10)), //status
        // {MoveId::Ember ,SimpleMove(MoveId::Ember,types::Types::Fire,100,40)),

        //{MoveId::Struggle, SimpleMove(MoveId::Struggle,types::Types::Typeless,50,30)),
    };

}