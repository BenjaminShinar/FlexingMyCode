#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "identifiers/types_id.h"
#include "identifiers/type_effectiveness_id.h"

namespace mockmon::types
{

    TypeEffectivenessModifier CombineTypeModifiers(TypeEffectivenessModifier lhs,TypeEffectivenessModifier rhs);


    class TypeEffectivness
    {
public:
        const Types AttackingType;
        TypeEffectivenessModifier GetTypeModifier(Types type) const;
        bool DoubleEffective (Types type) const;
        bool HalfEffective (Types type) const;
        bool NoEffective (Types type) const;

private:
        explicit TypeEffectivness(Types t,const std::vector<Types> & doubleEffect,const std::vector<Types> & halfEffect,const std::vector<Types> & noEffect)
        :
        AttackingType(t),DoesDoubleEffectiveTypes(doubleEffect),DoesHalfEffectiveTypes(halfEffect),DoesNothingEffectiveTypes(noEffect)
        {}

        const std::vector<Types> DoesDoubleEffectiveTypes;
        const std::vector<Types> DoesHalfEffectiveTypes;
        const std::vector<Types> DoesNothingEffectiveTypes;


public:
        static std::map<Types,TypeEffectivness> TypeEffectiveChart;
    };
}
