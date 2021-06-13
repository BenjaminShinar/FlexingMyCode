#include "game_driver/battle_tower.h"
#include "game_driver/controller.h"
#include "battle.h"
#include "types.h"
#include "types.h"
#include "random_gen.h"
#include <array>
#include <utility>

namespace mockmon
{

        /**
         * @brief 
         * teach whatever moves i want to verify that work, this is a 'debug' function, not to be used in 'real game' situations...
         * @param playerMonster 
         */
        void teachStartingMovesMoves(Mockmon & m)
        {
            using moves::MoveId;
            m.TeachMove(MoveId::ThunderWave);
            m.TeachMove(MoveId::BodySlam);
            m.TeachMove(MoveId::HyperBeam);

        }


        void BattleTower::StartTower (Mockmon & playerMonster,unsigned int maxFloor)
        {
            teachStartingMovesMoves(playerMonster);

            playerMonster.FullRestore();
            auto currentFloor{0u};
            while(currentFloor < maxFloor && playerMonster.IsAbleToBattle())
            {
                
                if (!TowerFloor(playerMonster,++currentFloor))
                    std::cout << "player mockmon " << playerMonster.GetName() << " has fallen in floor "  << currentFloor <<'\n';
                
                playerMonster.m_currentCondtion.RemoveAllConditions();

            }

            if (playerMonster.IsAbleToBattle())
            {
                std::cout << "player mockmon " << playerMonster.GetName() << " has conquered all "  << maxFloor << " of the tower!" <<'\n';
            }


        }
        bool BattleTower::TowerFloor (Mockmon & playerMonster,unsigned int floorLevel)
        {
            const auto RandomizeEnemyType = random::Randomer::GetOneOption({MockmonSpeciesId::Mew,MockmonSpeciesId::Weedle,MockmonSpeciesId::Rattata});
            
            auto enemy = BattleTower::GenerateEnemy(floorLevel,RandomizeEnemyType,"garry");
            std::cout<< "player mockmon " << playerMonster.GetName() << " will face " << enemy.GetName() << " the level " << enemy.GetCurrentLevel() << " " << enemy.GetMockmonSpeciesData().Identifier() << " with " << enemy.CurrentBattleStats.Health.GetStat() << " HP!"  <<'\n';
            battle::Battle::DoBattle(playerMonster,enemy);
            return(playerMonster.IsAbleToBattle());
            
        }

        Mockmon BattleTower::GenerateEnemy(int requestLevel,MockmonSpeciesId enemySpecies, std::string enemyName)
        {
            Mockmon enemy(enemySpecies,enemyName,TrainerAI::RandomChoice,true);
            auto needexp = MockmonExp::TotalExperinceForLevel(requestLevel,enemy.GetMockmonSpeciesData().SpeciesLevelUpGroup);
            enemy.GrantExperiencePoints(needexp);
            enemy.FullRestore();
            std::cout << "enemy mockmon " <<enemy.GetName() << " is " << enemy.CheckExperiencePoints() << " and has "<< enemy.CurrentBattleStats.Health.GetStat() <<" hit points!"<< '\n';
            return enemy;
        }
  
}