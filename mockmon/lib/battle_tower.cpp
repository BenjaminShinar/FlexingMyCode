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
            playerMonster.TeachMove(moves::MoveId::Guillotine);
            auto enemy = BattleTower::GenerateEnemy(9,"garry");
            Battle::DoBattle(playerMonster,enemy);
            
            // std::array<std::pair<std::string, types::Types>, 2> typesMap = {std::make_pair("iswater", types::Types::Water), std::make_pair("isnoram", types::Types::Normal)};
            // auto a =controller::GetAnyInput("test types",typesMap);
            // std::cout<< "testting any input: " << a <<'\n';
            // //generate oppnenets for the player to fight
        }

        Mockmon BattleTower::GenerateEnemy(int requestLevel,std::string enemyName)
        {
            Mockmon enemy(false);

            enemy.ChangeName(enemyName);
            for (auto z =1; z<=requestLevel;++z)
            {
                        enemy.GrantExperiencePoints(z* 100);
            }
            std::cout << "enemy mockmon " <<enemy.GetName() << " is " << enemy.CheckExperiencePoints() << '\n';
            enemy.TeachMove(moves::MoveId::Struggle);
            return enemy;
        }

}