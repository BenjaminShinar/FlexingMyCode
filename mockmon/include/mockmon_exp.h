#pragma once

#include <string>
#include <iostream>

namespace mockmon
{

    struct MockmonExp
    {      
        const long CurrentLevel;
        const long CurrentExperience;

        friend std::ostream& operator<<(std::ostream& os,const MockmonExp& mx);

    };
}