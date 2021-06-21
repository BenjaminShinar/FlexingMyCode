#include "battle.h"
#include "random_gen.h"
#include "specialized_moves.h"
#include "moves_stats_targeting.h"
#include "trainer_ai.h"
#include "damage_calculations.h"
#include <algorithm>
#include <numeric>

namespace mockmon::battle
{
    Battle::Battle(Trainer &playerTrainer, Trainer &enemyTrainer, Mockmon &playerMockmon, Mockmon &enemyMockmon, bool silent) : player_pair(playerTrainer, playerMockmon), enemy_pair(enemyTrainer, enemyMockmon), m_arena(silent)
    {
    }

    void Battle::DoBattle(TrainerAI ai_1, Mockmon &playerMockmon, TrainerAI ai_2, Mockmon &enemyMockmon)
    {
        std::cout << playerMockmon.GetName() << " starts the battle with " << playerMockmon.CurrentBattleStats.Health.GetStat() << " HP" << '\n';
        Trainer player{"player", ai_1};
        Trainer enemy{"enemy", ai_2};
        Battle battle(player, enemy, playerMockmon, enemyMockmon);
        battle.LoopBattle();
    }

    void Battle::LoopBattle()
    {
        // std::array<std::pair<std::string, controller::controllerEnum>, 2> actions = {std::make_pair("Win", controller::controllerEnum::ACTION_A), std::make_pair("Lose", controller::controllerEnum::CANCEL_B)};
        // auto cmd = controller::GetAnyInput("what will you do in battle?", actions);

        int round = 0;
        while (player_pair.second.IsAbleToBattle() && enemy_pair.second.IsAbleToBattle())
        {
            std::cout << player_pair.second.GetName() << " is engaging in battle with " << enemy_pair.second.GetName() << " starting round " << ++round << '\n';

            const auto playerMV = GetAI(player_pair.first.TrainerAIType)(player_pair.second, enemy_pair.second);
            const auto enemyMV = GetAI(enemy_pair.first.TrainerAIType)(enemy_pair.second, player_pair.second);

            if (DetermineOrder(playerMV, enemyMV))
            {

                AttackWith(m_arena, playerMV, player_pair.second, enemy_pair.second);
                AttackWith(m_arena, enemyMV, enemy_pair.second, player_pair.second);
            }
            else
            {
                AttackWith(m_arena, enemyMV, enemy_pair.second, player_pair.second);
                AttackWith(m_arena, playerMV, player_pair.second, enemy_pair.second);
            }
        }
        DetermineBattle(player_pair.second.IsAbleToBattle());
        const auto winner = player_pair.second.IsAbleToBattle() ? player_pair.second.GetName() : enemy_pair.second.GetName();
        std::cout << "Battle ended at round " << round << " winner: " << winner << '\n';
    }

    bool Battle::DetermineOrder(const moves::MoveId playerMv, const moves::MoveId enemyMv)
    {
        {
            //priority moves.

            const auto playerPriority{GetMovePriority(playerMv)};
            const auto enemyPriority{GetMovePriority(enemyMv)};
            if (playerPriority != enemyPriority)
            {
                return playerPriority > enemyPriority;
            }
        }
        // same priority
        const auto [playerSpeed, enemySpeed] = m_arena.GetStatsModifier(player_pair.second, StatsTypes::Speed, enemy_pair.second, StatsTypes::Speed);
        if (playerSpeed > enemySpeed)
        {
            return true;
        }
        if (playerSpeed < enemySpeed)
        {
            return false;
        }
        //speed tie
        return (random::Randomer::CheckPercentage(50));
    }

    void Battle::DetermineBattle(bool b)
    {

        if (b)
        {
            player_pair.second.GainExperienceFromVictory(enemy_pair.second);
            enemy_pair.second.LoseSomehow();
        }
        else
        {
            enemy_pair.second.GainExperienceFromVictory(player_pair.second);
            player_pair.second.LoseSomehow();
        }
    }

    //do something else
    bool IsStabModifier(const Mockmon &m, const moves::SimpleMove &AttackingMove)
    {
        return m.GetMockmonSpeciesData().IsSpeciesOfType(AttackingMove.Type);
    }

    types::TypeEffectivenessModifier GetTypeEffectivenessModifer(const Mockmon &m, const moves::SimpleMove &AttackingMove)
    {
        return m.GetMockmonSpeciesData().GetTypeEffetivenessModifier(AttackingMove.Type);
    }

    /**
     * @brief 
     * determine if an attack scored a critical hit
     * effected by: base speed,moves with high critical chance, focus energy
     * @param attackingMockmon 
     * @param mv 
     * @return true 
     * @return false 
     */
    bool IsCriticalHit(Mockmon &attackingMockmon, const moves::MoveId mv)
    {
        const auto movesCriticalChanceFactor = moves::CriticalChanceBoost(mv);
        const auto criticalHitChance = GetSingleStatsModifier(attackingMockmon, StatsTypes::CriticalHitChance, true);
        auto baseChance = (100 * criticalHitChance * movesCriticalChanceFactor) / 512.0;
        return random::Randomer::CheckPercentage(baseChance);
    }

    double GetCriticalHitModifier(Mockmon &attackingMockmon, const moves::MoveId mv)
    {
        if (IsCriticalHit(attackingMockmon, mv))
            return (GetLevelCriticalDamageModifier(attackingMockmon));
        else
            return 1.0;
    }

    /**
     * @brief 
     * normal attacking move
     * @param attackingMoveId 
     * @param attacker 
     * @param attackingStat 
     * @param defender 
     * @param defendingStat 
     * @return double damage dealt
     */
    double ModifyAttack(const moves::MoveId attackingMoveId, Mockmon &attacker, const StatsTypes attackingStat, Mockmon &defender, const StatsTypes defendingStat)
    {
        const auto &simpleAttack = moves::SimpleMove::AllMoves.at(attackingMoveId);
        auto levelModifier = GetLevelDamageModifier(attacker);
        const Arena a{true};
        const auto [attackstat, defencestat] = a.GetStatsModifier(attacker, attackingStat, defender, defendingStat);
        const auto statsModifier = attackstat / defencestat;

        auto criticalHitModifier = GetCriticalHitModifier(attacker, simpleAttack.Identifier());
        auto stabModifer{IsStabModifier(attacker, simpleAttack)};                                                     //stab
        auto typeMofider{GetTypeEffectivenessModifer(defender, simpleAttack)};                                        //typeResistancs and weakness
        auto typeEffectivenessAndStab{GetStabDamageModifier(stabModifer) * GetTypeEffetivenessModifier(typeMofider)}; //typeResistancs and weakness
        auto extraModifier = 1 * criticalHitModifier * typeEffectivenessAndStab;                                      // weahter, badge,status,
        auto randomModifer = GetDamageRanges();
        return (randomModifer * (extraModifier * (2 + ((levelModifier * simpleAttack.BasePower * statsModifier) / 50))));
    }

    /**
     * @brief 
     * perform a single attack, used in testing
     * @param arena 
     * @param mvid 
     * @param attacker 
     * @param defender 
     */
    void AttackWith(Arena &arena, moves::MoveId mvid, Mockmon &attacker, Mockmon &defender)
    {
        if (attacker.IsAbleToBattle() && defender.IsAbleToBattle())
        {

            attacker.m_currentCondtion.PulseBeforeTurn(); //assuming pulse before turn can't hurt the mockmon and cause it to faint or be unable to attack. maybe here we also switch moves to sleep/hurtself/

            if (auto cv = attacker.m_currentCondtion.GetChargedMove())
            {
                auto chargedMV = cv.value();
                const auto &compositeChargedMove = moves::CompositeMove::AllChargedCompositeMoves.at(chargedMV);
                compositeChargedMove.Perform(arena, attacker, defender);
            }
            else
            {

                //move this elsewhere, this means that if we choose quick attack and it has zero pp, we still get priority
                // also, we want no Trainer PP for Gen 1 glitch
                auto &mvset = attacker.GetMoveSet();
                auto chosenMove = std::find_if(std::begin(mvset), std::end(mvset),
                                               [&](const moves::EquipedMove &mv)
                                               { return mv.IsSameAs(mvid); });
                auto usedMove{moves::MoveId::Struggle};

                //if no charged/interupt move do the regular
                if (chosenMove != std::end(mvset) && chosenMove->RemainningPowerPoints() > 0)
                {
                    //maybe not?
                    // maybe pp should be something that is changed by the move itself?
                    usedMove = chosenMove->UseMove().value_or(moves::MoveId::Struggle);
                }
                const auto &compositeMove = moves::CompositeMove::AllCompositeMoves.at(usedMove);

                //if there is a charged move,perform that instead
                //const auto & compositeMove = moves::CompositeMove::AllChargedCompositeMoves.at(usedMove);
                compositeMove.Perform(arena, attacker, defender);
            }
        }
        if (attacker.IsAbleToBattle() && defender.IsAbleToBattle())
        {
            //if one of use was knocked out... don't pulse
            // this is a gen 1 thing!
            attacker.m_currentCondtion.PulseAfterTurn();
        }
    }
}