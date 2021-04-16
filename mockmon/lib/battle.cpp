#include "battle.h"
#include "controller.h"
#include "random_gen.h"
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
        int round =0;
        while (r_playerMockmon.IsAbleToBattle() && r_enemyMockmon.IsAbleToBattle())
        {
            std::cout << r_playerMockmon.GetName() <<" is engaging in battle with " << r_enemyMockmon.GetName()<< " starting round " << ++round <<'\n';
            PlayerTurn();
            if (r_enemyMockmon.IsAbleToBattle())
            {
                EnemyTurn();
            }
        }
        auto endAction = r_playerMockmon.IsAbleToBattle()? controller::controllerEnum::ACTION_A : controller::controllerEnum::CANCEL_B;
        DetermineBattle(endAction);
        const auto winner = r_playerMockmon.IsAbleToBattle() ? r_playerMockmon.GetName() : r_enemyMockmon.GetName();
        std::cout << "Battle ended at round " <<  round << " winner: "<< winner<<'\n';
    }

    void Battle::PlayerTurn()
    {
        auto attack = controller::GetAnyInput("which move to use?",r_playerMockmon.GetMoveSet());
        AttackWith(attack,r_playerMockmon,r_enemyMockmon);
    }

    void Battle::EnemyTurn()
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

    double Battle::ModifyAttack(const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)
    {
        auto baseDamage = AttackingMove.BasePower;
        auto levelModifier = 2+((2*attacker.CurrentLevel)/5);
        auto statsModifier = attacker.CurrentStats.Attack.GetStat() / defender.CurrentStats.Defence.GetStat(); //attack / defence
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
        
        if (chosenMove != attacker.m_Moveset.end() && chosenMove->RemainningPowerPoints()>0)
        {
            if (chosenMove->UseMove())
            {
                auto damage = static_cast<int>(ModifyAttack(moves::BaseMove::AllMoves.at(chosenMove->Identifier()),attacker,defender));
                std::cout<< attacker.GetName() << " hit " << defender.GetName() <<" with " << (*chosenMove).Identifier() <<" for " << damage << " damage!" << '\n';
                defender.CurrentStats.Health.ChangeHealth(-1* damage);
            }
            else
            {
                std::cout<< attacker.GetName() << " missed with " << (*chosenMove).Identifier() << '\n';
            }  
        }
        else
        {
            const auto struggleMove = moves::BaseMove::AllMoves.at(moves::MoveId::Struggle);
            if (moves::CheckMoveAccuracy(struggleMove))
            {
                auto damage = static_cast<int>(ModifyAttack(struggleMove,attacker,defender));
                auto recoilDamage =static_cast<int>(std::max(1.0,damage/2.0));
                std::cout<< attacker.GetName() << " struggles with  " << defender.GetName() <<" and managed to hit for " << damage << " damage!" << '\n';
                std::cout<< attacker.GetName() << " takes " << recoilDamage << " recoile damage while struggling!" << '\n';
                defender.CurrentStats.Health.ChangeHealth(-1* damage);
                attacker.CurrentStats.Health.ChangeHealth(-1* recoilDamage);
            }
            else
            {
                std::cout<< attacker.GetName() << " missed with " << struggleMove.Identifier() << '\n';
            }
        }
        
    }
}