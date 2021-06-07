#include "mockmon_species.h"
#include "interfaces.h"

namespace mockmon
{


   using s_t = std::set<types::Types>;
   using v_Mv= vector_type_T<moves::MoveId>;
   using mp_i_vec_Mv = std::map<int,v_Mv>;
    const std::map<MockmonSpeciesId,MockmonSpecies> MockmonSpecies::AllMockmons
    {
        //explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,long speciesExp,Stats & sepeciesStats,const std::map<int,moves::MoveId> & levelUpMovesList);
        
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Mew,
        s_t{types::Types::Psychic},
        LevelUpGroup::MediumSlowLevelUp,64,
        stats::SpeciesBaseStats{100,100,100,100,100},
        mp_i_vec_Mv
        {
            //moves list
            {1,{moves::MoveId::Tackle}}
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Rattata,
        s_t{types::Types::Normal},
        LevelUpGroup::MediumFastLevelUp,57,
        stats::SpeciesBaseStats{30,56,35,25,72},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
         //   {23,{moves::MoveId::FocusEnergy}},
            {34,{moves::MoveId::SuperFang}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Raticate,
        s_t{types::Types::Normal},
        LevelUpGroup::MediumFastLevelUp,116,
        stats::SpeciesBaseStats{55,81,60,50,97},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
       //     {27,{moves::MoveId::FocusEnergy}},
            {41,{moves::MoveId::SuperFang}},
        }
        ),

        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Weedle,
        s_t{types::Types::Bug,types::Types::Poison},
        LevelUpGroup::MediumFastLevelUp,52,
        stats::SpeciesBaseStats{40,35,30,20,50},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::PoisonSting, moves::MoveId::StringShot}},
        }
        ),
    };

}