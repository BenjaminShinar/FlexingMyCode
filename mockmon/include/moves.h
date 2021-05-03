#pragma once

#include "types.h"
#include "interfaces.h"

#include <string>
#include <string_view>
#include <iostream>
#include <map>
#include <optional>

namespace mockmon::moves
{
    //unique move name
    enum class MoveId
    {
        Absorb,
        Acid,
        AcidArmor,
        Agility,
        Amnesia,
        AuroraBeam,
        Barrage,
        Barrier,
        Bide,
        Bind,
        Bite,
        Blizzard,
        BodySlam,
        BoneClub,
        Bonemerang,
        Bubble,
        BubbleBeam,
        Clamp,
        CometPunch,
        ConfuseRay,
        Confusion,
        Constrict,
        Conversion,
        Counter,
        Crabhammer,
        Cut,
        DefenseCurl,
        Dig,
        Disable,
        DizzyPunch,
        DoubleKick,
        DoubleSlap,
        DoubleTeam,
        DoubleEdge,
        DragonRage,
        DreamEater,
        DrillPeck,
        Earthquake,
        EggBomb,
        Ember,
        Explosion,
        FireBlast,
        FirePunch,
        FireSpin,
        Fissure,
        Flamethrower,
        Flash,
        Fly,
        FocusEnergy,
        FuryAttack,
        FurySwipes,
        Glare,
        Growl,
        Growth,
        Guillotine,
        Gust,
        Harden,
        Haze,
        Headbutt,
        HighJumpKick,
        HornAttack,
        HornDrill,
        HydroPump,
        HyperBeam,
        HyperFang,
        Hypnosis,
        IceBeam,
        IcePunch,
        JumpKick,
        KarateChop,
        Kinesis,
        LeechLife,
        LeechSeed,
        Leer,
        Lick,
        LightScreen,
        LovelyKiss,
        LowKick,
        Meditate,
        MegaDrain,
        MegaKick,
        MegaPunch,
        Metronome,
        Mimic,
        Minimize,
        MirrorMove,
        Mist,
        NightShade,
        PayDay,
        Peck,
        PetalDance,
        PinMissile,
        PoisonGas,
        PoisonPowder,
        PoisonSting,
        Pound,
        Psybeam,
        Psychic,
        Psywave,
        QuickAttack,
        Rage,
        RazorLeaf,
        RazorWind,
        Recover,
        Reflect,
        Rest,
        Roar,
        RockSlide,
        RockThrow,
        RollingKick,
        SandAttack,
        Scratch,
        Screech,
        SeismicToss,
        SelfDestruct,
        Sharpen,
        Sing,
        SkullBash,
        SkyAttack,
        Slam,
        Slash,
        SleepPowder,
        Sludge,
        Smog,
        Smokescreen,
        SoftBoiled,
        SolarBeam,
        SonicBoom,
        SpikeCannon,
        Splash,
        Spore,
        Stomp,
        Strength,
        StringShot,
        Struggle,
        StunSpore,
        Submission,
        Substitute,
        SuperFang,
        Supersonic,
        Surf,
        Swift,
        SwordsDance,
        Tackle,
        TailWhip,
        TakeDown,
        Teleport,
        Thrash,
        Thunder,
        ThunderPunch,
        ThunderShock,
        ThunderWave,
        Thunderbolt,
        Toxic,
        Transform,
        TriAttack,
        Twineedle,
        VineWhip,
        ViseGrip,
        WaterGun,
        Waterfall,
        Whirlwind,
        WingAttack,
        Withdraw,
        Wrap
    };
    std::string moveToStr(const MoveId baseMove);
    std::ostream &operator<<(std::ostream &os, const MoveId &moveId);

    struct BaseMove : public IdentifiybleModule<moves::MoveId>
    {
        explicit BaseMove(moves::MoveId moveId, types::Types type) : IdentifiybleModule(moveId),
                                                                     Type(type)
        {
        }

        const types::Types Type;
    };

    struct SimpleMove : public BaseMove
    {
        explicit SimpleMove(moves::MoveId moveId, types::Types type, unsigned int accuracy, unsigned int power) : BaseMove(moveId, type), BaseAccuracy(accuracy), BasePower(power)
        {
        }
        double CriticalChanceBoost() const;
        const unsigned int BaseAccuracy;
        const unsigned int BasePower;

        static const std::map<moves::MoveId, SimpleMove> AllMoves;
    };

    //this the wrapped constant version the move,how it's handled from the outside
    struct ConstantMove : public IdentifiybleModule<moves::MoveId>
    {
        const unsigned int BaseStartingPowerPoints;
        const unsigned int BaseMaxPowerPoints;

        static const std::map<moves::MoveId, ConstantMove> AllMovesWrappers;

    private:
        explicit ConstantMove(moves::MoveId moveId, unsigned int basePP, unsigned int maxPP) : IdentifiybleModule(moveId),
                                                                                               BaseStartingPowerPoints(basePP), BaseMaxPowerPoints(maxPP)
        {
        }
    };

    //this is the move when it's on a pokemon
    class EquipedMove : public DescribleModule<moves::MoveId>
    {
    public:
        explicit EquipedMove(const ConstantMove &constantMove) : DescribleModule(constantMove.Identifier()),
                                                                 BaseMoveStats(constantMove), m_fullPowerPoints(constantMove.BaseStartingPowerPoints),
                                                                 m_currentPowerPoints(constantMove.BaseStartingPowerPoints)
        {
        }

        const ConstantMove &BaseMoveStats; //what move it refers to, constant db of moves;
        unsigned int RemainningPowerPoints() const;
        std::optional<moves::MoveId> UseMove();
        std::string Describe() const override;

        static constexpr std::size_t MaxMoves = 4;

    private:
        unsigned int m_fullPowerPoints;
        unsigned int m_currentPowerPoints;
        //these probably belong with a friend class;
        void RefillPowerPoints();
        bool IncreasePowerPoints();
    };

    bool CheckMoveAccuracy(const SimpleMove &attack);

    enum class MovesDamageTypes
    {
        NormalDamage,
        AugmentedAmount, // damage based on the normal amount, and other parts?
        FixedAmount,     //always the same
        ScalingAmount,   //based on a stat that isn't attack/defence/special
        OneHitKnockOut   //all the damage
    };

}
