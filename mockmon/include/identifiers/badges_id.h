#pragma once
#include <string>
#include <iostream>
namespace mockmon::badges
{
    const std::size_t IndigoBadgesNumber{8};
    //think about a way to put all the enums somewhere else, maybe template their << operator
    enum class IndigoBadge
    {
        Boulder_Badge,
        Cascage_Badge,
        Thunder_Badge,
        Rainbow_Badge,
        Soul_Badge,
        Marsh_Badge,
        Volcano_Badge,
        Earth_Badge
    };
    std::string Stringify(const IndigoBadge badge);
    std::ostream &operator<<(std::ostream &os, const IndigoBadge &e);

}