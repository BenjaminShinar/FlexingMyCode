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
       
}