#pragma once

#include "identifiers/moves_id.h"
#include "identifiers/type_effectiveness_id.h"
#include "trainer_ai.h"
#include "trainer.h"
#include "mockmon_data.h"
#include "arena.h"
#include <string>
#include <iostream>
#include <utility>
#include <tuple>

namespace mockmon::battle
{

    /**
     * @brief 
     * how we expose the outcome of a move
     * mostly text for now, but we should use the success flat more often
     */
    struct MoveOutcome
    {
        bool m_hit;
        std::string m_moveOutcomeDescrition;
    };

    [[nodiscard]] double ModifyAttack(const moves::MoveId attackingMoveId, Mockmon &attacker, const StatsTypes attackingStat, Mockmon &defender, const StatsTypes defendingStat);
    [[nodiscard]] bool IsCriticalHit(Mockmon &attackingMockmon, const moves::MoveId mv);
    [[nodiscard]] double GetCriticalHitModifier(Mockmon &attackingMockmon, const moves::MoveId mv);
    //    std::tuple<double, double> GetStatsModifier(const Mockmon &attacker, const StatsTypes attackingStat, const Mockmon &defender, const StatsTypes defendingStat);
    std::vector<MoveOutcome> AttackWith(Arena &arena, moves::MoveId mvid, Mockmon &attacker, Mockmon &defender);

    //this class will be used to simulate battles without the overworld
    class Battle
    {

    public:
        explicit Battle(Trainer &playerTrainer, Trainer &enemyTrainer, Mockmon &playerMockmon, Mockmon &enemyMockmon, bool silent = false);

        static void DoBattle(TrainerAI ai_1, Mockmon &playerMockmon, TrainerAI ai_2, Mockmon &enemyMockmon);

    private:
        void DetermineBattle(bool b);
        void LoopBattle();
        [[nodiscard]] bool DetermineOrder(const moves::MoveId playerMv, const moves::MoveId enemyMv);

        std::pair<Trainer &, Mockmon &> player_pair;
        std::pair<Trainer &, Mockmon &> enemy_pair;
        Arena m_arena;
    };
}