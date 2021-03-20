#include <types.h>

#include <string>
#include <iostream>
#include <sstream>

namespace mockmon::types
{

    std::string typeToStr(const Types type)
    {
        switch (type)
        {
        case Types::Typeless : return "Typeless";break;
        case Types::Water : return "Water";break;
        case Types::Normal : return "Noraml";break;
        default: return "Unknown Type!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const Types& type)
    {
        os << typeToStr(type);
        return os;
    }

}