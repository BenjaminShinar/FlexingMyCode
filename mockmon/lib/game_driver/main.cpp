
//#include <format>
#include "game_driver/main.h"
#include "game_driver/controller.h"
#include "mockmon_data.h"
#include "game_driver/battle_tower.h"



using namespace mockmon;

void StartGame(const std::string & mockmonName, int maxFloor)
{
  
    Mockmon m(MockmonSpeciesId::Mew,mockmonName,TrainerAI::PlayerChoice,true);

    BattleTower::StartTower(m,maxFloor);
}