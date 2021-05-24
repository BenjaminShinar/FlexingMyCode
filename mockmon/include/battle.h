#pragma once


#include "identifiers/moves_id.h"
#include "identifiers/type_effectiveness_id.h"


#include "mockmon_data.h"
#include "arena.h"
#include <string>
#include <iostream>
#include <tuple>

namespace mockmon::battle
{

    
    //this class will be used to simulate battles without the overworld
    class Battle
    {
        
        public:
        explicit Battle (Mockmon & playerMockmon, Mockmon & enemyMockmon);
        static void DoBattle(Mockmon & playerMockmon, Mockmon & enemyMockmon);       
        static double ModifyAttack(const moves::MoveId attackingMoveId, Mockmon & attacker,const StatsTypes attackingStat, Mockmon & defender,const StatsTypes defendingStat);
        static bool IsCriticalHit(Mockmon & attackingMockmon, const moves::MoveId mv);

        static  std::tuple<double,double> GetStatsModifier(const Mockmon & attacker,const StatsTypes attackingStat,const Mockmon & defender,const StatsTypes defendingStat) ;

        private:
        void DetermineBattle(bool b);
        void LoopBattle();
        bool DetermineOrder(const moves::MoveId playerMv,const moves::MoveId enemyMv);
        void AttackWith(moves::MoveId mvid,Mockmon & attacker,Mockmon & defender);

        Arena m_arena;
        Mockmon & r_playerMockmon;
        Mockmon & r_enemyMockmon;

        
    };
}