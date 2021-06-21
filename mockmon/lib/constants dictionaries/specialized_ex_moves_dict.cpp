#include "specialized_moves.h"
#include "interfaces.h"

#include "random_gen.h"

#include <initializer_list>
namespace mockmon::moves
{
    using il_exMV = std::initializer_list<ExMove>;

    /**
     * @brief 
     * this is probably the biggest dictionary/data base in the current engine
     * this controls what each move does
     */
    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllCompositeMoves{
        MakeDictionaryPair<CompositeMove>(MoveId::Tackle, CreateNormalAccuracyCheck(95, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Struggle, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical), CreateNormalRecoilDamagingMove(2.0)}),
        MakeDictionaryPair<CompositeMove>(MoveId::QuickAttack, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        //high critical hit rate moves
        MakeDictionaryPair<CompositeMove>(MoveId::Slash, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Crabhammer, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial)}),
        MakeDictionaryPair<CompositeMove>(MoveId::KarateChop, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::RazorLeaf, CreateNormalAccuracyCheck(95, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial)}),

        //a move that can't miss
        MakeDictionaryPair<CompositeMove>(MoveId::Swift, CreateByPassAccuracyCheck(), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        //boosting/hexing moves
        MakeDictionaryPair<CompositeMove>(MoveId::DefenseCurl, CreateByPassAccuracyCheck(), il_exMV{CreateSelfStatChangingMove(StatsTypes::Defence, StatModifiersLevels::Increase)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Harden, CreateByPassAccuracyCheck(), il_exMV{CreateSelfStatChangingMove(StatsTypes::Defence, StatModifiersLevels::Increase)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SwordsDance, CreateByPassAccuracyCheck(), il_exMV{CreateSelfStatChangingMove(StatsTypes::Attack, StatModifiersLevels::GreatlyIncrease)}),
        MakeDictionaryPair<CompositeMove>(MoveId::TailWhip, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentStatChangingMove(StatsTypes::Defence, StatModifiersLevels::Decrese)}),
        MakeDictionaryPair<CompositeMove>(MoveId::StringShot, CreateNormalAccuracyCheck(95, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentStatChangingMove(StatsTypes::Speed, StatModifiersLevels::Decrese)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Growl, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentStatChangingMove(StatsTypes::Attack, StatModifiersLevels::Decrese)}),
        MakeDictionaryPair<CompositeMove>(MoveId::DoubleTeam, CreateByPassAccuracyCheck(), il_exMV{CreateSelfStatChangingMove(StatsTypes::Evasion, StatModifiersLevels::Increase)}),

        //set damage moves
        MakeDictionaryPair<CompositeMove>(MoveId::SonicBoom, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveByPassImmunity(20)}),
        MakeDictionaryPair<CompositeMove>(MoveId::DragonRage, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveByPassImmunity(40)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SuperFang, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveTargetStateByPassImmunity([](const Mockmon &m)
                                                                                                                                                                                       { return std::max(1.0, m.CurrentBattleStats.Health.GetStat() / 2.0); })}),
        MakeDictionaryPair<CompositeMove>(MoveId::SeismicToss, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon &m)
                                                                                                                                                                                            { return std::max(1.0, m.GetCurrentLevel() * 1.0); })}),
        MakeDictionaryPair<CompositeMove>(MoveId::NightShade, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon &m)
                                                                                                                                                                                           { return std::max(1.0, m.GetCurrentLevel() * 1.0); })}),
        MakeDictionaryPair<CompositeMove>(MoveId::Psywave, CreateNormalAccuracyCheck(80, MovesTargeting::AccuracyEvasion), il_exMV{CreateDirectDamagingMoveAttackerStateByPassImmunity([](const Mockmon &m)
                                                                                                                                                                                       { return std::max(1.0, 1.0 + random::Randomer::GetRandom(m.GetCurrentLevel())); })}),

        // moves that can efflict Status in addition to damage
        //CreateOpponentConditionMove
        MakeDictionaryPair<CompositeMove>(MoveId::PoisonSting, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical), CreateOpponentPulsingConditionMove({types::Types::Poison, {30, {types::Types::Poison, types::Types::Steel}, {}}, condition::PulsingConditionId::Poison})}),
        //burnning moves

        MakeDictionaryPair<CompositeMove>(MoveId::Ember, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial), CreateOpponentPulsingConditionMove({types::Types::Fire, {10, {types::Types::Fire}, {}}, condition::PulsingConditionId::Burn}), CreateRemoveOpponentPulsingConditionMove({types::Types::Fire, {100, {}, {}}, condition::PulsingConditionId::Freeze})}),

        //freezing moves
        MakeDictionaryPair<CompositeMove>(MoveId::IcePunch, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial), CreateOpponentPulsingConditionMove({types::Types::Ice, {10, {types::Types::Ice}, {}}, condition::PulsingConditionId::Freeze})}),
        MakeDictionaryPair<CompositeMove>(MoveId::IceBeam, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial), CreateOpponentPulsingConditionMove({types::Types::Ice, {10, {types::Types::Ice}, {}}, condition::PulsingConditionId::Freeze})}),
        MakeDictionaryPair<CompositeMove>(MoveId::Blizzard, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial), CreateOpponentPulsingConditionMove({types::Types::Ice, {10, {types::Types::Ice}, {}}, condition::PulsingConditionId::Freeze})}),

        //parylsis moves
        MakeDictionaryPair<CompositeMove>(MoveId::BodySlam, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical), CreateOpponentPulsingConditionMove({types::Types::Normal, {30, {types::Types::Normal}, {}}, condition::PulsingConditionId::Paralysis})}),
        MakeDictionaryPair<CompositeMove>(MoveId::Lick, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial), CreateOpponentPulsingConditionMove({types::Types::Ghost, {30, {types::Types::Ghost}, {}}, condition::PulsingConditionId::Paralysis})}),

        //flinching moves
        MakeDictionaryPair<CompositeMove>(MoveId::HyperFang, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical), CreateOpponentPulsingConditionMove({types::Types::Normal, {10, {}, {}}, condition::PulsingConditionId::Flinch})}),

        // moves that only efflict conditions
        MakeDictionaryPair<CompositeMove>(MoveId::Spore, CreateNormalAccuracyCheck(75, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentPulsingConditionMove({types::Types::Grass, {100, {types::Types::Grass}, {}}, condition::PulsingConditionId::Sleep})}),
        MakeDictionaryPair<CompositeMove>(MoveId::PoisonPowder, CreateNormalAccuracyCheck(75, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentPulsingConditionMove({types::Types::Poison, {100, {types::Types::Poison, types::Types::Steel}, {}}, condition::PulsingConditionId::Poison})}),
        MakeDictionaryPair<CompositeMove>(MoveId::SleepPowder, CreateNormalAccuracyCheck(75, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentPulsingConditionMove({types::Types::Grass, {100, {types::Types::Grass}, {}}, condition::PulsingConditionId::Sleep})}),
        MakeDictionaryPair<CompositeMove>(MoveId::StunSpore, CreateNormalAccuracyCheck(75, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentPulsingConditionMove({types::Types::Grass, {100, {types::Types::Grass}, {}}, condition::PulsingConditionId::Paralysis})}),
        MakeDictionaryPair<CompositeMove>(MoveId::ConfuseRay, CreateNormalAccuracyCheck(75, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentPulsingConditionMove({types::Types::Ghost, {100, {}, {}}, condition::PulsingConditionId::Confusion})}),
        MakeDictionaryPair<CompositeMove>(MoveId::ThunderWave, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateOpponentPulsingConditionMove({types::Types::Electric, {100, {types::Types::Electric, types::Types::Ground}, {}}, condition::PulsingConditionId::Paralysis})}),

        MakeDictionaryPair<CompositeMove>(MoveId::Reflect, CreateByPassAccuracyCheck(), il_exMV{CreateSelfNonPulsingConditionMove({types::Types::Psychic, {100, {}, {}}, condition::NonPulsingConditionId::Reflect})}),
        MakeDictionaryPair<CompositeMove>(MoveId::LightScreen, CreateByPassAccuracyCheck(), il_exMV{CreateSelfNonPulsingConditionMove({types::Types::Psychic, {100, {}, {}}, condition::NonPulsingConditionId::LightScreen})}),
        MakeDictionaryPair<CompositeMove>(MoveId::FocusEnergy, CreateByPassAccuracyCheck(), il_exMV{CreateSelfNonPulsingConditionMove({types::Types::Normal, {100, {}, {}}, condition::NonPulsingConditionId::FocusEnergy})}),

        MakeDictionaryPair<CompositeMove>(MoveId::Haze, CreateByPassAccuracyCheck(), il_exMV{CreateResetSelfConditionMove(), CreateResetOpponentConditionMove()}),

        //ONE HIT KO Moves
        MakeDictionaryPair<CompositeMove>(MoveId::Fissure, CreateCheckSpeedThenNormalAccuracyCheck(30, MovesTargeting::AccuracyEvasion), il_exMV{CreateOHKOMove()}),    //OH-KO!
        MakeDictionaryPair<CompositeMove>(MoveId::Guillotine, CreateCheckSpeedThenNormalAccuracyCheck(30, MovesTargeting::AccuracyEvasion), il_exMV{CreateOHKOMove()}), //OH-KO!
        MakeDictionaryPair<CompositeMove>(MoveId::HornDrill, CreateCheckSpeedThenNormalAccuracyCheck(30, MovesTargeting::AccuracyEvasion), il_exMV{CreateOHKOMove()}),  //OH-KO!

        // two turn moves
        // recharge moves
        MakeDictionaryPair<CompositeMove>(MoveId::HyperBeam, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical), CreateStoredMove(MoveId::Recharging)}),

        // charge up moves, bypass accuracy check?
        MakeDictionaryPair<CompositeMove>(MoveId::SolarBeam, CreateByPassAccuracyCheck(), il_exMV{CreateStoredMove(MoveId::SolarBeam)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkullBash, CreateByPassAccuracyCheck(), il_exMV{CreateStoredMove(MoveId::SkullBash)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkyAttack, CreateByPassAccuracyCheck(), il_exMV{CreateStoredMove(MoveId::SkyAttack)}),

        // semi invurnable
        MakeDictionaryPair<CompositeMove>(MoveId::Dig, CreateByPassAccuracyCheck(), il_exMV{CreateStoredMove(MoveId::Dig)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Fly, CreateByPassAccuracyCheck(), il_exMV{CreateStoredMove(MoveId::Fly)}),
    };

    /**
     * @brief 
     * this database holds the effects of moves in thier 2nd stage.
     * not when they are used, but in the turn afterwards
     */
    const std::map<moves::MoveId, CompositeMove> CompositeMove::AllChargedCompositeMoves{
        MakeDictionaryPair<CompositeMove>(MoveId::SolarBeam, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PureSpecial)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkullBash, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::SkyAttack, CreateNormalAccuracyCheck(90, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        //semi invunable
        MakeDictionaryPair<CompositeMove>(MoveId::Dig, CreateNormalAccuracyCheck(100, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),
        MakeDictionaryPair<CompositeMove>(MoveId::Fly, CreateNormalAccuracyCheck(95, MovesTargeting::AccuracyEvasion), il_exMV{CreateNormalDamagingMove(MovesTargeting::PurePhysical)}),

        MakeDictionaryPair<CompositeMove>(MoveId::Recharging, CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),

        //effected by conditions
        MakeDictionaryPair<CompositeMove>(MoveId::WakeUp, CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::KeepSleeping, CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::Flinch, CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::ParalysisCantMove, CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::FreezeCantMove, CreateByPassAccuracyCheck(), il_exMV{CreateWastedTurnMove()}),
        MakeDictionaryPair<CompositeMove>(MoveId::HitSelfInConfusion, CreateByPassAccuracyCheck(), il_exMV{CreateNormalSelfDamagingMove(MovesTargeting::PurePhysical)}),
    };
}