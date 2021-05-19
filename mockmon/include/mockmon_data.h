#pragma once

#include "identifiers/trainer_ai_id.h"
#include "moves.h"
//#include <string_view>
#include <string>
#include <iostream>
#include <vector>

#include "condition.h"
#include "stats/stats.h"
#include "stats/battle_stats.h"
#include "mockmon_species.h"
#include "mockmon_exp.h"


namespace mockmon
{
    class Mockmon
    {   
        friend class Battle;
        friend class Arena;
        public:
        explicit Mockmon(MockmonSpeciesId species,const std::string & name,TrainerAI trainerAi = TrainerAI::RandomChoice,bool silent = false)
        :m_currentSpeciesId(species), m_name(name),m_trainer_ai_id(trainerAi),m_outputEvents(silent)
        {
            LearnLevelUpMoves();
            CurrentBattleStats.UpdateStats(stats::MockmonStats(GetMockmonSpeciesData().MockmonSpeciesStats,IVs,EVs,CurrentLevel));
        }

        unsigned int GetCurrentLevel() const;
        const MockmonSpecies & GetMockmonSpeciesData() const;
        int ModifyAttack(const moves::SimpleMove & AttackingMove,const Mockmon & target);
        void ChangeName(const std::string & newName); //needs to be somewhere else.
        void GrantExperiencePoints(long points);
        MockmonExp CheckExperiencePoints() const;
        long ExpFromDefeating()const;
        void GainEffortValueFromVictory(const Mockmon & defeatedMon);
        void GainExperienceFromVictory(const Mockmon & defeatedMon);
        void LoseSomehow();
        void FullRestore();
        bool IsAbleToBattle() const;
        bool IsWild() const {return false;}
        bool TeachMove(moves::MoveId);
        const std::vector<moves::EquipedMove> & GetMoveSet() const;
        std::string_view GetName() const;
        bool DisplayEvent() const {return  m_outputEvents;}
        TrainerAI GetTrainerAIID() const {return m_trainer_ai_id;}
        //battle relatedStuff probably alot of methods should go somewhere else
        bool GetStabModifier(const moves::SimpleMove & AttackingMove);
        types::TypeEffectivenessModifier GetTypeEffectivenessModifer(const moves::SimpleMove & AttackingMove) ;

        private:
        
        double ModifyAttackForCrticalHit();
        double ModifyAttackForType(const moves::SimpleMove & AttackingMove,const Mockmon & target);

        void LearnLevelUpMoves();
        void LearnLevelUpMoves(int level);
        void LevelUp();
        void UpdateStats();


        public:
        condition::Condition m_currentCondtion{};
        stats::BattleStats CurrentBattleStats; // this is calculated each level;

        protected:
        
        private:
        MockmonSpeciesId m_currentSpeciesId; //this can change when the mockmon evolves
        
        std::string m_name;
        TrainerAI m_trainer_ai_id;
        bool m_outputEvents;
        long CurrentLevel =1;
        long experience_points = 0;
        bool m_ableToBattle = true;
        std::vector<moves::EquipedMove> m_Moveset;
        const stats::IndividualStats IVs; //this is calculated once when the pokemon is born;
        stats::EffortValuesStats EVs; // this is what we gain after each battle;




    };
}
