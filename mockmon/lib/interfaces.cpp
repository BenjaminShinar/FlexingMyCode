#include "interfaces.h"

namespace mockmon
{

/**
 * @brief 
 * like C# string.join(), but doesn't work properly.
 * always sticks an extra space at the end...
 * needs fixing, or a 3rd party library
 * @param words 
 * @return std::string 
 */
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