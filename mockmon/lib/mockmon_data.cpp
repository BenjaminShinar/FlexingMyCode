#include "mockmon_data.h"
#include "random_gen.h"

#include <cmath>
#include <algorithm>

namespace mockmon
{
    //this is too big a  class, we need to seperate the functionally accross some stuff
    
    const MockmonSpecies & Mockmon::GetMockmonSpeciesData() const
    {
        return MockmonSpecies::AllMockmons.at(m_currentSpeciesId);
    }

    unsigned int Mockmon::GetCurrentLevel() const
    {
        return CurrentLevel;
    }
    
    bool Mockmon::IsAbleToBattle() const 
    {
        return m_ableToBattle && CurrentStats.Health.GetStat() >0;
    }

    double Mockmon::ModifyAttackForCrticalHit(const moves::SimpleMove & AttackingMove)
    {
        
        auto baseChance =100* GetMockmonSpeciesData().MockmonSpeciesStats.Speed * AttackingMove.CriticalChanceBoost() / 512.0;
        if (baseChance > random::Randomer::GetRandom())
        {
            
            auto damageBoost = (5.0+(CurrentLevel*2.0))/(CurrentLevel + 5.0);
            if (m_outputEvents)
            {
                std::cout << m_name << " scored a critical hit" << " boost factor: " << damageBoost <<'\n';
            }
            return damageBoost;
        }
        return 1.0;
    }


    //do something else
    bool Mockmon::GetStabModifier(const moves::SimpleMove & AttackingMove) 
    {
        return GetMockmonSpeciesData().GetStabModifier(AttackingMove.Type);
    }
    
    types::TypeEffectivenessModifier Mockmon::GetTypeEffectivenessModifer(const moves::SimpleMove & AttackingMove) 
    {
        return GetMockmonSpeciesData().GetTypeEffetivenessModifier(AttackingMove.Type);
    }

    void Mockmon::LoseSomehow()
    {
        m_ableToBattle = false;
    }

    void Mockmon::FullRestore()
    {
        CurrentStats.Health.RestStatToMax();
        CurrentStats.Accuracy.ResetBoost();
        CurrentStats.Attack.ResetBoost();
        CurrentStats.Defence.ResetBoost();
        CurrentStats.Special.ResetBoost();
        CurrentStats.Speed.ResetBoost();
        m_ableToBattle = true;
    }

    bool Mockmon::TeachMove(moves::MoveId newMoveId)
    {
        if (m_Moveset.size() <=moves::EquipedMove::MaxMoves)
        {
            m_Moveset.push_back(moves::EquipedMove(moves::ConstantMove::AllMovesWrappers.at(newMoveId)));
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
        auto positivePoints = static_cast<unsigned long>(points);
        auto neededToNextLevelAbs = MockmonExp::TotalExperinceForLevel(CurrentLevel+1,GetMockmonSpeciesData().SpeciesLevelUpGroup);
        auto neededToNextLevel = neededToNextLevelAbs - experience_points;      
        //std::cout<< m_name << " required exp for nexy level " << level+1 << " is " << neededToNextLevelAbs <<'\n';
        auto reminder = positivePoints - neededToNextLevel;

        if (positivePoints < neededToNextLevel)
        {
            experience_points += positivePoints;
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
        return MockmonExp{CurrentLevel,experience_points};
    }
    void Mockmon::LevelUp()
    {
        auto nextLevel = CurrentLevel+1;
        if (m_outputEvents)
        {
            std::cout << m_name << " level increase! [" << CurrentLevel << " -> " << nextLevel << "]"<<'\n';
        }
        ++CurrentLevel;
        UpdateStats();
        LearnLevelUpMoves(CurrentLevel);
    }

     void Mockmon::UpdateStats()
     {
         CurrentStats.UpdateStats(Stats(GetMockmonSpeciesData().MockmonSpeciesStats,IVs,EVs,CurrentLevel));
     }

    void Mockmon::LearnLevelUpMoves(int newLevel)
    {
        const auto movesFromLevelUp = GetMockmonSpeciesData().LevelUpMoves;
        
        for (const auto & mvs :  movesFromLevelUp)
        {
            if (mvs.first == newLevel)
            {
                for (const auto & mv : mvs.second)
                {
                    auto exists = std::find_if(std::begin(m_Moveset),std::end(m_Moveset),[&](const moves::EquipedMove & knownMove){return knownMove.Identifier() == mv;});
                    if (exists == std::end(m_Moveset))
                    {                
                        TeachMove(mv);           
                    }
                }
            }
        }
    }
    
    void Mockmon::LearnLevelUpMoves()
    {
        const auto movesFromLevelUp = GetMockmonSpeciesData().LevelUpMoves;
        
        for (const auto & mvs :  movesFromLevelUp)
        {
            if (mvs.first <= CurrentLevel)
            {
                for (const auto & mv : mvs.second)
                {
                    auto exists = std::find_if(std::begin(m_Moveset),std::end(m_Moveset),[&](const moves::EquipedMove & knownMove){return knownMove.Identifier() == mv;});
                    if (exists == std::end(m_Moveset))
                    {                
                        TeachMove(mv);           
                    }
                }
            }
        }
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
        EVs+=defeatedMon.GetMockmonSpeciesData().MockmonSpeciesStats;
        GrantExperiencePoints(xp);
    }

    long Mockmon::ExpFromDefeating() const
    {  
        auto speciesXp = GetMockmonSpeciesData().SpeciesExp;
        auto xp = std::floor((CurrentLevel * speciesXp * (IsWild()? 1.0: 1.5)/7.0)) ;
        std::cout << GetName() << " was defeted! gives out " << xp << " xp points!" <<'\n';
        return xp;
    }
}