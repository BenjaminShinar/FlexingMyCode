#pragma once

namespace mockmon
{

    
    //this class will be used to control weahter, screens, entry hazzards, etc...

    class Arena
    {   public:
        explicit Arena(bool silent):Silent(silent)
        {}
        explicit Arena(const Arena & other)=default;
        
        ~Arena()=default;
        const bool Silent;
    };
}