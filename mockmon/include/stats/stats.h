#pragma once

#include "../identifiers/moves_id.h"
#include "../identifiers/stat_modifiers_id.h"
#include "../identifiers/stats_id.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <map>

namespace mockmon::stats
{

    const unsigned int MaxStatValue = 65535; //2^16-1 max short

    struct StatsValues
    {
        unsigned int Health{1};
        unsigned int Attack{1};
        unsigned int Defence{1};
        unsigned int Special{1};
        unsigned int Speed{1};
    };

    //this is what species have, it cant be changed
    //Health, attack,Defence,Special,Speed
    struct SpeciesBaseStats
    {
        const StatsValues Stats;
    };

    struct EffortValuesStats
    {
        StatsValues Stats;
        void GainEffortValueStats(const SpeciesBaseStats &enemiesBaseStats);
    };

    struct IndividualStats
    {
    public:
        const StatsValues Stats;

    private:
        //this is used just in the ctor.
        [[nodiscard]] static constexpr unsigned int CalculateHealth(unsigned int attack, unsigned int defence, unsigned int special, unsigned int speed)
        {
            auto a1 = (attack & 0x1) << 0;
            auto a2 = (defence & 0x1) << 1;
            auto a3 = (speed & 0x1) << 2;
            auto a4 = (special & 0x1) << 3;

            return (a1 | a2 | a3 | a4);
        }

    public:
        //player mockmon data
        explicit IndividualStats(unsigned int attack, unsigned int defence, unsigned int special, unsigned int speed) : Stats{
                                                                                                                            CalculateHealth(attack, defence, special, speed),
                                                                                                                            attack,
                                                                                                                            defence,
                                                                                                                            special,
                                                                                                                            speed,
                                                                                                                        }
        {
        }

        //this is for enemies
        explicit IndividualStats() : Stats{
                                         CalculateHealth(9u, 8u, 8u, 8u),
                                         9u,
                                         8u,
                                         8u,
                                         8u,
                                     }
        {
        }
    };

    //think about how this should work
    struct MockmonStats
    {
        // base, iv,evs
        explicit MockmonStats() = default;
        explicit MockmonStats(const SpeciesBaseStats &speciesBaseStats, const IndividualStats &IVStats, const EffortValuesStats &EVStats, unsigned int level);

        StatsValues Stats;
        [[nodiscard]] static unsigned int ModifyStat(unsigned int base, unsigned int iv, unsigned int ev, unsigned int level);
    };
}