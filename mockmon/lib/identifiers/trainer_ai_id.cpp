#include "identifiers/trainer_ai_id.h"

namespace mockmon
{

    std::string Stringify(const TrainerAI trainerAI)
    {
        switch (trainerAI)
        {
            case TrainerAI::PlayerChoice: return "Player Choice";break;
            case TrainerAI::RandomChoice: return "Random Choice";break;
            case TrainerAI::PreferSuperEffective: return "Good AI Pattern";break;

            default: return "Unknown AI Pattern!"; break;
        }
    }
    std::ostream &operator<<(std::ostream &os, const TrainerAI &e)
    {
        os << Stringify(e);
        return os;
    }
}