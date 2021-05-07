#include "identifiers/types_id.h"

namespace mockmon::types
{

    std::string Stringify(const Types type)
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
    std::ostream &operator<<(std::ostream &os, const Types &e)
    {
        os << Stringify(e);
        return os;
    }

}