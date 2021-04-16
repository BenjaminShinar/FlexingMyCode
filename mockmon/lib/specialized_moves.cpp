#include "specialized_moves.h"
namespace mockmon::moves
{
  
       //here are some other attacks, will eventually need refactoring
    void RegularMove(Battle & battle,const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)
    {
        auto damage = static_cast<int>(battle.ModifyAttack(AttackingMove,attacker,defender));
        std::cout<< attacker.GetName() << " hit " << defender.GetName() <<" with " << AttackingMove.Identifier() <<" for " << damage << " damage!" << '\n';
        defender.CurrentStats.Health.ChangeHealth(-1* damage);
    }
    
    double SeisemeticToss(const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)    
    {
        return attacker.GetCurrentLevel();
    }

    double NightShade(const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)    
    {
        return attacker.GetCurrentLevel();
    }

    double DragonRage(const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)
    {
        auto typeMofider {defender.GetTypeEffectivenessModifer(AttackingMove)};  //typeResistancs and weakness
        if (typeMofider == types::TypeEffectivenessModifier::NotEffective)
            return 0.0;
        
        return 40.0;

    }

    double SuperFang(const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)
    {
        
        //always does half
        return std::max(1,defender.CurrentStats.Health.GetStat());
    }

    double SonicBoom(const moves::BaseMove & AttackingMove,Mockmon & attacker,Mockmon & defender)
    {
        //always does half
        return std::max(1,defender.CurrentStats.Health.GetStat());
    }

}