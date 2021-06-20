#pragma once

#include "moves.h"
#include "mockmon_data.h"
#include "identifiers/trainer_ai_id.h"
#include "identifiers/badges_id.h"
#include "bitset"

#include <functional>

//this should control how moves are chosen,
namespace mockmon
{

    //this is a return function typedef
    //takes battle, arena, attacker, defender
    //does some magic and returns an attac
    using ChosenMove = std::function<moves::MoveId(Mockmon &attacker, Mockmon &defender)>;

    ChosenMove GetAI(const TrainerAI trainerAI);

    class Trainer
    {
    private:
        static std::size_t LastTrainerId;

    public:
        explicit Trainer(const std::string &trainer_name, TrainerAI trainerAIType = TrainerAI::RandomChoice) : m_Trainer_Name(trainer_name), TrainerAIType(trainerAIType)
        {
        }
        std::string m_Trainer_Name;
        const std::size_t UniqueTrainerID{LastTrainerId++};
        const TrainerAI TrainerAIType{TrainerAI::RandomChoice};
        void GiveBadge(badges::IndigoBadge badge);
        bool CheckBadge(badges::IndigoBadge badge) const;

    private:
        std::bitset<badges::IndigoBadgesNumber> m_Indigo_Badges{0};
    };
}