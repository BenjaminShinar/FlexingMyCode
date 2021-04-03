#include "stats.h"
#include <cmath>
namespace mockmon
{
    
    //this happens when we beat an enemy and gain EVS
    Stats& Stats::operator+=(const Stats& otherStats)
    {
      Health = std::min(Health+otherStats.Health,MaxStatValue);
      Attack = std::min(Attack+otherStats.Attack,MaxStatValue);
      Defence = std::min(Defence+otherStats.Defence,MaxStatValue);
      Special = std::min(Special+otherStats.Special,MaxStatValue);
      Speed = std::min(Speed+otherStats.Speed,MaxStatValue);
      return *this;
    }

    //this happens when we beat an enemy and gain EVS
    Stats& Stats::operator=(const Stats& otherStats)
    {
      Health = std::min(otherStats.Health,MaxStatValue);
      Attack = std::min(otherStats.Attack,MaxStatValue);
      Defence = std::min(otherStats.Defence,MaxStatValue);
      Special = std::min(otherStats.Special,MaxStatValue);
      Speed = std::min(otherStats.Speed,MaxStatValue);
      return *this;
    }


    //this is the level up stats Increase
    Stats::Stats(const Stats & baseStats,const Stats & IVStats,const Stats & EVStats, unsigned int level)
    {
        Health = std::min(ModifyStat(baseStats.Health,IVStats.Health,EVStats.Health,level)+level+10,MaxStatValue);;
        Attack = std::min(ModifyStat(baseStats.Attack,IVStats.Attack,EVStats.Attack,level)+5,MaxStatValue);
        Defence = std::min(ModifyStat(baseStats.Defence,IVStats.Defence,EVStats.Defence,level)+5,MaxStatValue);;
        Special= std::min(ModifyStat(baseStats.Special,IVStats.Special,EVStats.Special,level)+5,MaxStatValue);;
        Speed = std::min(ModifyStat(baseStats.Speed,IVStats.Speed,EVStats.Speed,level)+5,MaxStatValue);
    }
    unsigned int Stats::ModifyStat(unsigned int base, unsigned int iv, unsigned int ev, unsigned int level)
    {
        auto stat = std::floor(((base + iv)*2 + (sqrt(ev)/4.0)*level)/100);
        return stat;
    }
}