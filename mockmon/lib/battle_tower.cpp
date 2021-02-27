#include "battle_tower.h"

namespace mockmon
{
        void BattleTower::StartTower (Mockmon & playerMonster)
        {
            auto enemy = BattleTower::GenerateEnemy(9,"garry");
            playerMonster.GainExperienceFromVictory(enemy);
        //generate oppnenets for the player to fight
        }
        Mockmon BattleTower::GenerateEnemy(int requestLevel,std::string enemyName)
        {
            Mockmon enmey(false);

            enmey.ChangeName(enemyName);
            for (auto z =1; z<=requestLevel;++z)
            {
                        enmey.GrantExperiencePoints(z* 100);
            }
            std::cout << "enemy is " << enmey.CheckExperiencePoints() << '\n';

            return enmey;
        }

}