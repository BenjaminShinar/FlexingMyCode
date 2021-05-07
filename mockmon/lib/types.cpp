#include "types.h"

#include <string>
#include <iostream>
#include <sstream>
#include <utility>
#include <vector>
#include <algorithm>

namespace mockmon::types
{

    TypeEffectivenessModifier TypeEffectivness::GetTypeModifier(Types defendingType) const
    {
        auto doubleEffect = DoubleEffective(defendingType);
        auto noEffect = NoEffective(defendingType);
        auto halfEffective = HalfEffective(defendingType);

        if (doubleEffect)
        {
            std::cout<<  AttackingType << " is double effective against " << defendingType <<'\n';
            return TypeEffectivenessModifier::VeryEffective;
        }
        if (noEffect)
            return TypeEffectivenessModifier::NotEffective;

        if (halfEffective)
            return TypeEffectivenessModifier::NotVeryEffective;
        
        return TypeEffectivenessModifier::NormalEffective;
    }
    TypeEffectivenessModifier CombineTypeModifiers(TypeEffectivenessModifier lhs,TypeEffectivenessModifier rhs)
    {
        if (lhs == TypeEffectivenessModifier::NormalEffective)
            return rhs;
        if (rhs == TypeEffectivenessModifier::NormalEffective)
            return lhs;

        if (lhs == TypeEffectivenessModifier::NotVeryEffective && rhs == TypeEffectivenessModifier::NotVeryEffective)
            return TypeEffectivenessModifier::NotVeryEffective;

        if (lhs == TypeEffectivenessModifier::VeryEffective && rhs == TypeEffectivenessModifier::VeryEffective)
            return TypeEffectivenessModifier::SuperEffective;

        if ((lhs == TypeEffectivenessModifier::VeryEffective && rhs == TypeEffectivenessModifier::NotVeryEffective) ||
            (lhs == TypeEffectivenessModifier::NotVeryEffective && rhs == TypeEffectivenessModifier::VeryEffective))
            return TypeEffectivenessModifier::NormalEffective;

        if ((lhs == TypeEffectivenessModifier::VeryEffective && rhs == TypeEffectivenessModifier::NotEffective) ||
            (lhs == TypeEffectivenessModifier::NotEffective && rhs == TypeEffectivenessModifier::VeryEffective))
            return TypeEffectivenessModifier::NotVeryEffective;

        if ((lhs == TypeEffectivenessModifier::NotVeryEffective && rhs == TypeEffectivenessModifier::NotEffective) ||
            (lhs == TypeEffectivenessModifier::NotEffective && rhs == TypeEffectivenessModifier::NotVeryEffective))
            return TypeEffectivenessModifier::NotEffective;

        return TypeEffectivenessModifier::NormalEffective;
    }


    bool TypeEffectivness::DoubleEffective (Types defendingType) const
    {
        const auto pos = std::find(std::begin(DoesDoubleEffectiveTypes),std::end(DoesDoubleEffectiveTypes),defendingType);
        return pos != std::end(DoesDoubleEffectiveTypes);
    }
    
    bool TypeEffectivness::HalfEffective (Types defendingType) const
    {
        const auto pos = std::find(std::begin(DoesHalfEffectiveTypes),std::end(DoesHalfEffectiveTypes),defendingType);
        return pos != std::end(DoesHalfEffectiveTypes);
    }

    bool TypeEffectivness::NoEffective (Types defendingType) const
    {
        const auto pos = std::find(std::begin(DoesNothingEffectiveTypes),std::end(DoesNothingEffectiveTypes),defendingType);
        return pos != std::end(DoesNothingEffectiveTypes);
    }

        
    std::map<Types,TypeEffectivness> TypeEffectivness::TypeEffectiveChart
    {
        {Types::Typeless,TypeEffectivness{Types::Typeless,{},{},{}}},
        {Types::Normal,TypeEffectivness{Types::Normal,{},{Types::Rock,Types::Steel},{Types::Ghost}}},
        {Types::Fire, TypeEffectivness{Types::Fire,{Types::Grass,Types::Ice,Types::Bug, Types::Steel},{Types::Fire,Types::Water,Types::Rock,Types::Dragon},{}}},
        {Types::Water, TypeEffectivness{Types::Water,{Types::Fire,Types::Ground,Types::Rock},{Types::Water,Types::Grass,Types::Dragon},{}}},
        {Types::Electric, TypeEffectivness{Types::Electric,{Types::Water,Types::Flying},{Types::Electric,Types::Ground,Types::Dragon},{Types::Ground}}},
        {Types::Grass, TypeEffectivness{Types::Grass,{Types::Water,Types::Rock,Types::Ground},{Types::Fire,Types::Fire,Types::Poison,Types::Bug,Types::Dragon,Types::Steel},{}}},
        {Types::Ice, TypeEffectivness{Types::Ice,{Types::Grass,Types::Ground,Types::Flying,Types::Dragon},{Types::Fire,Types::Water,Types::Ice,Types::Steel},{}}},
        {Types::Fighting, TypeEffectivness{Types::Fighting,{Types::Normal,Types::Ice,Types::Rock,Types::Dark,Types::Steel},{Types::Poison,Types::Flying,Types::Psychic,Types::Bug,Types::Fairy},{Types::Ghost}}},
        {Types::Poison, TypeEffectivness{Types::Poison,{Types::Grass,Types::Fairy},{Types::Poison,Types::Flying,Types::Rock,Types::Ghost},{Types::Steel}}},
        {Types::Ground, TypeEffectivness{Types::Ground,{Types::Fire,Types::Electric,Types::Poison,Types::Rock,Types::Steel},{Types::Grass,Types::Bug},{Types::Ground}}},
        {Types::Flying, TypeEffectivness{Types::Flying,{Types::Grass,Types::Fighting,Types::Bug},{Types::Electric,Types::Rock,Types::Steel},{}}},
        {Types::Psychic, TypeEffectivness{Types::Psychic,{Types::Fighting,Types::Poison},{Types::Bug,Types::Steel},{Types::Dark}}},        
        {Types::Bug, TypeEffectivness{Types::Bug,{Types::Grass,Types::Psychic,Types::Dark},{Types::Fire,Types::Fighting,Types::Poison,Types::Flying,Types::Ghost,Types::Steel,Types::Fairy},{}}},
        {Types::Rock, TypeEffectivness{Types::Rock,{Types::Water,Types::Ice,Types::Flying,Types::Bug},{Types::Fighting,Types::Ground,Types::Steel},{}}},
        {Types::Ghost, TypeEffectivness{Types::Ghost,{Types::Psychic,Types::Ghost},{Types::Dark},{Types::Normal}}},
        {Types::Dragon, TypeEffectivness{Types::Dragon,{Types::Dragon},{Types::Steel},{Types::Fairy}}},
        {Types::Dark, TypeEffectivness{Types::Dark,{Types::Psychic,Types::Ghost},{Types::Fighting,Types::Dark,Types::Fairy},{}}},
        {Types::Steel, TypeEffectivness{Types::Steel,{Types::Ice,Types::Rock,Types::Fairy},{Types::Fire,Types::Water,Types::Electric,Types::Steel},{}}},
        {Types::Fairy, TypeEffectivness{Types::Fairy,{Types::Fighting,Types::Dragon,Types::Dark},{Types::Fire,Types::Poison,Types::Steel},{}}},
     };
}