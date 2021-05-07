#include "interfaces.h"

namespace mockmon
{



    std::string AppendAll(const std::initializer_list<std::string_view> &words)
    {
        
        std::string s;
        for (const auto &word : words)
        {
            s.append(std::string(word)).append(" ");
        }

        return s;
    }
}