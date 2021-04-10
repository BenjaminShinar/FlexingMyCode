#include "mockmon_data.h"
#include "random_gen.h"

#include <cmath>
#include <algorithm>

namespace mockmon
{
    const MockmonSpecies & Mockmon::GetMockmonSpeciesData() const
    {
        return MockmonSpecies::AllMockmons.at(m_currentSpeciesId);
    }

    bool Mockmon::IsAbleToBattle() const 
    {
        return m_ableToBattle && m_currentCondtion.HP() >0;
    }

    void Mockmon::AttackWith(Mockmon & enemy, moves::MoveId mvid)
    {
        auto chosenMove = std::find_if(m_Moveset.begin(),m_Moveset.end(),[&](const moves::EquipedMove  & mv ){ return mv.Identifier() == mvid;});
        
        if (chosenMove != m_Moveset.end() && chosenMove->RemainningPowerPoints()>0)
        {
            if (chosenMove->UseMove())
            {
                auto damage = ModifyAttack(moves::BaseMove::AllMoves.at(chosenMove->Identifier()),enemy);
                std::cout<< GetName() << " hit " << enemy.GetName() <<" with " << (*chosenMove).Identifier() <<" for " << damage << " damage!" << '\n';
                enemy.m_currentCondtion.ChangeHealth(-1* damage);
            }
            else
            {
                std::cout<< GetName() << " missed with " << (*chosenMove).Identifier() << '\n';
            }  
        }
        else
        {
            const auto struggleMove = moves::BaseMove::AllMoves.at(moves::MoveId::Struggle);
            if (moves::CheckMoveAccuracy(struggleMove))
            {
                auto damage = ModifyAttack(struggleMove,enemy);
                auto recoilDamage = std::max(1,damage/2);
                std::cout<< GetName() << " struggles with  " << enemy.GetName() <<" and managed to hit for " << damage << " damage!" << '\n';
                std::cout<< GetName() << " takes " << recoilDamage << " recoile damage while struggling!" << '\n';
                enemy.m_currentCondtion.ChangeHealth(-1* damage);
                m_currentCondtion.ChangeHealth(-1* recoilDamage);
            }
            else
            {
                std::cout<< GetName() << " missed with " << struggleMove.Identifier() << '\n';
            }
        }
        
    }

    int Mockmon::ModifyAttack(const moves::BaseMove & AttackingMove, const Mockmon & target)
    {
        auto baseDamage = AttackingMove.BasePower;
        auto levelModifier = 2+((2*CurrentLevel)/5);
        auto  statsModifier = CurrentStats.Attack / target.CurrentStats.Defence; //attack / defence
        auto criticalHitModifier {ModifyAttackForCrticalHit(AttackingMove,target)};
        auto typeEffectivenessAndStab {ModifyAttackForType(AttackingMove,target)};
        auto  extraModifier = 1 * criticalHitModifier * typeEffectivenessAndStab ; // stab, type, weahter, badge,status,
        return (extraModifier*(2+((levelModifier* baseDamage * statsModifier)/50)));
    }

    double Mockmon::ModifyAttackForCrticalHit(const moves::BaseMove & AttackingMove,const Mockmon & target)
    {
        
        auto baseChance =100* GetMockmonSpeciesData().SpeciesStats.Speed * AttackingMove.CriticalChanceBoost() / 512.0;
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

    double Mockmon::ModifyAttackForType(const moves::BaseMove & AttackingMove,const Mockmon & target)
    {
        auto stabModifier = AttackingMove.Type == GetMockmonSpeciesData().SpeciesType ? 1.5 : 1.0;
        auto sameTypeResistance = AttackingMove.Type == target.GetMockmonSpeciesData().SpeciesType ? 0.75 : 1.0;
        //need type weakness chart
        //what if something else?
        return stabModifier* sameTypeResistance;

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
         CurrentStats = Stats(GetMockmonSpeciesData().SpeciesStats,IVs,EVs,CurrentLevel);
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
        EVs+=defeatedMon.GetMockmonSpeciesData().SpeciesStats;
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