#pragma once


#include "identifiers/moves_id.h"
#include "identifiers/type_effectiveness_id.h"


#include "game_driver/controller.h"
#include "mockmon_data.h"
#include "arena.h"
#include <string>
#include <iostream>

namespace mockmon
{

    
    //this class will be used to simulate battles without the overworld
    class Battle
    {
        
        public:
        explicit Battle (Mockmon & playerMockmon, Mockmon & enemyMockmon);
        static void DoBattle(Mockmon & playerMockmon, Mockmon & enemyMockmon);
        
        static double GetTypeEffetiveness(types::TypeEffectivenessModifier modifier);
        
        void AttackWith(moves::MoveId mvid,Mockmon & attacker,Mockmon & defender);
        static double ModifyAttack(const moves::SimpleMove & AttackingMove, Mockmon & attacker,const StatsTypes attackingStat, Mockmon & defender,const StatsTypes defendingStat);

        
        private:
        void DetermineBattle(controller::controllerEnum action);
        void LoopBattle();
        bool DetermineOrder(const moves::MoveId playerMv,const moves::MoveId enemyMv);
        static bool IsCriticalHit(Mockmon & attackingMockmon, const moves::MoveId mv);
        Arena m_arena;
        Mockmon & r_playerMockmon;
        Mockmon & r_enemyMockmon;

        
    };
}