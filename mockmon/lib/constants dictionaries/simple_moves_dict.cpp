#include "moves.h"
#include "random_gen.h"
#include "interfaces.h"

namespace mockmon::moves
{
    /*
    stats modifers (increase attck, decrease enemy defence, accuracy)
    status : confused, poison, paralyzed,etc
    moves that deal unique amount of damage (set amount, percent, bylevel)
    moves with recoil damage,
    */

    const std::map<MoveId,SimpleMove> SimpleMove::AllMoves
    {
        //id,{id,type,accuracy,power}
        MakeDictionaryPair<SimpleMove>(MoveId::Tackle,types::Types::Normal,95,35),
        MakeDictionaryPair<SimpleMove>(MoveId::TailWhip,types::Types::Normal,100,5),
        MakeDictionaryPair<SimpleMove>(MoveId::QuickAttack,types::Types::Normal,100,40),
        MakeDictionaryPair<SimpleMove>(MoveId::HyperFang,types::Types::Normal,90,80),
        MakeDictionaryPair<SimpleMove>(MoveId::FocusEnergy,types::Types::Normal,100,5),
        
        MakeDictionaryPair<SimpleMove>(MoveId::WaterGun,types::Types::Water,100,40),
        MakeDictionaryPair<SimpleMove>(MoveId::Guillotine ,types::Types::Normal,30,200),
        MakeDictionaryPair<SimpleMove>(MoveId::Slash ,types::Types::Normal,100,70),
        
        MakeDictionaryPair<SimpleMove>(MoveId::StringShot,types::Types::Bug,95,0), //negative boosting

        MakeDictionaryPair<SimpleMove>(MoveId::Ember,types::Types::Fire,100,40),
        MakeDictionaryPair<SimpleMove>(MoveId::Struggle,types::Types::Typeless,50,30),
        MakeDictionaryPair<SimpleMove>(MoveId::SwordsDance,types::Types::Normal,100,0), //boosting
        MakeDictionaryPair<SimpleMove>(MoveId::QuickAttack,types::Types::Normal,100,40), //priority

        //set damage moves
        MakeDictionaryPair<SimpleMove>(MoveId::SonicBoom,types::Types::Normal,90,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::SuperFang,types::Types::Normal,90,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::SeismicToss,types::Types::Normal,100,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::DragonRage,types::Types::Dragon,100,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::NightShade,types::Types::Ghost,100,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::Psywave,types::Types::Psychic,100,0), //set Damage

        //status condition moves
        MakeDictionaryPair<SimpleMove>(MoveId::PoisonSting,types::Types::Poison ,100,15), //status
        MakeDictionaryPair<SimpleMove>(MoveId::PoisonPowder,types::Types::Poison ,75,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::SleepPowder,types::Types::Grass ,75,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::Reflect,types::Types::Psychic ,100,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::LightScreen,types::Types::Psychic ,100,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::Haze,types::Types::Ice ,75,0), //status


    };
}