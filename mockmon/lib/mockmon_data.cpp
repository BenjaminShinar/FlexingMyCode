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
        return m_ableToBattle && CurrentBattleStats.Health.GetStat() >0;
    }

    void Mockmon::LoseSomehow()
    {
        m_ableToBattle = false;
    }

    void Mockmon::FullRestore()
    {
        CurrentBattleStats.Health.RestStatToMax();
        for (auto & stat : CurrentBattleStats.m_battleStats)
        {
            stat.second.ResetBoost();
        }
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

    void Mockmon::TryEvolve()
    {
        if (!GetMockmonSpeciesData().PossibleEvolutions.empty())
        {
            m_currentSpeciesId=*std::begin(GetMockmonSpeciesData().PossibleEvolutions);
            UpdateBaseStats();
        }
    }
/**
 * @brief 
 * returns changeble version of the move set, 
 * use in actual battle
 * @return std::vector<moves::EquipedMove>& 
 */
    std::vector<moves::EquipedMove> & Mockmon::GetMoveSet()
    {
        return m_Moveset;
    }

/**
 * @brief 
 * return a none-changble version of the move set, 
 * use for making decisions
 * @return const std::vector<moves::EquipedMove>& 
 */
    const std::vector<moves::EquipedMove> & Mockmon::ViewMoveSet() const
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
        if (m_outputEvents)
        {
            std::cout << m_name << " level increase! [" << CurrentLevel << " -> " << (CurrentLevel+1) << "]"<<'\n';
        }
        ++CurrentLevel;
        UpdateBaseStats();
        LearnLevelUpMoves(CurrentLevel);
    }

     void Mockmon::UpdateBaseStats()
     {
         CurrentBattleStats.UpdateBattleStats(stats::MockmonStats(GetMockmonSpeciesData().MockmonSpeciesStats,IVs,EVs,CurrentLevel));
     }

    void TeachMoves(Mockmon & m,const std::vector<moves::MoveId> & mvs)
    {
        const auto & mvset = m.ViewMoveSet();
        for (const auto & mv : mvs)
        {
            if (!std::any_of(std::begin(mvset),std::end(mvset),[&](const moves::EquipedMove & knownMove){return knownMove.IsSameAs(mv);}))
            {                
                m.TeachMove(mv);           
            }
        }
    }

    void Mockmon::LearnLevelUpMoves(int newLevel)
    {
        const auto movesFromLevelUp = GetMockmonSpeciesData().LevelUpMoves;
        
        for (const auto & mvs :  movesFromLevelUp)
        {
            if (mvs.first == newLevel)
            {
                TeachMoves(*this,mvs.second);
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
                TeachMoves(*this,mvs.second);
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
    
    
    void Mockmon::GainEffortValueFromVictory(const Mockmon & defeatedMon)
    {
        EVs.GainEffortValueStats(defeatedMon.GetMockmonSpeciesData().MockmonSpeciesStats);
    }

    void Mockmon::GainExperienceFromVictory(const Mockmon & defeatedMon)
    {
        GainEffortValueFromVictory(defeatedMon);

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
            std::cout << AppendAll({GetName(),"gain" ,std::to_string(xp),"xp points!"}) <<'\n';
        }
        GrantExperiencePoints(xp);
    }

    long Mockmon::ExpFromDefeating() const
    {  
        auto speciesXp = GetMockmonSpeciesData().SpeciesExp;
        auto xp = std::floor((CurrentLevel * speciesXp * (IsWild()? 1.0: 1.5)/7.0)) ;
        std::cout << AppendAll({GetName(),"was defeted! gives out" ,std::to_string(xp),"xp points!"}) <<'\n';
        return xp;
    }
}