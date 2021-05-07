#include "trainer_ai.h"
#include "random_gen.h"
#include "controller.h"

namespace mockmon
{

 moves::MoveId PlayerInputChoice(Mockmon & attacker,Mockmon & defender)
 {
    return controller::GetAnyInput("which move to use?",attacker.GetMoveSet());    
 }

moves::MoveId RandomChoice(Mockmon & attacker,Mockmon & defender)
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