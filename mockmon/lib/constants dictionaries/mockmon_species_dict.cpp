#include "mockmon_species.h"

#include "interfaces.h"

namespace mockmon
{


   //using s_t = std::set<types::Types>;
    //using m_i_v_m = std::map<int,vector_type_T<moves::MoveId>>;
    const std::map<MockmonSpeciesId,MockmonSpecies> MockmonSpecies::AllMockmons
    {
        //explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,long speciesExp,Stats & sepeciesStats,const std::map<int,moves::MoveId> & levelUpMovesList);
        
        {MockmonSpeciesId::Mew,MockmonSpecies(MockmonSpeciesId::Mew,
        {types::Types::Psychic},
        LevelUpGroup::MediumSlowLevelUp,64,
        SpeciesStats{100,100,100,100,100},
        {
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::Struggle}}
        }
        )},
        {MockmonSpeciesId::Rattata, MockmonSpecies(MockmonSpeciesId::Rattata,
        {types::Types::Normal},
        LevelUpGroup::MediumFastLevelUp,57,
        SpeciesStats{30,56,35,25,72},
        {
            //moves list

            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            // {14,{moves::MoveId::HyperFang}},
            // {23,{moves::MoveId::FocusEnergy}},
            // {34,{moves::MoveId::SuperFang}},
        }
        )},
        {MockmonSpeciesId::Raticate, MockmonSpecies(MockmonSpeciesId::Raticate,
        {types::Types::Normal},
        LevelUpGroup::MediumFastLevelUp,116,
        SpeciesStats{55,81,60,50,97},
        {
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
            {27,{moves::MoveId::FocusEnergy}},
            {41,{moves::MoveId::SuperFang}},
        }
        )},

        {MockmonSpeciesId::Weedle, MockmonSpecies(MockmonSpeciesId::Weedle,
        {types::Types::Bug,types::Types::Poison},
        LevelUpGroup::MediumFastLevelUp,52,
        SpeciesStats{40,35,30,20,50},
        {
            //moves list
             {1,{moves::MoveId::Struggle}},
            //{1,{moves::MoveId::PoisonSting, moves::MoveId::StringShot}},
        }
        )},
    };

}