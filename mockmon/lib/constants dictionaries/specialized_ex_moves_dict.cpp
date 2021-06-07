#include "specialized_moves.h"
#include "interfaces.h"

#include "random_gen.h"

#include <initializer_list>
namespace mockmon::moves
{
    using il_exMV = std::initializer_list<ExMove>;

    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllCompositeMoves{
        //how this works?
        MakeDictionaryPair<CompositeMove>(MoveId::Tackle,CreateNormalAccuracyCheck(95,MovesTargeting::AccuracyEvasion),il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Struggle,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical), CreateNormalRecoilDamagingMove(2.0)}),  
        MakeDictionaryPair<CompositeMove>(MoveId::QuickAttack,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        
        //high critical hit rate moves
        MakeDictionaryPair<CompositeMove>(MoveId::Slash,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Crabhammer,CreateNormalAccuracyCheck(90,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial)}),
        MakeDictionaryPair<CompositeMove>(MoveId::KarateChop,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::RazorLeaf,CreateNormalAccuracyCheck(95,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial)}),
          /*
        case MoveId::Slash:
        case MoveId::Crabhammer:
        case MoveId::KarateChop:
        case MoveId::RazorLeaf:
        */
        //a move that can't miss
        MakeDictionaryPair<CompositeMove>(MoveId::Swift,CreateByPassAccuracyCheck(), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        //boosting/hexing moves
        MakeDictionaryPair<CompositeMove>(MoveId::SwordsDance,CreateSetAccuracyCheck(100), il_exMV{CreateSelfStatChangingMove(StatsTypes::Attack,StatModifiersLevels::GreatlyIncrease)}),
        MakeDictionaryPair<CompositeMove>(MoveId::TailWhip,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentStatChangingMove(StatsTypes::Defence,StatModifiersLevels::Decrese)}),
        MakeDictionaryPair<CompositeMove>(MoveId::StringShot,CreateNormalAccuracyCheck(95,MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentStatChangingMove(StatsTypes::Speed,StatModifiersLevels::Decrese)}),


       // MakeDictionaryPair<CompositeMove>(MoveId::FocusEnergy,CreateByPassAccuracyCheck(), il_exMV{CreateSelfConditionMove({types::Types::Normal,condition::PulsingConditionId::Reflect,100})},

        //set damage moves
        MakeDictionaryPair<CompositeMove>(MoveId::SonicBoom, CreateNormalAccuracyCheck(90,MovesTargeting::AccuracyEvasion),il_exMV{CreateDirectDamagingMoveByPassImmunity(20)}),
        MakeDictionaryPair<CompositeMove>(MoveId::DragonRage,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveByPassImmunity(40)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SuperFang,CreateNormalAccuracyCheck(90,MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveTargetStateByPassImmunity([](const Mockmon & m){return std::max(1.0,m.CurrentBattleStats.Health.GetStat()/2.0);})}),
        MakeDictionaryPair<CompositeMove>(MoveId::SeismicToss,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon & m){return std::max(1.0,m.GetCurrentLevel()*1.0);})}),
        MakeDictionaryPair<CompositeMove>(MoveId::NightShade,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon & m){return std::max(1.0,m.GetCurrentLevel()*1.0);})}),
        MakeDictionaryPair<CompositeMove>(MoveId::Psywave,CreateNormalAccuracyCheck(80,MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon & m){return std::max(1.0,1.0 + random::Randomer::GetRandom(m.GetCurrentLevel()));})}),

        // moves that can efflict Status in addition to damage
        //CreateOpponentConditionMove
        MakeDictionaryPair<CompositeMove>(MoveId::PoisonSting,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion),il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical),CreateOpponentPulsingConditionMove({types::Types::Poison,30,condition::PulsingConditionId::Poison})}),
        MakeDictionaryPair<CompositeMove>(MoveId::Ember,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion),il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial),CreateOpponentPulsingConditionMove({types::Types::Fire,10,condition::PulsingConditionId::Burn})}),
        
        // moves that only efflict conditions
        MakeDictionaryPair<CompositeMove>(MoveId::PoisonPowder,CreateNormalAccuracyCheck(75,MovesTargeting::AccuracyEvasion),il_exMV{CreateOpponentPulsingConditionMove({types::Types::Poison,100,condition::PulsingConditionId::Poison})}),
        MakeDictionaryPair<CompositeMove>(MoveId::SleepPowder,CreateNormalAccuracyCheck(75,MovesTargeting::AccuracyEvasion),il_exMV{CreateOpponentPulsingConditionMove({types::Types::Grass,100,condition::PulsingConditionId::Sleep})}),
        MakeDictionaryPair<CompositeMove>(MoveId::StunSpore,CreateNormalAccuracyCheck(75,MovesTargeting::AccuracyEvasion),il_exMV{CreateOpponentPulsingConditionMove({types::Types::Grass,100,condition::PulsingConditionId::Paralysis})}),

        MakeDictionaryPair<CompositeMove>(MoveId::Reflect,CreateSetAccuracyCheck(100),il_exMV{CreateSelfNonPulsingConditionMove({types::Types::Psychic,100,condition::NonPulsingConditionId::Reflect})}),
        MakeDictionaryPair<CompositeMove>(MoveId::LightScreen,CreateSetAccuracyCheck(100),il_exMV{CreateSelfNonPulsingConditionMove({types::Types::Psychic,100,condition::NonPulsingConditionId::LightScreen})}),
        MakeDictionaryPair<CompositeMove>(MoveId::Haze,CreateSetAccuracyCheck(100),il_exMV{CreateResetSelfConditionMove(),CreateResetOpponentConditionMove()}),


        // two turn moves
        // charge up moves, bypass accuracy check?
        MakeDictionaryPair<CompositeMove>(MoveId::SolarBeam,CreateByPassAccuracyCheck(),il_exMV{CreateStoredMove(MoveId::SolarBeam)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkullBash,CreateByPassAccuracyCheck(),il_exMV{CreateStoredMove(MoveId::SkullBash)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkyAttack,CreateByPassAccuracyCheck(),il_exMV{CreateStoredMove(MoveId::SkyAttack)}),

        // semi invurnable
        MakeDictionaryPair<CompositeMove>(MoveId::Dig,CreateByPassAccuracyCheck(),il_exMV{CreateStoredMove(MoveId::Dig)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Fly,CreateByPassAccuracyCheck(),il_exMV{CreateStoredMove(MoveId::Fly)}),

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


    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllChargedCompositeMoves
    {
        MakeDictionaryPair<CompositeMove>(MoveId::SolarBeam,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkullBash,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkyAttack,CreateNormalAccuracyCheck(90,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        
        //semi invunable
        MakeDictionaryPair<CompositeMove>(MoveId::Dig,CreateNormalAccuracyCheck(100,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Fly,CreateNormalAccuracyCheck(95,MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        MakeDictionaryPair<CompositeMove>(MoveId::Recharging,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),

//effected by conditions
        MakeDictionaryPair<CompositeMove>(MoveId::WakeUp,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::KeepSleeping,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::Flinch,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::ParalysisCantMove,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::FreezeCantMove,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::HitSelfInConfusion,CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
    };
}