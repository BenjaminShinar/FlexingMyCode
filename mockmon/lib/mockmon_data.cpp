#include "mockmon_data.h"
#include <cmath>

namespace mockmon
{
    bool Mockmon::IsAbleToBattle() const {return m_ableToBattle;}
    void Mockmon::LoseSomehow()
    {
        m_ableToBattle = false;
    }
    void Mockmon::FullRestore()
    {
        m_ableToBattle = true;
    }
    void Mockmon::GrantExperiencePoints(long points)
    {
        if (points <= 0) return;
        auto neededToNextLevelAbs =((level+1)*(level+2)) / 2 *100;
        auto neededToNextLevel = neededToNextLevelAbs - experience_points;
        
        //std::cout<< m_name << " required exp for nexy level " << level+1 << " is " << neededToNextLevelAbs <<'\n';
        auto reminder = points - neededToNextLevel;

        if (points < neededToNextLevel)
        {
            experience_points += points;
            //std::cout<< m_name << " cant increase it's level! has " << experience_points << " and needs total of: " << neededToNextLevelAbs <<'\n';

        }
        else
        {
            experience_points += neededToNextLevel;
            LevelUp();
            GrantExperiencePoints(reminder);
        }
    }

    //level 1: 0 -100
    //level 2: 100-300
    //level 3: 300 - 600
    //level 4: 600 - 1000
    //level 5: 1500 - 2100
    //level 6: 2100 - 2700
    void Mockmon::LevelUp()
    {
        auto nextLevel = level+1;
        if (m_outputEvents)
        {
            std::cout << m_name << " level increase! [" << level << " -> " << nextLevel << "]"<<'\n';
        }
        ++level;
        //evolve?

    }

    void Mockmon::ChangeName(const std::string & newName)
    {
        m_name = newName;
    }

    void Mockmon::GainExperienceFromVictory(const Mockmon & defeatedMon)
    {

        //https://bulbapedia.bulbagarden.net/wiki/Experience#Experience_gain_in_battle
        //exp = (a*t*b*e*L*p*f*V) / (7 *s)

        auto participatingPokemonInWinningTeam = 1;

        // auto ExtraFromAbility = false; //p
        // auto ExtraFromTraded = false; //t
        // auto IsPastEvolution = false; //v

        //t*e*p*f*v
        //originalOwner * Egg * powerSomething * Affection * PastEvolutin
        auto NominatorModifiers = 1;
        //a*b*L
        auto NominatorValue = defeatedMon.ExpFromDefeating();

        //7*s
        auto Denominator = 1* participatingPokemonInWinningTeam; //number of participating pokmon;

        long xp =static_cast<long>(std::floor((NominatorValue*NominatorModifiers)/Denominator));
        if (m_outputEvents)
        {
            std::cout << m_name << " gain " << xp << " xp points!" <<'\n';
        }
        GrantExperiencePoints(xp);
    }

    long Mockmon::ExpFromDefeating() const
    {

         
        auto xp = std::floor(level * m_speciesExp * (IsWild()? 1.0: 1.2));
        std::cout << m_name << " gives out " << xp << " xp points!" <<'\n';
        return xp;
    }
    std::ostream& operator<<(std::ostream& os,const MockmonExp& mx)
    {
        os << "Level: " << mx.CurrentLevel << " Exp: " << mx.CurrentExperience;
        return os;
    }
}