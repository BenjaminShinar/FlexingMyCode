#include "speciesId.h"

#include <iostream>


//this is the base class of each mockmon, the shared data between them.
namespace mockmon
{
    std::string speciesToStr(const MockmonSpeciesId speceis)
    {
        switch (speceis)
        {
        case MockmonSpeciesId::Mew : return "Mew";break;
        case MockmonSpeciesId::Ratata : return "Ratata";break;
        case MockmonSpeciesId::Raticate : return "Raticate"; break;
        default: return "Unknown mockmon!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const MockmonSpeciesId& speceis)
    {
        os << speciesToStr(speceis);
        return os;
    }
}