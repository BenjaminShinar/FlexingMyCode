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

int main(int argc, char *argv[],char ** env)
{
    Mockmon m(true);
    
    if (argc <2)
    {
        std::string mockmonName;
        std::cout<< "how will you call your mockmon?" << '\n';
        std::cin >> mockmonName;
        m.ChangeName(mockmonName);
    }
    else
    {
        m.ChangeName(argv[1]);
    }

    BattleTower::StartTower(m);
}