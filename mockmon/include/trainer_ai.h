#pragma once

#include <string>
#include <iostream>
#include <algorithm>
#include <map>

namespace mockmon
{
    enum class TrainerAIID
    {
        PlayerChoice,
        RandomChoice,
        PreferSuperEffective
    };

        std::ostream &operator<<(std::ostream &os, const TrainerAIID &trainer_ai_id);

}