#include "types.h"

#include <string>
#include <iostream>
#include <sstream>
#include <utility>

namespace mockmon::types
{

    std::string typeToStr(const Types type)
    {
        switch (type)
        {
            case Types::Typeless : return "Typeless";break;
            case Types::Normal : return "Noraml";break;
            case Types::Fire : return "Fire"; break;
            case Types::Water : return "Water";break;
            case Types::Electric : return "Electric"; break;
            case Types::Grass : return "Grass"; break;
            case Types::Ice : return "Ice"; break;
            case Types::Fighting : return "Fighting"; break;
            case Types::Poison : return "Poison"; break;
            case Types::Ground : return "Ground"; break;
            case Types::Flying : return "Flying"; break;
            case Types::Psychic : return "Psychic"; break;
            case Types::Bug : return "Bug"; break;
            case Types::Rock : return "Rock"; break;
            case Types::Ghost : return "Ghost"; break;
            case Types::Dragon : return "Dragon"; break;
            case Types::Dark : return "Dark"; break;
            case Types::Steel : return "Steel"; break;
            case Types::Fairy : return "Fairy"; break;
            default: return "Unknown Type!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const Types& type)
    {
        os << typeToStr(type);
        return os;
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