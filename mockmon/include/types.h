#pragma once
#include <iostream>
namespace mockmon::types
{
    enum class Types
    {      
        Typeless,
        Normal,
        Water
    };
    std::ostream& operator<<(std::ostream& os,const Types& type);
}
