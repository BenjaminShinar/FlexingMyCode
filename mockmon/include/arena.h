#pragma once
#include "trainer_ai.h"
#include <array>
#include <tuple>

namespace mockmon
{

    // this class will be used to control weahter, screens, entry hazzards, etc...
    // probably badgeboost as well?
    // start as brute force create badge boost, then think again

    class Arena
    {
    public:
        explicit Arena(bool silent) : Silent(silent)
        {
        }
        explicit Arena(const Arena &other) = default;
        ~Arena() = default;
        double GetBadgeBoost(const Trainer &trainer, StatsTypes stat) const;
        void MultiplyBadgeBoost(const Trainer &, StatsTypes stat, double multiply);
        void SetBadgeBoosts(const Trainer &);
        const bool Silent;

    private:
        /**
     * @brief 
     * this holds the badge boosts per trainer
     * not pretty, and should exists.
     */
        std::map<int, std::map<StatsTypes, double>> m_badgeBoosts;

        using boost_tpl = std::tuple<StatsTypes, badges::IndigoBadge, double>;

        static const std::array<boost_tpl, 4> BoostsMap;
    };
}