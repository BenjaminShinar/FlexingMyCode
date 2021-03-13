//#include <format>

#include "controller.h"
#include "mockmon_data.h"
#include "battle_tower.h"


#include <iostream>
#include <sstream> 

#include <string>
#include <array>
#include <utility>




using namespace mockmon;

int main()
{
    Mockmon m(true);
    m.ChangeName("levelupper");
    BattleTower::StartTower(m);
}