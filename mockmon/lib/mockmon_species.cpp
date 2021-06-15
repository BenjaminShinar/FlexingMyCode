#include "mockmon_species.h"
#include <cmath>
#include <algorithm>
#include <interfaces.h>

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

    bool MockmonSpecies::IsSpeciesOfType(types::Types type) const
    {
        auto matchedType = SpeciesTypes.find(type);
        return (matchedType != SpeciesTypes.end());
    }

}