
//#include <format>
#include "main.h"
#include "controller.h"
#include "mockmon_data.h"
#include "battle_tower.h"



using namespace mockmon;

void StartGame(const std::string & mockmonName, int maxFloor)
{
  
    Mockmon m(MockmonSpeciesId::Mew,mockmonName,true);

    BattleTower::StartTower(m,maxFloor);
}