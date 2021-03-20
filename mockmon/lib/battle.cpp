#include "battle.h"
#include "controller.h"

namespace mockmon
{
    Battle::Battle(Mockmon &playerMockmon, Mockmon &enemyMockmon) : r_playerMockmon(playerMockmon), r_enemyMockmon(enemyMockmon)
    {
    }
    void Battle::DoBattle(Mockmon &playerMockmon, Mockmon &enemyMockmon)
    {
        
        Battle battle(playerMockmon, enemyMockmon);
        battle.LoopBattle();
        
        
    }

    void Battle::LoopBattle()
    {
        // std::array<std::pair<std::string, controller::controllerEnum>, 2> actions = {std::make_pair("Win", controller::controllerEnum::ACTION_A), std::make_pair("Lose", controller::controllerEnum::CANCEL_B)};
        // auto cmd = controller::GetAnyInput("what will you do in battle?", actions);
        int round =0;
        while (r_playerMockmon.IsAbleToBattle() && r_enemyMockmon.IsAbleToBattle())
        {
            std::cout << "" <<" is engaging in battle with " << ""<< " starting round " << ++round <<'\n';
            PlayerTurn();
        }
        auto endAction = r_enemyMockmon.IsAbleToBattle()? controller::controllerEnum::ACTION_A : controller::controllerEnum::CANCEL_B;
        DetermineBattle(endAction);
        std::cout << "" <<" battke ended at round " <<  round <<'\n';

    }

    void Battle::PlayerTurn()
    {
        auto attck = controller::GetAnyInput("which move to use?",r_playerMockmon.GetMoveSet());
        r_playerMockmon.AttackWith(r_enemyMockmon,attck);

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