#pragma once

#include "interfaces.h"
#include <iostream>


//this is the base class of each mockmon, the shared data between them.
namespace mockmon
{
    enum class MockmonSpeciesId
    {      
        Ratata,
        Raticate,
        Mew,
        Weedle,
        UknownSpecies
    };

    std::ostream& operator<<(std::ostream& os,const MockmonSpeciesId& mockmonSpeciesId);
    
}