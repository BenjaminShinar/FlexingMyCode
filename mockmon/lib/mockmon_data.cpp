#include "mockmon_data.h"
#include <cmath>
#include <algorithm>

namespace mockmon
{
    bool Mockmon::IsAbleToBattle() const 
    {
        return m_ableToBattle && m_currentCondtion.HP() >0;
    }

    void Mockmon::AttackWith(Mockmon & enemy, moves::MoveId mvid)
    {
        auto chosenMove = std::find_if(m_Moveset.begin(),m_Moveset.end(),[&](const moves::EquipedMove  & mv ){ return mv.Identifier() == mvid;});
        if (chosenMove != m_Moveset.end())
        {
            auto usedPower = chosenMove->UseMove();
            if (usedPower.has_value())
            {
                auto damage = ModifyAttack(usedPower.value_or(0),enemy);          
                std::cout<< GetName() << " hit " << enemy.GetName() <<" with " << (*chosenMove).Identifier() <<" for " << damage << " damage!" << '\n';
                enemy.m_currentCondtion.ChangeHealth(-1* damage);
            }
            else
            {
                std::cout<< GetName() << " missed with " << (*chosenMove).Identifier() << '\n';
            }
                
        }
        
    }

    int Mockmon::ModifyAttack(const int baseDamage,const Mockmon & target) const
    {
        auto levelModifier = 2+((2*level)/5);
        auto extraModifier = 1; //attack / defence
        auto statsModifier = 1; // stab? all others
        return (extraModifier*(2+((levelModifier* baseDamage * statsModifier)/50)));
    }

    void Mockmon::LoseSomehow()
    {
        m_ableToBattle = false;
    }
    void Mockmon::FullRestore()
    {
        auto amountToMax = 100 - m_currentCondtion.HP();
        m_currentCondtion.ChangeHealth(amountToMax);
        m_ableToBattle = true;
    }
    bool Mockmon::TeachMove(moves::MoveId newMoveId)
    {
        if (m_Moveset.size() <=moves::EquipedMove::MaxMoves)
        {
            m_Moveset.push_back(moves::EquipedMove(moves::BaseMove::AllMoves.at(newMoveId)));
            if (m_outputEvents)
            {
                std::cout << m_name << " learned [" << newMoveId << "]"<<'\n';
            } 
            return true;
        }
        if (m_outputEvents)
        {
            std::cout << m_name << " cant learn [" << newMoveId << "]"<<'\n';
        } 
        return false;
    }
    const std::vector<moves::EquipedMove> & Mockmon::GetMoveSet() const
    {
        return m_Moveset;
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
    MockmonExp Mockmon::CheckExperiencePoints() const 
    {
        return MockmonExp{level,experience_points};
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
    std::string_view Mockmon::GetName() const
    {
        return m_name;
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
            std::cout << GetName() << " gain " << xp << " xp points!" <<'\n';
        }
        EVs+=defeatedMon.BaseTypeStats;
        GrantExperiencePoints(xp);
    }

    long Mockmon::ExpFromDefeating() const
    {  
        auto xp = std::floor(level * m_speciesExp * (IsWild()? 1.0: 1.2));
        std::cout << GetName() << " was defeted! gives out " << xp << " xp points!" <<'\n';
        return xp;
    }
}