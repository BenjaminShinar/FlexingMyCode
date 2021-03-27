#pragma once

#include <string>
#include <iostream>



namespace mockmon
{
   
    //think about how this should work
    struct Stats
    {
        // base, iv,evs
        explicit Stats() = default;
        Stats(unsigned int health,unsigned int attack,unsigned int defence,unsigned int special,unsigned int speed):
        Health(health),Attack(attack),Defence(defence),Special(special),Speed(speed)
        {

        }
        Stats(const Stats & baseStats,const Stats & IVStats,const Stats & EVStats, unsigned int level);

        unsigned int Health =1;
        unsigned int Attack = 1;
        unsigned int Defence = 1;
        unsigned int Special = 1;
        unsigned int Speed = 1;
        
        Stats& operator+=(const Stats&);

        private:
        const unsigned int MaxStatValue = 65535;
        unsigned int ModifyStat(unsigned int base, unsigned int iv, unsigned int ev, unsigned int level);
    };


}