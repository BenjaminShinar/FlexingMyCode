#pragma once


#include "mockmon_data.h"
#include <string>
#include <iostream>

namespace mockmon
{

    
    //this class will be used to simulate battles without the overworld

    class BattleTower
    {
        public:
        static void StartTower (Mockmon & playerMonster);
        static Mockmon GenerateEnemy(int requestLevel,std::string enemyName);


    };
}