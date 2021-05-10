#include "specialized_moves.h"
#include <functional>
#include <utility>

namespace mockmon::moves
{
    using namespace std::placeholders; //import this for _1,_2,

    void CompositeMove::Perform(Battle &battle, Arena &arena, Mockmon &attacker, Mockmon &defender) const
    {
        const auto simpleAttackingMove = SimpleMove::AllMoves.at(Identifier());

        if (moves::CheckMoveAccuracy(simpleAttackingMove))
        {
            for (auto &mv : MoveComponenets)
            {
                const auto outomce = mv(battle, arena, simpleAttackingMove, attacker, defender);
                std::cout << outomce.m_moveOutcomeDescrition << '\n';
            }
        }
        else
        {
            std::cout << attacker.GetName() << " missed with " << simpleAttackingMove.Identifier() << '\n';
        }
    }

    //here are some other attacks, will eventually need refactoring
#pragma region attacks

    MoveOutcome RegularMove(Battle &battle, Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    {
        auto damage = static_cast<int>(battle.ModifyAttack(AttackingMove, attacker, defender));
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), " damage!"})};
        return o;
    }

    MoveOutcome RecoilDamageMove(Battle &battle, Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, double divisionFactor)
    {
        auto damage = std::max(1, static_cast<int>(battle.ModifyAttack(AttackingMove, attacker, attacker) / divisionFactor));
        attacker.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "takes", std::to_string(damage), "recoil damage from", Stringify(AttackingMove.Identifier())})};
        return o;
    }

    MoveOutcome ChangeSelfStatMove(Battle &battle, Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  attacker.CurrentStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", "with",Stringify(AttackingMove.Identifier()), "and changed stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

        MoveOutcome ChangeOpponentStatMove(Battle &battle, Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto & statRef =  defender.CurrentStats.m_battleStats.at(effectedStat);
        const auto previous = statRef.GetStat();
        statRef.AddModifier(modifer);
        MoveOutcome o{AppendAll({attacker.GetName(), "used", "with", Stringify(AttackingMove.Identifier()), "and changed", defender.GetName(),"stat from", std::to_string(previous), "to", std::to_string(statRef.GetStat())})};
        return o;
    }

    MoveOutcome DirectDamageByPassResistance(Battle &battle, Arena &arena, const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender, double damage)
    {
        defender.CurrentStats.Health.ChangeHealth(-1 * damage);
        MoveOutcome o{AppendAll({attacker.GetName(), "hit", defender.GetName(), "with", Stringify(AttackingMove.Identifier()), "for", std::to_string(damage), " damage!"})};
        return o;
    }

#pragma endregion

    ExMove CreateSelfBoostingMove(StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto bounded = std::bind(&ChangeSelfStatMove, _1, _2, _3, _4, _5,effectedStat, modifer);
        return bounded;
    }

    ExMove CreateOpponentBoostingMove(StatsTypes effectedStat, StatModifiersLevels modifer)
    {
        auto bounded = std::bind(&ChangeOpponentStatMove, _1, _2, _3, _4, _5,effectedStat, modifer);
        return bounded;
    }

    ExMove CreateNormalRecoilDamagingMove(const double divFactor)
    {
        auto bounded = std::bind(&RecoilDamageMove, _1, _2, _3, _4, _5, divFactor);
        return bounded;
    }

    ExMove CreateDirectDamagingMoveByPassImmunity(const double setDamage)
    {
        auto bounded = std::bind(&DirectDamageByPassResistance, _1, _2, _3, _4, _5, setDamage);
        return bounded;
    }

    


    ExMove CreateNormalDamagingMove()
    {
        return RegularMove;
    }

    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllCompositeMoves{
        //how this works?
        {MoveId::Tackle, CompositeMove(MoveId::Tackle, {CreateNormalDamagingMove()})},
        {MoveId::Struggle, CompositeMove(MoveId::Struggle, {CreateNormalDamagingMove(), CreateNormalRecoilDamagingMove(2.0)})},
        {MoveId::SwordsDance, CompositeMove(MoveId::SwordsDance, {CreateSelfBoostingMove(StatsTypes::Attack,StatModifiersLevels::GreatlyIncrease)})},
        {MoveId::TailWhip, CompositeMove(MoveId::TailWhip, {CreateOpponentBoostingMove(StatsTypes::Defence,StatModifiersLevels::Decrese)})},

        {MoveId::SonicBoom, CompositeMove(MoveId::SonicBoom, {CreateDirectDamagingMoveByPassImmunity(20)})},
        {MoveId::QuickAttack, CompositeMove(MoveId::QuickAttack, {CreateNormalDamagingMove()})},
        // {MoveId::TailWhip,SimpleMove(MoveId::TailWhip,types::Types::Normal,100,5)},
        // {MoveId::QuickAttack,SimpleMove(MoveId::QuickAttack,types::Types::Normal,100,40)},
        // {MoveId::HyperFang,SimpleMove(MoveId::HyperFang,types::Types::Normal,90,80)},
        // {MoveId::FocusEnergy,SimpleMove(MoveId::FocusEnergy,types::Types::Normal,100,5)},
        // {MoveId::SuperFang,SimpleMove(MoveId::SuperFang,types::Types::Normal,90,5)},
        // {MoveId::WaterGun, SimpleMove(MoveId::WaterGun,types::Types::Water,100,40)},
        // {MoveId::Guillotine ,SimpleMove(MoveId::Guillotine ,types::Types::Normal,30,200)},
        // {MoveId::Slash ,SimpleMove(MoveId::Slash ,types::Types::Normal,100,70)},
        // {MoveId::PoisonSting ,SimpleMove(MoveId::PoisonSting,types::Types::Poison ,100,15)}, //status
        // {MoveId::StringShot ,SimpleMove(MoveId::StringShot,types::Types::Bug,95,10)}, //status
        // {MoveId::Ember ,SimpleMove(MoveId::Ember,types::Types::Fire,100,40)},

        //{MoveId::Struggle, SimpleMove(MoveId::Struggle,types::Types::Typeless,50,30)},
    };

    double SeisemeticToss(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    {
        return attacker.GetCurrentLevel();
    }

    double NightShade(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    {
        return attacker.GetCurrentLevel();
    }

    double DragonRage(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    {
        auto typeMofider{defender.GetTypeEffectivenessModifer(AttackingMove)}; //typeResistancs and weakness
        if (typeMofider == types::TypeEffectivenessModifier::NotEffective)
            return 0.0;

        return 40.0;
    }

    double SuperFang(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    {

        //always does half
        return std::max(1, defender.CurrentStats.Health.GetStat());
    }

    double SonicBoom(const moves::SimpleMove &AttackingMove, Mockmon &attacker, Mockmon &defender)
    {
        //always does half
        return std::max(1, defender.CurrentStats.Health.GetStat());
    }

}