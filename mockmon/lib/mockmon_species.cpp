#include "mockmon_species.h"
#include <cmath>
#include <algorithm>

namespace mockmon
{

    const std::map<MockmonSpeciesId,MockmonSpecies> MockmonSpecies::AllMockmons
    {
        //explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,long speciesExp,Stats & sepeciesStats,const std::map<int,moves::MoveId> & levelUpMovesList);
        {MockmonSpeciesId::Mew, MockmonSpecies(MockmonSpeciesId::Mew,types::Types::Normal,LevelUpGroup::MediumSlowLevelUp,64,{100,100,100,100,100},
        {
            //moves list
            {1,{moves::MoveId::WaterGun,moves::MoveId::Guillotine}}
        }
        )},
        {MockmonSpeciesId::Ratata, MockmonSpecies(MockmonSpeciesId::Ratata,types::Types::Normal,LevelUpGroup::MediumFastLevelUp,57,{30,56,35,25,72},
        {
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
            {23,{moves::MoveId::FocusEnergy}},
            {34,{moves::MoveId::SuperFang}},
        }
        )},
        {MockmonSpeciesId::Raticate, MockmonSpecies(MockmonSpeciesId::Raticate,types::Types::Normal,LevelUpGroup::MediumFastLevelUp,116,{55,81,60,50,97},
        {
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
            {27,{moves::MoveId::FocusEnergy}},
            {41,{moves::MoveId::SuperFang}},
        }
        )},

        //{MockmonSpeciesId::Ratata, MockmonSpecies()},
        //{MockmonSpeciesId::Ratata, MockmonSpecies(MockmonSpeciesId::Ratata,types::Types::Water,100,40,25,40)},
    };

}