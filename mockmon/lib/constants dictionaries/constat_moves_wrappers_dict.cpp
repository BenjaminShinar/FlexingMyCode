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
        MakeDictionaryPair<ConstantMove>(MoveId::Slash ,20,32),
        MakeDictionaryPair<ConstantMove>(MoveId::PoisonSting ,35,56),
        MakeDictionaryPair<ConstantMove>(MoveId::StringShot ,40,64),
        MakeDictionaryPair<ConstantMove>(MoveId::Ember ,25,40),
        MakeDictionaryPair<ConstantMove>(MoveId::Struggle,500,1000), //probably not needed!
        MakeDictionaryPair<ConstantMove>(MoveId::SwordsDance,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::QuickAttack,30,48), 

        //set damage moves
        MakeDictionaryPair<ConstantMove>(MoveId::SuperFang,10,16),
        MakeDictionaryPair<ConstantMove>(MoveId::SonicBoom,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::DragonRage,10,16), 
        MakeDictionaryPair<ConstantMove>(MoveId::SeismicToss,20,32), 
        MakeDictionaryPair<ConstantMove>(MoveId::NightShade,15,24), 
        MakeDictionaryPair<ConstantMove>(MoveId::Psywave,15,24), 

    };

}