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
        //id,{id,type,power}
        MakeDictionaryPair<SimpleMove>(MoveId::Tackle,types::Types::Normal,35),
        MakeDictionaryPair<SimpleMove>(MoveId::TailWhip,types::Types::Normal,5),
        MakeDictionaryPair<SimpleMove>(MoveId::QuickAttack,types::Types::Normal,40),
        MakeDictionaryPair<SimpleMove>(MoveId::HyperFang,types::Types::Normal,80),
        //MakeDictionaryPair<SimpleMove>(MoveId::Guillotine ,types::Types::Normal,200),
        MakeDictionaryPair<SimpleMove>(MoveId::WaterGun,types::Types::Water,40),
        

        MakeDictionaryPair<SimpleMove>(MoveId::Slash ,types::Types::Normal,70), //high critical hit rate
        MakeDictionaryPair<SimpleMove>(MoveId::Crabhammer ,types::Types::Water,90), //high critical hit rate
        MakeDictionaryPair<SimpleMove>(MoveId::KarateChop ,types::Types::Normal,50), //high critical hit rate
        MakeDictionaryPair<SimpleMove>(MoveId::RazorLeaf ,types::Types::Grass,55), //high critical hit rate
        

        MakeDictionaryPair<SimpleMove>(MoveId::StringShot,types::Types::Bug,0), //negative boosting

        MakeDictionaryPair<SimpleMove>(MoveId::Ember,types::Types::Fire,40),
        MakeDictionaryPair<SimpleMove>(MoveId::Struggle,types::Types::Typeless,30),
        MakeDictionaryPair<SimpleMove>(MoveId::SwordsDance,types::Types::Normal,0), //boosting
        MakeDictionaryPair<SimpleMove>(MoveId::QuickAttack,types::Types::Normal,40), //priority

        // moves that can't miss
        MakeDictionaryPair<SimpleMove>(MoveId::Swift,types::Types::Normal,60), //can't miss
        //set damage moves
        MakeDictionaryPair<SimpleMove>(MoveId::SonicBoom,types::Types::Normal,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::SuperFang,types::Types::Normal,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::SeismicToss,types::Types::Normal,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::DragonRage,types::Types::Dragon,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::NightShade,types::Types::Ghost,0), //set Damage
        MakeDictionaryPair<SimpleMove>(MoveId::Psywave,types::Types::Psychic,0), //set Damage

        //status condition moves
        MakeDictionaryPair<SimpleMove>(MoveId::PoisonSting,types::Types::Poison ,15), //status
        MakeDictionaryPair<SimpleMove>(MoveId::PoisonPowder,types::Types::Poison ,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::SleepPowder,types::Types::Grass ,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::StunSpore,types::Types::Grass ,0), //status

        MakeDictionaryPair<SimpleMove>(MoveId::Reflect,types::Types::Psychic ,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::LightScreen,types::Types::Psychic ,0), //status
        MakeDictionaryPair<SimpleMove>(MoveId::FocusEnergy,types::Types::Normal,0), //status

        MakeDictionaryPair<SimpleMove>(MoveId::Haze,types::Types::Ice ,0), //status

        //charged moves
        MakeDictionaryPair<SimpleMove>(MoveId::SolarBeam,types::Types::Grass ,120), //damage is still taken from here
        MakeDictionaryPair<SimpleMove>(MoveId::SkullBash,types::Types::Normal ,100), //damage is still taken from here
        MakeDictionaryPair<SimpleMove>(MoveId::SkyAttack,types::Types::Flying ,140), //damage is still taken from here


        
        //semi-invulnerable,
        MakeDictionaryPair<SimpleMove>(MoveId::Dig,types::Types::Ground ,100), //damage is still taken from here
        MakeDictionaryPair<SimpleMove>(MoveId::Fly,types::Types::Flying ,70), //damage is still taken from here

        //moves requiring recharge
        //MakeDictionaryPair<SimpleMove>(MoveId::SolarBeam,types::Types::Grass ,100), //damage is still taken from here
    };
}