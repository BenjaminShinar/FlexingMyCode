#pragma once

#include <string>
#include <iostream>
#include <algorithm>

namespace mockmon
{
   
   
    struct IndividualStats
    {
        explicit IndividualStats(unsigned int attack,unsigned int defence,unsigned int special,unsigned int speed):
        Attack(attack),
        Defence(defence),
        Special(special),
        Speed(speed),
        Health(CalculateHealth())
        {

        }

        explicit IndividualStats():
        Attack(9),
        Defence(8),
        Special(8),
        Speed(8),
        Health(CalculateHealth())
        {

        }
        
        const unsigned int Attack;
        const unsigned int Defence;
        const unsigned int Special;
        const unsigned int Speed;
        const unsigned int Health;
        private:
        unsigned int CalculateHealth() const
        {
            auto a1 = (Attack & 0x1) <<0;
            auto a2 = (Defence & 0x1) <<1;
            auto a3 = (Speed & 0x1) << 2;
            auto a4 = (Special & 0x1) <<3;

            return (a1 |a2 |a3|a4);
        }
    };
 
     struct SpeciesStats
    {

        const unsigned int Attack{1};
        const unsigned int Defence{1};
        const unsigned int Special{1};
        const unsigned int Speed{1};
        const unsigned int Health{1};
    };
    //think about how this should work
    struct Stats
    {
        // base, iv,evs
        explicit Stats() = default;
        Stats(unsigned int health,unsigned int attack,unsigned int defence,unsigned int special,unsigned int speed):
        Health(health),Attack(attack),Defence(defence),Special(special),Speed(speed)
        {

        }
        Stats(const SpeciesStats & baseStats,const IndividualStats & IVStats,const Stats & EVStats, unsigned int level);

        unsigned int Health = 1;
        unsigned int Attack = 9;
        unsigned int Defence = 8;
        unsigned int Special = 8;
        unsigned int Speed = 8;
        
        Stats& operator+=(const SpeciesStats&);
        //Stats& operator= (const Stats&);

        private:
        const unsigned int MaxStatValue = 65535;
        unsigned int ModifyStat(unsigned int base, unsigned int iv, unsigned int ev, unsigned int level);
    };

    template<typename T>
    class BattleSingleStat
    {
        public:
        BattleSingleStat(T statValue ):m_stat(statValue){}
        T GetStat() const {return m_stat* m_currentBoost;};
        void ResetBoost() {m_currentBoost = 1.0;}
        void ChangeBoost(double boost) {m_currentBoost+=boost;};
        void ChangeStat(T statValue) {m_stat= statValue;}

        private:
        T m_stat;
        double m_currentBoost{1.0};
    };

    
    class HealthStat
    {
        public:
        HealthStat(int statValue ):m_max_stat(statValue),m_current_stat(statValue){}
        int GetStat() const {return m_current_stat;}
        void RestStatToMax() {m_current_stat = m_max_stat;}
        void ChangeHealth(int statChange) {ChangeCurrentStat(m_current_stat+statChange);}
        void ChangeStatMax(int statValue) {m_max_stat = statValue;}

        private:
        void ChangeCurrentStat(int statChange) {m_current_stat = std::clamp(statChange,0,m_max_stat);}
        int m_max_stat;
         int m_current_stat;
    };

    struct BattleStats
    {

        explicit BattleStats() = default;
        BattleStats(const Stats & stats):
        Health(stats.Health),
        Attack(stats.Attack),
        Defence(stats.Defence),
        Special(stats.Special),
        Speed(stats.Speed)
        {
        }

        void UpdateStats(const Stats & stats)
        {
            Health.ChangeStatMax(stats.Health);
            Attack.ChangeStat(stats.Attack);
            Defence.ChangeStat(stats.Defence);
            Special.ChangeStat(stats.Special);
            Speed.ChangeStat(stats.Speed);
        }


        HealthStat Health{1}; //this should be special
        BattleSingleStat<unsigned int> Attack{1};
        BattleSingleStat<unsigned int> Defence{1};
        BattleSingleStat<unsigned int> Special{1};
        BattleSingleStat<unsigned int> Speed{1};
        BattleSingleStat<double> Accuracy{100.0};

    };
}