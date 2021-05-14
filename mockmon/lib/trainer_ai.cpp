#include "interfaces.h"
#include "trainer_ai.h"
#include "random_gen.h"
#include "game_driver/controller.h"


namespace mockmon
{

 moves::MoveId PlayerInputChoice(Mockmon & attacker,Mockmon & defender)
 {
    const auto prompt = AppendAll({"which move should",attacker.GetName(), "attack",defender.GetName(), "with?"});
    return controller::GetAnyInput(prompt,attacker.GetMoveSet());    
 }

moves::MoveId RandomChoice(Mockmon & attacker,Mockmon &)
 {
    const auto possibleOptions = attacker.GetMoveSet().size();
    if (possibleOptions>0)
    {
        auto randomAttack = random::Randomer::GetRandom(possibleOptions);
        return (attacker.GetMoveSet().at(randomAttack).Identifier());
    }
     return moves::MoveId::Struggle;
 }

    ChosenMove GetAI(const TrainerAI trainerAI)
    {
        switch (trainerAI)
        {
        case TrainerAI::PlayerChoice:
            return PlayerInputChoice;
            break;
        
        default:
        return RandomChoice;
            break;
        }
    }

}