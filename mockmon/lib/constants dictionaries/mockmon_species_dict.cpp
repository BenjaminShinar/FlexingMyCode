#include "mockmon_species.h"
#include "interfaces.h"

namespace mockmon
{


   using s_t = std::set<types::Types>;
   using s_species = std::set<MockmonSpeciesId>;
   using v_Mv= vector_type_T<moves::MoveId>;
   using mp_i_vec_Mv = std::map<int,v_Mv>;
    const std::map<MockmonSpeciesId,MockmonSpecies> MockmonSpecies::AllMockmons
    {
        //explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,long speciesExp,Stats & sepeciesStats,const std::map<int,moves::MoveId> & levelUpMovesList);
        
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Mew,
        s_species{},
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
        s_species{MockmonSpeciesId::Raticate},
        s_t{types::Types::Normal},
        LevelUpGroup::MediumFastLevelUp,57,
        stats::SpeciesBaseStats{30,56,35,25,72},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
            {23,{moves::MoveId::FocusEnergy}},
            {34,{moves::MoveId::SuperFang}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Raticate,
        s_species{},
        s_t{types::Types::Normal},
        LevelUpGroup::MediumFastLevelUp,116,
        stats::SpeciesBaseStats{55,81,60,50,97},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Tackle, moves::MoveId::TailWhip}},
            {7,{moves::MoveId::QuickAttack}},
            {14,{moves::MoveId::HyperFang}},
            {27,{moves::MoveId::FocusEnergy}},
            {41,{moves::MoveId::SuperFang}},
        }
        ),

        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Weedle,
        s_species{},
        s_t{types::Types::Bug,types::Types::Poison},
        LevelUpGroup::MediumFastLevelUp,52,
        stats::SpeciesBaseStats{40,35,30,20,50},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::PoisonSting, moves::MoveId::StringShot}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Pikachu,
        s_species{},
        s_t{types::Types::Electric},
        LevelUpGroup::MediumFastLevelUp,82,
        stats::SpeciesBaseStats{35,55,30,50,90},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Growl}},
            //{1,{moves::MoveId::ThunderShock, moves::MoveId::Growl}},
            {9,{moves::MoveId::ThunderWave}},
            {16,{moves::MoveId::QuickAttack}},
            {26,{moves::MoveId::Swift}},
            //{33,{moves::MoveId::Agility}},
            //{43,{moves::MoveId::Thunder}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Geodude,
        s_species{},
        s_t{types::Types::Rock,types::Types::Ground},
        LevelUpGroup::MediumSlowLevelUp,86,
        stats::SpeciesBaseStats{40,40,100,30,20},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Tackle}},
            {11,{moves::MoveId::DefenseCurl}},
            //{16,{moves::MoveId::RockThrow}},
            //{21,{moves::MoveId::SelfDestruct}},
            {26,{moves::MoveId::Harden}},
            //{31,{moves::MoveId::Earthquake}},
            //{36,{moves::MoveId::Explosion}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Vulpix,
        s_species{},
        s_t{types::Types::Fire},
        LevelUpGroup::MediumFastLevelUp,63,
        stats::SpeciesBaseStats{38,41,40,65,65},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::TailWhip,moves::MoveId::Ember}},
            {16,{moves::MoveId::QuickAttack}},
            //{21,{moves::MoveId::Roar}},
            {28,{moves::MoveId::ConfuseRay}},
            //{35,{moves::MoveId::Flamethrower}},
            //{42,{moves::MoveId::FireSpin}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Gastly,
        s_species{},
        s_t{types::Types::Ghost,types::Types::Poison},
        LevelUpGroup::MediumSlowLevelUp,95,
        stats::SpeciesBaseStats{30,35,30100,80},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::Lick,moves::MoveId::ConfuseRay,moves::MoveId::NightShade}},
            //{27,{moves::MoveId::Hypnosis}},
            //{35,{moves::MoveId::DreamEater}},
        }
        ),
        MakeDictionaryPair<MockmonSpecies>(MockmonSpeciesId::Lapras,
        s_species{},
        s_t{types::Types::Water,types::Types::Ice},
        LevelUpGroup::SlowLevelUp,219,
        stats::SpeciesBaseStats{130,85,80,95,60},
        mp_i_vec_Mv{
            //moves list
            {1,{moves::MoveId::WaterGun,moves::MoveId::Growl}},
           // {16,{moves::MoveId::Sing}},
            //{20,{moves::MoveId::Mist}},
            {25,{moves::MoveId::BodySlam}},
            {31,{moves::MoveId::ConfuseRay}},
            {38,{moves::MoveId::IceBeam}},
            //{46,{moves::MoveId::HydroPump}},
        }
        ),

    };

}