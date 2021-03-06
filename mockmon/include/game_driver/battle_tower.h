#pragma once

#include "mockmon_data.h"
#include "identifiers/mockmon_species_id.h"
#include <string>
#include <iostream>

namespace mockmon
{

    //this class will be used to simulate battles without the overworld

    class BattleTower
    {
    public:
        static void StartTower(Mockmon &playerMonster, unsigned int maxTowerLevel);
        static bool TowerFloor(Mockmon &playerMonster, unsigned int floorLevel);
        [[nodiscard]] static Mockmon GenerateEnemy(int requestLevel, MockmonSpeciesId enemySpecies, std::string enemyName);
    };
}