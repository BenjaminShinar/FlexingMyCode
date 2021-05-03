#include "mockmon_species.h"
#include <cmath>
#include <algorithm>

namespace mockmon
{

    types::TypeEffectivenessModifier MockmonSpecies::GetTypeEffetivenessModifier(types::Types attackingMoveType) const
    {
        using types::TypeEffectivenessModifier;
        
        auto typeEffectives = types::TypeEffectivness::TypeEffectiveChart.at(attackingMoveType);

        const auto TypesNumber = SpeciesTypes.size();
        std::vector<types::TypeEffectivenessModifier> modifiers(TypesNumber);
        std::transform(std::begin(SpeciesTypes),std::end(SpeciesTypes),std::begin(modifiers),[&typeEffectives](const auto & type)
        {   
            return  typeEffectives.GetTypeModifier(type);
        });

        if (TypesNumber == 1)
            return modifiers.front();
        if (TypesNumber == 2)
            return CombineTypeModifiers(modifiers.front(),modifiers.back());
        
        return TypeEffectivenessModifier::NormalEffective;
    }

    bool MockmonSpecies::GetStabModifier(types::Types attackingMoveType) const
    {
        auto stabType = SpeciesTypes.find(attackingMoveType);
        return (stabType != SpeciesTypes.end());
    }

    const std::map<MockmonSpeciesId,MockmonSpecies> MockmonSpecies::AllMockmons
    {
        //explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,long speciesExp,Stats & sepeciesStats,const std::map<int,moves::MoveId> & levelUpMovesList);
        {MockmonSpeciesId::Mew, MockmonSpecies(MockmonSpeciesId::Mew,
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
            // {7,{moves::MoveId::QuickAttack}},
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