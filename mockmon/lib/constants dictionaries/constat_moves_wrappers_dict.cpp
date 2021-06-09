#include "moves.h"
#include "interfaces.h"

namespace mockmon::moves
{
  
    const std::map<MoveId,ConstantMove> ConstantMove::AllMovesWrappers
    {
        //id,{id, base pp,max pp}
        MakeDictionaryPair<ConstantMove>(MoveId::Tackle,35,56),
        MakeDictionaryPair<ConstantMove>(MoveId::TailWhip,30,48),
        MakeDictionaryPair<ConstantMove>(MoveId::QuickAttack,30,48),
        MakeDictionaryPair<ConstantMove>(MoveId::HyperFang,15,24),
        
        MakeDictionaryPair<ConstantMove>(MoveId::FocusEnergy,30,48),
        
        MakeDictionaryPair<ConstantMove>(MoveId::WaterGun,25,40),
        MakeDictionaryPair<ConstantMove>(MoveId::Guillotine ,5,8),

        //high critical hit rate
        MakeDictionaryPair<ConstantMove>(MoveId::Slash ,20,32),
        MakeDictionaryPair<ConstantMove>(MoveId::Crabhammer ,10,16),
        MakeDictionaryPair<ConstantMove>(MoveId::KarateChop ,25,40),
        MakeDictionaryPair<ConstantMove>(MoveId::RazorLeaf ,25,40),


        MakeDictionaryPair<ConstantMove>(MoveId::StringShot ,40,64),
        MakeDictionaryPair<ConstantMove>(MoveId::Ember ,25,40),
        MakeDictionaryPair<ConstantMove>(MoveId::Struggle,500,1000), //probably not needed!
        MakeDictionaryPair<ConstantMove>(MoveId::SwordsDance,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::QuickAttack,30,48), 

        MakeDictionaryPair<ConstantMove>(MoveId::Swift,20,32), 


        //freezing moves
        MakeDictionaryPair<ConstantMove>(MoveId::IcePunch,15,24),
        MakeDictionaryPair<ConstantMove>(MoveId::IceBeam,10,16),
        MakeDictionaryPair<ConstantMove>(MoveId::Blizzard,5,8),

        //set damage moves
        MakeDictionaryPair<ConstantMove>(MoveId::SuperFang,10,16),
        MakeDictionaryPair<ConstantMove>(MoveId::SonicBoom,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::DragonRage,10,16), 
        MakeDictionaryPair<ConstantMove>(MoveId::SeismicToss,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::NightShade,15,24), 
        MakeDictionaryPair<ConstantMove>(MoveId::Psywave,15,24), 

        //status condition moves
        MakeDictionaryPair<ConstantMove>(MoveId::PoisonSting ,35,56),
        MakeDictionaryPair<ConstantMove>(MoveId::PoisonPowder ,35,56),
        MakeDictionaryPair<ConstantMove>(MoveId::SleepPowder ,15,24),
        MakeDictionaryPair<ConstantMove>(MoveId::StunSpore ,30,48),
        MakeDictionaryPair<ConstantMove>(MoveId::ConfuseRay,10,16), 


        MakeDictionaryPair<ConstantMove>(MoveId::Reflect,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::LightScreen,30,48), 
        MakeDictionaryPair<ConstantMove>(MoveId::Haze,30,48), 

        //charged moves
        MakeDictionaryPair<ConstantMove>(MoveId::SolarBeam,10 ,16), //charge
        MakeDictionaryPair<ConstantMove>(MoveId::SkullBash,10 ,16), //charge
        MakeDictionaryPair<ConstantMove>(MoveId::SkyAttack,5 ,8), //charge

        //semi-invulnerable,
        MakeDictionaryPair<ConstantMove>(MoveId::Dig,10 ,16), //charge, semi-invulnerable,
        MakeDictionaryPair<ConstantMove>(MoveId::Fly,15 ,24), //charge, semi-invulnerable,

    };

}