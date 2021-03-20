#include "battle_tower.h"
#include "battle.h"
#include "types.h"
#include "controller.h"
#include "types.h"
#include <array>
#include <utility>

namespace mockmon
{
        void BattleTower::StartTower (Mockmon & playerMonster)
        {
            playerMonster.TeachMove(moves::MoveId::WaterGun);
            auto enemy = BattleTower::GenerateEnemy(9,"garry");
            Battle::DoBattle(playerMonster,enemy);
            
            // std::array<std::pair<std::string, types::Types>, 2> typesMap = {std::make_pair("iswater", types::Types::Water), std::make_pair("isnoram", types::Types::Normal)};
            // auto a =controller::GetAnyInput("test types",typesMap);
            // std::cout<< "testting any input: " << a <<'\n';
            // //generate oppnenets for the player to fight
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