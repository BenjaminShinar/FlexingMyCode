#include "battle.h"
#include "game_driver/controller.h"
#include "random_gen.h"
#include "specialized_moves.h"
#include "moves_stats_targeting.h"
#include "trainer_ai.h"

#include <algorithm>
#include <numeric>

namespace mockmon
{
    Battle::Battle(Mockmon &playerMockmon, Mockmon &enemyMockmon) : r_playerMockmon(playerMockmon), r_enemyMockmon(enemyMockmon)
    {
    }
    void Battle::DoBattle(Mockmon &playerMockmon, Mockmon &enemyMockmon)
    {
        std::cout << playerMockmon.GetName() << " starts the battle with " << playerMockmon.CurrentBattleStats.Health.GetStat() << " HP"<<'\n';
        Battle battle(playerMockmon, enemyMockmon);
        battle.LoopBattle();
        
        
    }


    double Battle::GetTypeEffetiveness(types::TypeEffectivenessModifier modifier)
    {
        using types::TypeEffectivenessModifier;        
        switch (modifier)
        {
            case TypeEffectivenessModifier::NotEffective: return 0.0; break;
            case TypeEffectivenessModifier::VeryNotEffective: return 0.25; break;
            case TypeEffectivenessModifier::NotVeryEffective: return 0.5; break;
            case TypeEffectivenessModifier::NormalEffective: return 1.0; break;
            case TypeEffectivenessModifier::VeryEffective: return 2.0; break;
            case TypeEffectivenessModifier::SuperEffective: return 4.0; break;
            default: break;
        }

        return 1.0;
    } //how an attack effects this pokemon

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
        auto endAction = r_playerMockmon.IsAbleToBattle()? controller::controllerEnum::ACTION_A : controller::controllerEnum::CANCEL_B;
        DetermineBattle(endAction);
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
        const auto playerSpeed {r_playerMockmon.CurrentBattleStats.m_battleStats.at(StatsTypes::Speed).GetStat()};
        const auto enemySpeed {r_enemyMockmon.CurrentBattleStats.m_battleStats.at(StatsTypes::Speed).GetStat()};
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

    void Battle::DetermineBattle(controller::controllerEnum action)
    {

        switch (action)
        {
        case (controller::controllerEnum::ACTION_A):
        {
            r_playerMockmon.GainExperienceFromVictory(r_enemyMockmon);
            r_enemyMockmon.LoseSomehow();
            break;
        }
        case (controller::controllerEnum::CANCEL_B):
        {
            r_enemyMockmon.GainExperienceFromVictory(r_playerMockmon);
            r_playerMockmon.LoseSomehow();
            break;
        }
        default:
            break;
        }
    }

    double GetStatsModifier(const Mockmon & attacker,const StatsTypes attackingStat,const Mockmon & defender,const StatsTypes defendingStat)  
    {
        const auto attackerStat = attacker.CurrentBattleStats.m_battleStats.at(attackingStat).GetStat()* attacker.m_currentCondtion.GetConditionalBoost(attackingStat,true);
        const auto defenderStat = defender.CurrentBattleStats.m_battleStats.at(defendingStat).GetStat()* defender.m_currentCondtion.GetConditionalBoost(defendingStat,false);
        return (attackerStat / defenderStat); //attack / defence
    }

    bool Battle::IsCriticalHit(Mockmon & attackingMockmon, const moves::MoveId mv)
    {
        auto baseChance =100* attackingMockmon.GetMockmonSpeciesData().MockmonSpeciesStats.Stats.Speed * moves::CriticalChanceBoost(mv) / 512.0;
        return random::Randomer::CheckPercentage(baseChance);
    }

    //this is normal attack
    double Battle::ModifyAttack(const moves::SimpleMove & AttackingMove,Mockmon & attacker,const StatsTypes attackingStat, Mockmon & defender,const StatsTypes defendingStat)
    {
            auto levelModifier = 2+((2*attacker.GetCurrentLevel())/5);
        auto statsModifier = GetStatsModifier(attacker,attackingStat,defender,defendingStat);
        
        auto criticalHitModifier = [](Mockmon & attacker,const moves::MoveId mv){
            if (IsCriticalHit(attacker,mv))
            return (attacker.ModifyAttackForCrticalHit());
            else
            return 1.0;
        }(attacker,AttackingMove.Identifier()); 
        
        auto stabModifer {attacker.GetStabModifier(AttackingMove) ? 1.5 : 1.0}; //stab
        auto typeMofider {defender.GetTypeEffectivenessModifer(AttackingMove)};  //typeResistancs and weakness
        auto typeEffectivenessAndStab {stabModifer *  GetTypeEffetiveness(typeMofider)}; //typeResistancs and weakness
        auto  extraModifier = 1 * criticalHitModifier * typeEffectivenessAndStab ; // weahter, badge,status,
        return (extraModifier*(2+((levelModifier* AttackingMove.BasePower * statsModifier)/50)));
    }

    

    void Battle::AttackWith(moves::MoveId mvid,Mockmon & attacker,Mockmon & defender)
    {
        if (attacker.IsAbleToBattle() && defender.IsAbleToBattle())
        {
            auto chosenMove = std::find_if(attacker.m_Moveset.begin(),attacker.m_Moveset.end(),
                [&](const moves::EquipedMove  & mv ){ return mv.Identifier() == mvid;});
            auto usedMove{moves::MoveId::Struggle};

            attacker.m_currentCondtion.PulseBeforeTurn(); //assuming pulse before turn can't hurt the mockmon and cause it to faint or be unable to attack. maybe here we also switch moves to sleep/hurtself/        

            if (chosenMove != attacker.m_Moveset.end() && chosenMove->RemainningPowerPoints()>0)
            {
                usedMove = chosenMove->UseMove().value_or(moves::MoveId::Struggle);
            }
            const auto & compositeMove = moves::CompositeMove::AllCompositeMoves.at(usedMove);
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