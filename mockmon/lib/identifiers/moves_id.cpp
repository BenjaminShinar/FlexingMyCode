#include "identifiers/moves_id.h"
#include <iostream>

namespace mockmon::moves
{

    std::string Stringify(const MoveId baseMove)
    {
        switch (baseMove)
        {
            case MoveId::Absorb: return "Absorb"; break;
            case MoveId::Acid: return "Acid"; break;
            case MoveId::AcidArmor: return "Acid Armor"; break;
            case MoveId::Agility: return "Agility"; break;
            case MoveId::Amnesia: return "Amnesia"; break;
            case MoveId::AuroraBeam: return "Aurora Beam"; break;
            case MoveId::Barrage: return "Barrage"; break;
            case MoveId::Barrier: return "Barrier"; break;
            case MoveId::Bide: return "Bide"; break;
            case MoveId::Bind: return "Bind"; break;
            case MoveId::Bite: return "Bite"; break;
            case MoveId::Blizzard: return "Blizzard"; break;
            case MoveId::BodySlam: return "Body Slam"; break;
            case MoveId::BoneClub: return "Bone Club"; break;
            case MoveId::Bonemerang: return "Bonemerang"; break;
            case MoveId::Bubble: return "Bubble"; break;
            case MoveId::BubbleBeam: return "BubbleBeam"; break;
            case MoveId::Clamp: return "Clamp"; break;
            case MoveId::CometPunch: return "Comet Punch"; break;
            case MoveId::ConfuseRay: return "ConfuseRay"; break;
            case MoveId::Confusion: return "Confusion"; break;
            case MoveId::Constrict: return "Constrict"; break;
            case MoveId::Conversion: return "Conversion"; break;
            case MoveId::Counter: return "Counter"; break;
            case MoveId::Crabhammer: return "Crabhammer"; break;
            case MoveId::Cut: return "Cut"; break;
            case MoveId::DefenseCurl: return "DefenseCurl"; break;
            case MoveId::Dig: return "Dig"; break;
            case MoveId::Disable: return "Disable"; break;
            case MoveId::DizzyPunch: return "Dizzy Punch"; break;
            case MoveId::DoubleKick: return "Double Kick"; break;
            case MoveId::DoubleSlap: return "Double Slap"; break;
            case MoveId::DoubleTeam: return "Double Team"; break;
            case MoveId::DoubleEdge: return "Double Edge"; break;
            case MoveId::DragonRage: return "Dragon Rage"; break;
            case MoveId::DreamEater: return "Dream Eater"; break;
            case MoveId::DrillPeck: return "Drill Peck"; break;
            case MoveId::Earthquake: return "Earthquake"; break;
            case MoveId::EggBomb: return "Egg Bomb"; break;
            case MoveId::Ember: return "Ember"; break;
            case MoveId::Explosion: return "Explosion"; break;
            case MoveId::FireBlast: return "Fire Blast"; break;
            case MoveId::FirePunch: return "Fire Punch"; break;
            case MoveId::FireSpin: return "Fire Spin"; break;
            case MoveId::Fissure: return "Fissure"; break;
            case MoveId::Flamethrower: return "Flamethrower"; break;
            case MoveId::Flash: return "Flash"; break;
            case MoveId::Fly: return "Fly"; break;
            case MoveId::FocusEnergy: return "Focus Energy"; break;
            case MoveId::FuryAttack: return "Fury Attack"; break;
            case MoveId::FurySwipes: return "Fury Swipes"; break;
            case MoveId::Glare: return "Glare"; break;
            case MoveId::Growl: return "Growl"; break;
            case MoveId::Growth: return "Growth"; break;
            case MoveId::Guillotine: return "Guillotine"; break;
            case MoveId::Gust: return "Gust"; break;
            case MoveId::Harden: return "Harden"; break;
            case MoveId::Haze: return "Haze"; break;
            case MoveId::Headbutt: return "Headbutt"; break;
            case MoveId::HighJumpKick: return "High Jump Kick"; break;
            case MoveId::HornAttack: return "Horn Attack"; break;
            case MoveId::HornDrill: return "Horn Drill"; break;
            case MoveId::HydroPump: return "Hydro Pump"; break;
            case MoveId::HyperBeam: return "Hyper Beam"; break;
            case MoveId::HyperFang: return "Hyper Fang"; break;
            case MoveId::Hypnosis: return "Hypnosis"; break;
            case MoveId::IceBeam: return "Ice Beam"; break;
            case MoveId::IcePunch: return "Ice Punch"; break;
            case MoveId::JumpKick: return "Jump Kick"; break;
            case MoveId::KarateChop: return "Karate Chop"; break;
            case MoveId::Kinesis: return "Kinesis"; break;
            case MoveId::LeechLife: return "Leech Life"; break;
            case MoveId::LeechSeed: return "Leech Seed"; break;
            case MoveId::Leer: return "Leer"; break;
            case MoveId::Lick: return "Lick"; break;
            case MoveId::LightScreen: return "Light Screen"; break;
            case MoveId::LovelyKiss: return "Lovely Kiss"; break;
            case MoveId::LowKick: return "Low Kick"; break;
            case MoveId::Meditate: return "Meditate"; break;
            case MoveId::MegaDrain: return "Mega Drain"; break;
            case MoveId::MegaKick: return "Mega Kick"; break;
            case MoveId::MegaPunch: return "Mega Punch"; break;
            case MoveId::Metronome: return "Metronome"; break;
            case MoveId::Mimic: return "Mimic"; break;
            case MoveId::Minimize: return "Minimize"; break;
            case MoveId::MirrorMove: return "Mirro rMove"; break;
            case MoveId::Mist: return "Mist"; break;
            case MoveId::NightShade: return "Night Shade"; break;
            case MoveId::PayDay: return "Pay Day"; break;
            case MoveId::Peck: return "Peck"; break;
            case MoveId::PetalDance: return "Petal Dance"; break;
            case MoveId::PinMissile: return "Pin Missile"; break;
            case MoveId::PoisonGas: return "Poison Gas"; break;
            case MoveId::PoisonPowder: return "Poison Powder"; break;
            case MoveId::PoisonSting: return "Poison Sting"; break;
            case MoveId::Pound: return "Pound"; break;
            case MoveId::Psybeam: return "Psybeam"; break;
            case MoveId::Psychic: return "Psychic"; break;
            case MoveId::Psywave: return "Psywave"; break;
            case MoveId::QuickAttack: return "Quick Attack"; break;
            case MoveId::Rage: return "Rage"; break;
            case MoveId::RazorLeaf: return "Razor Leaf"; break;
            case MoveId::RazorWind: return "Razor Wind"; break;
            case MoveId::Recover: return "Recover"; break;
            case MoveId::Reflect: return "Reflect"; break;
            case MoveId::Rest: return "Rest"; break;
            case MoveId::Roar: return "Roar"; break;
            case MoveId::RockSlide: return "Rock Slide"; break;
            case MoveId::RockThrow: return "Rock Throw"; break;
            case MoveId::RollingKick: return "Rolling Kick"; break;
            case MoveId::SandAttack: return "Sand Attack"; break;
            case MoveId::Scratch: return "Scratch"; break;
            case MoveId::Screech: return "Screech"; break;
            case MoveId::SeismicToss: return "Seismic Toss"; break;
            case MoveId::SelfDestruct: return "Self Destruct"; break;
            case MoveId::Sharpen: return "Sharpen"; break;
            case MoveId::Sing: return "Sing"; break;
            case MoveId::SkullBash: return "Skull Bash"; break;
            case MoveId::SkyAttack: return "Sky Attack"; break;
            case MoveId::Slam: return "Slam"; break;
            case MoveId::Slash: return "Slash"; break;
            case MoveId::SleepPowder: return "Sleep Powder"; break;
            case MoveId::Sludge: return "Sludge"; break;
            case MoveId::Smog: return "Smog"; break;
            case MoveId::Smokescreen: return "Smokescreen"; break;
            case MoveId::SoftBoiled: return "Soft Boiled"; break;
            case MoveId::SolarBeam: return "Solar Beam"; break;
            case MoveId::SonicBoom: return "Sonic Boom"; break;
            case MoveId::SpikeCannon: return "Spike Cannon"; break;
            case MoveId::Splash: return "Splash"; break;
            case MoveId::Spore: return "Spore"; break;
            case MoveId::Stomp: return "Stomp"; break;
            case MoveId::Strength: return "Strength"; break;
            case MoveId::StringShot: return "StringShot"; break;
            case MoveId::Struggle: return "Struggle"; break;
            case MoveId::StunSpore: return "Stun Spore"; break;
            case MoveId::Submission: return "Submission"; break;
            case MoveId::Substitute: return "Substitute"; break;
            case MoveId::SuperFang: return "Super Fang"; break;
            case MoveId::Supersonic: return "Supersonic"; break;
            case MoveId::Surf: return "Surf"; break;
            case MoveId::Swift: return "Swift"; break;
            case MoveId::SwordsDance: return "Swords Dance"; break;
            case MoveId::Tackle: return "Tackle"; break;
            case MoveId::TailWhip: return "Tail Whip"; break;
            case MoveId::TakeDown: return "Take Down"; break;
            case MoveId::Teleport: return "Teleport"; break;
            case MoveId::Thrash: return "Thrash"; break;
            case MoveId::Thunder: return "Thunder"; break;
            case MoveId::ThunderPunch: return "Thunder Punch"; break;
            case MoveId::ThunderShock: return "Thunder Shock"; break;
            case MoveId::ThunderWave: return "Thunder Wave"; break;
            case MoveId::Thunderbolt: return "Thunderbolt"; break;
            case MoveId::Toxic: return "Toxic"; break;
            case MoveId::Transform: return "Transform"; break;
            case MoveId::TriAttack: return "Tri Attack"; break;
            case MoveId::Twineedle: return "Twineedle"; break;
            case MoveId::VineWhip: return "Vine Whip"; break;
            case MoveId::ViseGrip: return "Vise Grip"; break;
            case MoveId::WaterGun: return "Water Gun"; break;
            case MoveId::Waterfall: return "Waterfall"; break;
            case MoveId::Whirlwind: return "Whirlwind"; break;
            case MoveId::WingAttack: return "Wing Attack"; break;
            case MoveId::Withdraw: return "Withdraw"; break;
            case MoveId::Wrap: return "Wrap"; break;

            //charged moves?
            case MoveId::WakeUp: return "Wake Up"; break;
            case MoveId::KeepSleeping: return "Keep Sleeping"; break;
            case MoveId::FreezeCantMove: return "Frozen Solied"; break;
            case MoveId::ParalysisCantMove: return "Fully Paralyzed"; break;
            case MoveId::Flinch: return "Flinched"; break;
            case MoveId::HitSelfInConfusion: return "Hit Self In Confusion"; break;
            case MoveId::Recharging: return "Recharge Turn"; break;

            default: return "Unknown move!"; break;
        }
    }

    std::ostream &operator<<(std::ostream &os, const MoveId &e)
    {
        os << Stringify(e);
        return os;
    }
}