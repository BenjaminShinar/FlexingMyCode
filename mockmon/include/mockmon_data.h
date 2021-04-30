#pragma once

#include "moves.h"
//#include <string_view>
#include <string>
#include <iostream>
#include <vector>

#include "condition.h"
#include "stats.h"
#include "mockmon_species.h"
#include "mockmon_exp.h"

namespace mockmon
{
    class Mockmon
    {   
        friend class Battle;
        public:
        explicit Mockmon(MockmonSpeciesId species,const std::string & name,bool silent = false)
        :m_currentSpeciesId(species), m_name(name),m_outputEvents(silent)
        {
            LearnLevelUpMoves();
            CurrentStats.UpdateStats(Stats(GetMockmonSpeciesData().MockmonSpeciesStats,IVs,EVs,CurrentLevel));
        }
        unsigned int GetCurrentLevel() const;
        const MockmonSpecies & GetMockmonSpeciesData() const;
        int ModifyAttack(const moves::SimpleMove & AttackingMove,const Mockmon & target);
        void ChangeName(const std::string & newName); //needs to be somewhere else.
        void GrantExperiencePoints(long points);
        MockmonExp CheckExperiencePoints() const;
        long ExpFromDefeating()const;
        void GainExperienceFromVictory(const Mockmon & defeatedMon);
        void LoseSomehow();
        void FullRestore();
        bool IsAbleToBattle() const;
        bool IsWild() const {return false;}
        bool TeachMove(moves::MoveId);

        const std::vector<moves::EquipedMove> & GetMoveSet() const;
        std::string_view GetName() const;
        bool DisplayEvent() const {return  m_outputEvents;}

        //battle relatedStuff probably alot of methods should go somewhere else
        bool GetStabModifier(const moves::SimpleMove & AttackingMove);
        types::TypeEffectivenessModifier GetTypeEffectivenessModifer(const moves::SimpleMove & AttackingMove) ;

        private:
        
        double ModifyAttackForCrticalHit(const moves::SimpleMove & AttackingMove);
        double ModifyAttackForType(const moves::SimpleMove & AttackingMove,const Mockmon & target);

        void LearnLevelUpMoves();
        void LearnLevelUpMoves(int level);
        void LevelUp();
        void UpdateStats();


        public:
        Condition m_currentCondtion{};
        BattleStats CurrentStats; // this is calculated each level;

        protected:
        
        private:
        MockmonSpeciesId m_currentSpeciesId;
        std::string m_name;
        bool m_outputEvents;
        long CurrentLevel =1;
        long experience_points = 0;
        bool m_ableToBattle = true;
        std::vector<moves::EquipedMove> m_Moveset;
        const IndividualStats IVs; //this is calculated once when the pokemon is born;
        Stats EVs; // this is what we gain after each battle;




    };
}
