#include "battle.h"
#include "controller.h"
#include "random_gen.h"

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
            std::cout << r_playerMockmon.GetName() <<" is engaging in battle with " << r_enemyMockmon.GetName()<< " starting round " << ++round <<'\n';
            PlayerTurn();
            if (r_enemyMockmon.IsAbleToBattle())
            {
                EnemyTurn();
            }
        }
        auto endAction = r_playerMockmon.IsAbleToBattle()? controller::controllerEnum::ACTION_A : controller::controllerEnum::CANCEL_B;
        DetermineBattle(endAction);
        const auto winner = r_playerMockmon.IsAbleToBattle() ? r_playerMockmon.GetName() : r_enemyMockmon.GetName();
        std::cout << "Battle ended at round " <<  round << " winner: "<< winner<<'\n';
    }

    void Battle::PlayerTurn()
    {
        auto attack = controller::GetAnyInput("which move to use?",r_playerMockmon.GetMoveSet());
        r_playerMockmon.AttackWith(r_enemyMockmon,attack);
    }

    void Battle::EnemyTurn()
    {
        
        auto options = r_enemyMockmon.GetMoveSet().size();
        auto attack = moves::MoveId::Struggle;
        if (options>0)
        {
            auto randomAttack = random::Randomer::GetRandom(options);
            attack= r_enemyMockmon.GetMoveSet().at(randomAttack).Identifier();
        }
        
        r_enemyMockmon.AttackWith(r_playerMockmon,attack);
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
            r_enemyMockmon.GainExperienceFromVictory(r_playerMockmon);
            r_playerMockmon.LoseSomehow();
            break;
        }
        default:
            break;
        }
    }

}