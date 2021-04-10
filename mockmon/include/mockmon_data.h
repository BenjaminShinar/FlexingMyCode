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
        public:
        explicit Mockmon(MockmonSpeciesId species,const std::string & name,bool silent = false)
        :m_currentSpeciesId(species), m_name(name),m_outputEvents(silent),m_currentCondtion()
        {
            LearnLevelUpMoves();
        }
        
        const MockmonSpecies & GetMockmonSpeciesData() const;
        int ModifyAttack(const moves::EquipedMove & AttackingMove,const Mockmon & target) const;
        int ModifyAttack(const moves::BaseMove & AttackingMove,const Mockmon & target) const; //struggle

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
        void AttackWith(Mockmon & enemy, moves::MoveId);
        const std::vector<moves::EquipedMove> & GetMoveSet() const;
        Condition m_currentCondtion;
        std::string_view GetName() const;
        protected:
        
        private:
        MockmonSpeciesId m_currentSpeciesId;
        std::string m_name;
        long CurrentLevel =1;
        long experience_points = 0;
        void LearnLevelUpMoves();
        void LearnLevelUpMoves(int level);
        void LevelUp();
        void UpdateStats();
        bool m_outputEvents;
        bool m_ableToBattle = true;
        std::vector<moves::EquipedMove> m_Moveset;
        const Stats IVs; //this is calculated once when the pokemon is born;
        Stats CurrentStats; // this is calculated each level;
        Stats EVs; // this is what we gain after each battle;
    };
}
