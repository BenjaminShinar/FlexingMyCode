#pragma once
#include <iostream>
#include <vector>
#include <map>

namespace mockmon::types
{
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
        explicit TypeEffectivness(Types t,const std::vector<Types> & doubleEffect,const std::vector<Types> & halfEffect,const std::vector<Types> & noEffect)
        :
        AttackingType(t),DoesDoubleEffectiveTypes(doubleEffect),DoesHalfEffectiveTypes(halfEffect),DoesNothingEffectiveTypes(noEffect)
        {}
        const Types AttackingType;
        const std::vector<Types> DoesDoubleEffectiveTypes;
        const std::vector<Types> DoesHalfEffectiveTypes;
        const std::vector<Types> DoesNothingEffectiveTypes;

public:
        static std::map<Types,TypeEffectivness> TypeEffectiveChart;
    };
}
