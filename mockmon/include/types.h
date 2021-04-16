#pragma once
#include <iostream>
#include <vector>
#include <map>

namespace mockmon::types
{
    enum class TypeEffectivenessModifier
    {   
        NotEffective,
        VeryNotEffective, 
        NotVeryEffective,
        NormalEffective,
        VeryEffective,
        SuperEffective, //4.0
    };
    std::ostream& operator<<(std::ostream& os,const TypeEffectivenessModifier& typeEffectivenessModifier);
    TypeEffectivenessModifier CombineTypeModifiers(TypeEffectivenessModifier lhs,TypeEffectivenessModifier rhs);

    enum class Types
    {      
        Typeless,
        Normal,
        Fire,
        Water,
        Electric,
        Grass,
        Ice,
        Fighting,
        Poison,
        Ground,
        Flying,
        Psychic,
        Bug,
        Rock,
        Ghost,
        Dragon,
        Dark,
        Steel,
        Fairy
    };
    std::ostream& operator<<(std::ostream& os,const Types& type);
    
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
