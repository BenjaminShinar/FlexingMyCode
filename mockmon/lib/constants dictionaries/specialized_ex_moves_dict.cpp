#include "specialized_moves.h"
#include "interfaces.h"

#include "random_gen.h"

#include <initializer_list>
namespace mockmon::moves
{
    using il_exMV = std::initializer_list<ExMove>;

    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllCompositeMoves{
        //how this works?
        MakeDictionaryPair<CompositeMove>(MoveId::Tackle,il_exMV{CreateNormalDamagingMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::Struggle, il_exMV{CreateNormalDamagingMove(), CreateNormalRecoilDamagingMove(2.0)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SwordsDance, il_exMV{CreateSelfStatChangingMove(StatsTypes::Attack,StatModifiersLevels::GreatlyIncrease)}),
        MakeDictionaryPair<CompositeMove>(MoveId::TailWhip, il_exMV{CreateOpponentStatChangingMove(StatsTypes::Defence,StatModifiersLevels::Decrese)}),
        MakeDictionaryPair<CompositeMove>(MoveId::QuickAttack, il_exMV{CreateNormalDamagingMove()}),
        
        //set damage moves
        MakeDictionaryPair<CompositeMove>(MoveId::SonicBoom, il_exMV{CreateDirectDamagingMoveByPassImmunity(20)}),
        MakeDictionaryPair<CompositeMove>(MoveId::DragonRage, il_exMV{CreateDirectDamagingMoveByPassImmunity(40)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SuperFang, il_exMV{CreateDirectDamagingMoveTargetStateByPassImmunity([](const Mockmon & m){return std::max(1.0,m.CurrentStats.Health.GetStat()/2.0);})}),
        MakeDictionaryPair<CompositeMove>(MoveId::SeismicToss, il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon & m){return std::max(1.0,m.GetCurrentLevel()*1.0);})}),
        MakeDictionaryPair<CompositeMove>(MoveId::NightShade, il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon & m){return std::max(1.0,m.GetCurrentLevel()*1.0);})}),
        MakeDictionaryPair<CompositeMove>(MoveId::Psywave, il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon & m){return std::max(1.0,1.0 + random::Randomer::GetRandom(m.GetCurrentLevel()));})}),


        // {MoveId::TailWhip,SimpleMove(MoveId::TailWhip,types::Types::Normal,100,5)},
        // {MoveId::QuickAttack,SimpleMove(MoveId::QuickAttack,types::Types::Normal,100,40)},
        // {MoveId::HyperFang,SimpleMove(MoveId::HyperFang,types::Types::Normal,90,80)},
        // {MoveId::FocusEnergy,SimpleMove(MoveId::FocusEnergy,types::Types::Normal,100,5)},
        // {MoveId::SuperFang,SimpleMove(MoveId::SuperFang,types::Types::Normal,90,5)},
        // {MoveId::WaterGun, SimpleMove(MoveId::WaterGun,types::Types::Water,100,40)},
        // {MoveId::Guillotine ,SimpleMove(MoveId::Guillotine ,types::Types::Normal,30,200)},
        // {MoveId::Slash ,SimpleMove(MoveId::Slash ,types::Types::Normal,100,70)},
        // {MoveId::PoisonSting ,SimpleMove(MoveId::PoisonSting,types::Types::Poison ,100,15)}, //status
        // {MoveId::StringShot ,SimpleMove(MoveId::StringShot,types::Types::Bug,95,10)}, //status
        // {MoveId::Ember ,SimpleMove(MoveId::Ember,types::Types::Fire,100,40)},

        //{MoveId::Struggle, SimpleMove(MoveId::Struggle,types::Types::Typeless,50,30)},
    };

}