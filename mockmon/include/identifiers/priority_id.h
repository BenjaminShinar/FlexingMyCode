#pragma once
#include <string>
#include <iostream>
namespace mockmon::moves   
{
    enum class Priority
    {      
        NegativePriority,
        Normal,
        PositivePriority
    };
    std::string Stringify(const Priority priority);
    std::ostream &operator<<(std::ostream &os, Priority priority);

}