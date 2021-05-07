#pragma once

#include <string>
#include <iostream>

namespace mockmon
{
    enum class TrainerAI
    {
        PlayerChoice,
        RandomChoice,
        PreferSuperEffective
    };

    std::string Stringify(const TrainerAI trainer_ai_id);
        std::ostream &operator<<(std::ostream &os, const TrainerAI &e);


}