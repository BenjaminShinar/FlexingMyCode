#include "battle.h"
#include "controller.h"
#include "random_gen.h"
#include "specialized_moves.h"

#include <algorithm>
#include <numeric>

namespace mockmon
{
    Battle::Battle(Mockmon &playerMockmon, Mockmon &enemyMockmon) : r_playerMockmon(playerMockmon), r_enemyMockmon(enemyMockmon)
    {
    }
    void Battle::DoBattle(Mockmon &playerMockmon, Mockmon &enemyMockmon)
    {
        std::cout << playerMockmon.GetName() << " starts the battle with " << playerMockmon.CurrentStats.Health.GetStat() << " HP"<<'\n';
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
        Arena arena;//spikes, screens, weather, etc;

        int round =0;
        while (r_playerMockmon.IsAbleToBattle() && r_enemyMockmon.IsAbleToBattle())
        {
            std::cout << r_playerMockmon.GetName() <<" is engaging in battle with " << r_enemyMockmon.GetName()<< " starting round " << ++round <<'\n';
            const auto playerMV =r_playerMockmon.DecideMove(r_enemyMockmon);
            const auto enemyMV =r_enemyMockmon.DecideMove(r_playerMockmon);
    
            if (DetermineOrder())
            {

                AttackWith(playerMV,r_playerMockmon,r_enemyMockmon);
                if (r_enemyMockmon.IsAbleToBattle())
                {
                    AttackWith(enemyMV,r_enemyMockmon,r_playerMockmon);
                }
            }
            else
            {
                AttackWith(enemyMV,r_enemyMockmon,r_playerMockmon);
                if (r_playerMockmon.IsAbleToBattle())
                {
                    AttackWith(playerMV,r_playerMockmon,r_enemyMockmon);
                }
            }
        }
        auto endAction = r_playerMockmon.IsAbleToBattle()? controller::controllerEnum::ACTION_A : controller::controllerEnum::CANCEL_B;
        DetermineBattle(endAction);
        const auto winner = r_playerMockmon.IsAbleToBattle() ? r_playerMockmon.GetName() : r_enemyMockmon.GetName();
        std::cout << "Battle ended at round " <<  round << " winner: "<< winner<<'\n';
    }

    bool Battle::DetermineOrder()
    {
        //ignoring priority moves for now.
        const auto playerSpeed {r_playerMockmon.CurrentStats.m_battleStats.at(StatsTypes::Speed).GetStat()};
        const auto enemySpeed {r_enemyMockmon.CurrentStats.m_battleStats.at(StatsTypes::Speed).GetStat()};
        if (playerSpeed > enemySpeed)
        {
            return true;
        }
        if (playerSpeed < enemySpeed)
        {
            return false;
        }
        //speed tie
        return (random::Randomer::GetRandom(2) ==0);
    }

    void Battle::PlayerTurn(moves::MoveId mv)
    {
        auto attack = controller::GetAnyInput("which move to use?",r_playerMockmon.GetMoveSet());
        AttackWith(attack,r_playerMockmon,r_enemyMockmon);
    }

    void Battle::EnemyTurn(moves::MoveId mv)
    {
        
        auto options = r_enemyMockmon.GetMoveSet().size();
        auto attack = moves::MoveId::Struggle;
        if (options>0)
        {
            
            auto randomAttack = random::Randomer::GetRandom(options);
            attack= r_enemyMockmon.GetMoveSet().at(randomAttack).Identifier();
        }
        
        AttackWith(attack,r_enemyMockmon,r_playerMockmon);    
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

    double GetStatsModifier(const moves::SimpleMove & AttackingMove,const Mockmon & attacker,const Mockmon & defender)  
    {
        //this should be extracted from the move
        const auto attackingStat = StatsTypes::Attack;
        const auto defendingStat = StatsTypes::Defence;
        return (attacker.CurrentStats.m_battleStats.at(attackingStat).GetStat() / defender.CurrentStats.m_battleStats.at(defendingStat).GetStat()); //attack / defence
    }
    //this is normal attack
    double Battle::ModifyAttack(const moves::SimpleMove & AttackingMove,Mockmon & attacker,Mockmon & defender)
    {
        auto baseDamage = AttackingMove.BasePower;
        auto levelModifier = 2+((2*attacker.GetCurrentLevel())/5);
        auto statsModifier = GetStatsModifier(AttackingMove,attacker,defender);
        auto criticalHitModifier {attacker.ModifyAttackForCrticalHit(AttackingMove)};
        auto stabModifer {attacker.GetStabModifier(AttackingMove) ? 1.5 : 1.0}; //stab
        auto typeMofider {defender.GetTypeEffectivenessModifer(AttackingMove)};  //typeResistancs and weakness
        auto typeEffectivenessAndStab {stabModifer *  GetTypeEffetiveness(typeMofider)}; //typeResistancs and weakness
        auto  extraModifier = 1 * criticalHitModifier * typeEffectivenessAndStab ; // weahter, badge,status,
        return (extraModifier*(2+((levelModifier* baseDamage * statsModifier)/50)));
    }

    

    void Battle::AttackWith(moves::MoveId mvid,Mockmon & attacker,Mockmon & defender)
    {
        auto chosenMove = std::find_if(attacker.m_Moveset.begin(),attacker.m_Moveset.end(),[&](const moves::EquipedMove  & mv ){ return mv.Identifier() == mvid;});
        Arena arena;//spikes, screens, weather, etc;
        auto usedMove{moves::MoveId::Struggle};
        
        if (chosenMove != attacker.m_Moveset.end() && chosenMove->RemainningPowerPoints()>0)
        {
            usedMove = chosenMove->Identifier();
        }
        const auto & compositeMove = moves::CompositeMove::AllCompositeMoves.at(usedMove);
        compositeMove.Perform(*this,arena,attacker,defender);
        
    }
}