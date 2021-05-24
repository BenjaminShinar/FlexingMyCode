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

    //do something else
    bool IsStabModifier(const Mockmon & m ,const moves::SimpleMove & AttackingMove) 
    {
        return m.GetMockmonSpeciesData().IsSpeciesOfType(AttackingMove.Type);
    }
    
    types::TypeEffectivenessModifier GetTypeEffectivenessModifer(const Mockmon & m,const moves::SimpleMove & AttackingMove) 
    {
        return m.GetMockmonSpeciesData().GetTypeEffetivenessModifier(AttackingMove.Type);
    }


    Battle::Battle(Mockmon &playerMockmon, Mockmon &enemyMockmon) : r_playerMockmon(playerMockmon), r_enemyMockmon(enemyMockmon)
    {
    }
    void Battle::DoBattle(Mockmon &playerMockmon, Mockmon &enemyMockmon)
    {
        std::cout << playerMockmon.GetName() << " starts the battle with " << playerMockmon.CurrentBattleStats.Health.GetStat() << " HP"<<'\n';
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
   
            const auto playerMV = GetAI(r_playerMockmon.GetTrainerAIID())(r_playerMockmon,r_enemyMockmon);
            const auto enemyMV = GetAI(r_enemyMockmon.GetTrainerAIID())(r_enemyMockmon,r_playerMockmon);
    
            if (DetermineOrder(playerMV,enemyMV))
            {

                AttackWith(playerMV,r_playerMockmon,r_enemyMockmon);
                AttackWith(enemyMV,r_enemyMockmon,r_playerMockmon);
            }
            else
            {
                AttackWith(enemyMV,r_enemyMockmon,r_playerMockmon);
                AttackWith(playerMV,r_playerMockmon,r_enemyMockmon);
            }
        }
        DetermineBattle(r_playerMockmon.IsAbleToBattle());
        const auto winner = r_playerMockmon.IsAbleToBattle() ? r_playerMockmon.GetName() : r_enemyMockmon.GetName();
        std::cout << "Battle ended at round " <<  round << " winner: "<< winner<<'\n';
    }

    bool Battle::DetermineOrder(const moves::MoveId playerMv,const moves::MoveId enemyMv)
    {
        {
        //priority moves.

            const auto playerPriority {GetMovePriority(playerMv)};
            const auto enemyPriority {GetMovePriority(enemyMv)};
            if (playerPriority != enemyPriority)
            {
                return playerPriority >enemyPriority;
            }
        }
        // same priority
        const auto [playerSpeed,enemySpeed] = GetStatsModifier(r_playerMockmon,StatsTypes::Speed,r_enemyMockmon,StatsTypes::Speed);
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
            r_playerMockmon.GainExperienceFromVictory(r_enemyMockmon);
            r_enemyMockmon.LoseSomehow();
        }
        else
        {
            r_enemyMockmon.GainExperienceFromVictory(r_playerMockmon);
            r_playerMockmon.LoseSomehow();
        }
    }


    std::tuple<double,double> Battle::GetStatsModifier(const Mockmon & attacker,const StatsTypes attackingStat,const Mockmon & defender,const StatsTypes defendingStat)  
    {
        const auto attackerStat = attacker.CurrentBattleStats.m_battleStats.at(attackingStat).GetStat()* attacker.m_currentCondtion.GetConditionalBoost(attackingStat,true);
        const auto defenderStat = defender.CurrentBattleStats.m_battleStats.at(defendingStat).GetStat()* defender.m_currentCondtion.GetConditionalBoost(defendingStat,false);
        return std::make_tuple(attackerStat, defenderStat); //attack / defence
    }


    bool Battle::IsCriticalHit(Mockmon & attackingMockmon, const moves::MoveId mv)
    {
        auto baseChance =100* attackingMockmon.GetMockmonSpeciesData().MockmonSpeciesStats.Stats.Speed * moves::CriticalChanceBoost(mv) / 512.0;
        return random::Randomer::CheckPercentage(baseChance);
    }

    //this is normal attack
    double Battle::ModifyAttack(const moves::MoveId attackingMoveId,Mockmon & attacker,const StatsTypes attackingStat, Mockmon & defender,const StatsTypes defendingStat)
    {
        const auto & simpleAttack = moves::SimpleMove::AllMoves.at(attackingMoveId);
        auto levelModifier = GetLevelDamageModifier(attacker);
        const auto [attackstat,defencestat] = Battle::GetStatsModifier(attacker,attackingStat,defender,defendingStat);
        const auto statsModifier = attackstat/defencestat;
        
        auto criticalHitModifier = [](Mockmon & attacker,const moves::MoveId mv){
            if (IsCriticalHit(attacker,mv))
            return (GetLevelCriticalDamageModifier(attacker));
            else
            return 1.0;
        }(attacker,simpleAttack.Identifier()); 
        
        auto stabModifer {IsStabModifier(attacker,simpleAttack)}; //stab
        auto typeMofider {GetTypeEffectivenessModifer(defender,simpleAttack)};  //typeResistancs and weakness
        auto typeEffectivenessAndStab {GetStabDamageModifier(stabModifer) *  GetTypeEffetivenessModifier(typeMofider)}; //typeResistancs and weakness
        auto  extraModifier = 1 * criticalHitModifier * typeEffectivenessAndStab ; // weahter, badge,status,
        return (extraModifier*(2+((levelModifier* simpleAttack.BasePower * statsModifier)/50)));
    }

    

    void Battle::AttackWith(moves::MoveId mvid,Mockmon & attacker,Mockmon & defender)
    {
        if (attacker.IsAbleToBattle() && defender.IsAbleToBattle())
        {
            auto & mvset = attacker.GetMoveSet();
            auto chosenMove = std::find_if(std::begin(mvset),std::end(mvset),
                [&](const moves::EquipedMove  & mv ){ return mv.IsSameAs(mvid);});
            auto usedMove{moves::MoveId::Struggle};

            attacker.m_currentCondtion.PulseBeforeTurn(); //assuming pulse before turn can't hurt the mockmon and cause it to faint or be unable to attack. maybe here we also switch moves to sleep/hurtself/        
            //if no charged/interupt move do the regular
            if (chosenMove != std::end(mvset) && chosenMove->RemainningPowerPoints()>0)
            {
                usedMove = chosenMove->UseMove().value_or(moves::MoveId::Struggle);
            }
            const auto & compositeMove = moves::CompositeMove::AllCompositeMoves.at(usedMove);

            //if there is a charged move,perform that instead
            //const auto & compositeMove = moves::CompositeMove::AllChargedCompositeMoves.at(usedMove);
            compositeMove.Perform(m_arena,attacker,defender);

        }
        if (attacker.IsAbleToBattle() && defender.IsAbleToBattle())
        {
            //if one of use was knocked out... don't pulse
            // this is a gen 1 thing!
            attacker.m_currentCondtion.PulseAfterTurn();
        }
    }
}