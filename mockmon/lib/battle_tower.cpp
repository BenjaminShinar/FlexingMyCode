#include "battle_tower.h"
#include "battle.h"
#include "types.h"
#include "controller.h"
#include "types.h"
#include <array>
#include <utility>

namespace mockmon
{
        void BattleTower::StartTower (Mockmon & playerMonster,unsigned int maxFloor)
        {
            auto currentFloor{0u};
            while(currentFloor < maxFloor && playerMonster.IsAbleToBattle())
            {
                
                if (!TowerFloor(playerMonster,++currentFloor))
                    std::cout << "player mockmon " << playerMonster.GetName() << " has fallen in floor "  << currentFloor <<'\n';
            }

            if (playerMonster.IsAbleToBattle())
            {
                std::cout << "player mockmon " << playerMonster.GetName() << " has conquered all "  << maxFloor << " of the tower!" <<'\n';
            }

        }
        bool BattleTower::TowerFloor (Mockmon & playerMonster,unsigned int floorLevel)
        {
            //playerMonster.TeachMove(moves::MoveId::WaterGun);
            //playerMonster.TeachMove(moves::MoveId::Guillotine);
            auto enemy = BattleTower::GenerateEnemy(floorLevel,MockmonSpeciesId::Ratata,"garry");
            std::cout<< "player mockmon " << playerMonster.GetName() << " will face " << enemy.GetName() << " the level " << enemy.CheckExperiencePoints().CurrentLevel << " " << enemy.GetMockmonSpeciesData().Identifier() <<'\n';
            Battle::DoBattle(playerMonster,enemy);
            return(playerMonster.IsAbleToBattle());
            // std::array<std::pair<std::string, types::Types>, 2> typesMap = {std::make_pair("iswater", types::Types::Water), std::make_pair("isnoram", types::Types::Normal)};
            // auto a =controller::GetAnyInput("test types",typesMap);
            // std::cout<< "testting any input: " << a <<'\n';
            // //generate oppnenets for the player to fight
        }

        Mockmon BattleTower::GenerateEnemy(int requestLevel,MockmonSpeciesId enemySpecies, std::string enemyName)
        {
            Mockmon enemy(enemySpecies,enemyName,true);
            auto needexp = MockmonExp::TotalExperinceForLevel(requestLevel,enemy.GetMockmonSpeciesData().SpeciesLevelUpGroup);
            enemy.GrantExperiencePoints(needexp);
            
            std::cout << "enemy mockmon " <<enemy.GetName() << " is " << enemy.CheckExperiencePoints() << '\n';
            return enemy;
        }

}