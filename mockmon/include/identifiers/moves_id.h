#pragma once
#include <string>
#include <iostream>
namespace mockmon::moves
{
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
    std::string Stringify(const MoveId moveId);
        std::ostream &operator<<(std::ostream &os, const MoveId &e);


}