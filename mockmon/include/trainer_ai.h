#pragma once


#include "moves.h"
#include "mockmon_data.h"
#include "identifiers/trainer_ai_id.h"


#include <functional>

//this should control how moves are chosen, 
namespace mockmon
{

    //this is a return function typedef
    //takes battle, arena, attacker, defender
    //does some magic and returns an attac
    using ChosenMove = std::function<moves::MoveId(Mockmon & attacker,Mockmon & defender)>;

    ChosenMove GetAI(const TrainerAI trainerAI);
}