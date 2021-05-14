#pragma once
#include <string>
#include <iostream>
namespace mockmon::moves
{
    enum class MovesTargeting
    {
        PurePhysical,
        PureSpecial,
    };
    std::string Stringify(const MovesTargeting movesTargeting);
    std::ostream &operator<<(std::ostream &os, const MovesTargeting &e);
}