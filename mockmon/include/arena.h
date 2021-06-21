#pragma once
#include "trainer.h"
#include <array>
#include <tuple>

namespace mockmon
{

    // this class will be used to control weahter, screens, entry hazzards, etc...
    // probably badgeboost as well?
    // start as brute force create badge boost, then think again
    // maybe this can also be the basis for double battles?
    // the arena hold the trainers?
    // some arenas negate the badge boost (pvp)
    // this will also take care of leech seed and stuff that effect one side of the field

    class Arena
    {
    public:
        explicit Arena(bool silent) : Silent(silent)
        {
        }
        explicit Arena(const Arena &other) = default;
        ~Arena() = default;
        double GetBadgeBoost(const Trainer &trainer, StatsTypes stat) const;
        double GetBadgeBoost(const std::size_t &trainerId, StatsTypes stat) const;

        void MultiplyBadgeBoost(const Trainer &, StatsTypes stat, double multiply);
        void SetBadgeBoosts(const Trainer &);
        std::tuple<double, double> GetStatsModifier(const Mockmon &attacker, const StatsTypes attackingStat, const Mockmon &defender, const StatsTypes defendingStat) const;
        const bool Silent;

    private:
        /**
     * @brief 
     * this holds the badge boosts per trainer
     * not pretty, and should exists.
     */
        std::map<std::size_t, std::map<StatsTypes, double>> m_badgeBoosts;

        using boost_tpl = std::tuple<StatsTypes, badges::IndigoBadge, double>;

        static const std::array<boost_tpl, 4> BoostsMap;
    };
}