#pragma once

#include "moves.h"
//#include <string_view>
#include <string>
#include <iostream>
#include <vector>

#include "condition.h"
#include "stats.h"
#include "mockmon_exp.h"

namespace mockmon
{
    class Mockmon
    {   
        public:
        explicit Mockmon(bool silent = false)
        : m_name("Nameless"),m_outputEvents(silent),m_currentCondtion(),m_Moveset()
        {

        }

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
        std::string m_name;
        long level =1;
        long experience_points = 0;
        void LevelUp();
        bool m_outputEvents;
        bool m_ableToBattle = true;
        const long m_speciesExp = 35;
        std::vector<moves::EquipedMove> m_Moveset;
    };

           /*
        name
        id
        original trainer id

        base type
        current type:
        level:
        exp:


        stats:
        ev
        iv

        moves:
        */

}
