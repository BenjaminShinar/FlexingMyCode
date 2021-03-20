#pragma once

#include "controller.h"
#include "mockmon_data.h"

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
        
        
        
        private:
        void DetermineBattle(controller::controllerEnum action);
        void PlayerTurn();
        void EnemyTurn();
        void LoopBattle();

        Mockmon & r_playerMockmon;
        Mockmon & r_enemyMockmon;
        
    };
}