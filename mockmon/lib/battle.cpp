#include "battle.h"

#include "controller.h"

namespace mockmon
{
    Battle::Battle(Mockmon &playerMockmon, Mockmon &enemyMockmon) : r_playerMockmon(playerMockmon), r_enemyMockmon(enemyMockmon)
    {
    }
    void Battle::DoBattle(Mockmon &playerMockmon, Mockmon &enemyMockmon)
    {
        std::array<std::pair<std::string, controller::controllerEnum>, 2> actions = {std::make_pair("Win", controller::controllerEnum::ACTION_A), std::make_pair("Lose", controller::controllerEnum::CANCEL_B)};
        Battle battle(playerMockmon, enemyMockmon);
        auto cmd = controller::GetInput("what will you do in battle?", actions);
        battle.DetermineBattle(cmd);
    }

    void Battle::DetermineBattle(controller::controllerEnum action)
    {

        switch (action)
        {
        case (controller::controllerEnum::ACTION_A):
        {
            r_playerMockmon.GainExperienceFromVictory(r_enemyMockmon);
            r_enemyMockmon.LoseSomehow();
            break;
        }
        case (controller::controllerEnum::CANCEL_B):
        {
            r_playerMockmon.LoseSomehow();
            break;
        }
        default:
            break;
        }
    }

}