#include "arena.h"
#include "damage_calculations.h"
#include <utility>

#include <algorithm>
#include <iterator>
namespace mockmon
{
    /**
 * @brief 
 * mapping badge to stats and the badge boost
 */
    const std::array<Arena::boost_tpl, 4> Arena::BoostsMap{
        std::make_tuple(StatsTypes::Attack, badges::IndigoBadge::Boulder_Badge, 1.125),
        std::make_tuple(StatsTypes::Defence, badges::IndigoBadge::Thunder_Badge, 1.125),
        std::make_tuple(StatsTypes::Speed, badges::IndigoBadge::Soul_Badge, 1.125),
        std::make_tuple(StatsTypes::Special, badges::IndigoBadge::Volcano_Badge, 1.125),
    };

    /**
 * @brief 
 * get badge boost for trainer for stat
 * @param trainer 
 * @param stat 
 * @return double 
 */
    double Arena::GetBadgeBoost(const Trainer &trainer, StatsTypes stat) const
    {
        return GetBadgeBoost(trainer.UniqueTrainerID, stat);
    }
    /**
 * @brief 
 * get badge boost for trainer for stat
 * @param trainer 
 * @param stat 
 * @return double 
 */
    double Arena::GetBadgeBoost(const std::size_t &trainerId, StatsTypes stat) const
    {
        auto trainer_match = m_badgeBoosts.find(trainerId);
        if (trainer_match != std::end(m_badgeBoosts))
        {
            auto stats_match = trainer_match->second.find(stat);
            if (stats_match != std::end(trainer_match->second))
            {
                return stats_match->second;
            }
        }
        return 1.0;
    }

    /**
 * @brief 
 * multiply badgeboost
 * this is the bug?
 * how does Haze mess it up?
 * @param stat 
 * @param multiply 
 */
    void Arena::MultiplyBadgeBoost(const Trainer &trainer, StatsTypes stat, double multiply)
    {
        auto trainer_match = m_badgeBoosts.find(trainer.UniqueTrainerID);
        if (trainer_match != std::end(m_badgeBoosts))
        {
            auto stats_match = trainer_match->second.find(stat);
            if (stats_match != std::end(trainer_match->second))
            {
                stats_match->second *= multiply;
            }
        }
    }

    /**
 * @brief 
 * set the badgeboost
 * use this when leveling up
 */
    void Arena::SetBadgeBoosts(const Trainer &trainer)
    {
        //set badgeboosts
        std::map<StatsTypes, double> boosts{};
        std::transform(std::begin(BoostsMap), std::end(BoostsMap), std::inserter(boosts, std::end(boosts)),
                       [&](const boost_tpl &tpl)
                       {
                           return std::make_pair(std::get<0>(tpl), trainer.CheckBadge(std::get<1>(tpl)) ? std::get<2>(tpl) : 1.0);
                       });
        m_badgeBoosts.insert_or_assign(trainer.UniqueTrainerID, boosts);
    }

    /**
     * @brief 
     * here we can start adding the badge boost glitch, or anyother modifiers
     * @param attacker 
     * @param attackingStat 
     * @param defender 
     * @param defendingStat 
     * @return std::tuple<double, double> 
     */

    std::tuple<double, double> Arena::GetStatsModifier(const Mockmon &attacker, const StatsTypes attackingStat, const Mockmon &defender, const StatsTypes defendingStat) const
    {
        auto getBoost = [&](const Mockmon &m, const StatsTypes s)
        {
            if (auto trainer_id = m.GetCurrentTrainer())
            {
                return GetBadgeBoost(trainer_id.value(), s);
            }
            return 1.0;
        };
        const auto attackerStat = battle::GetSingleStatsModifier(attacker, attackingStat, true);
        const auto attackerBoost{getBoost(attacker, attackingStat)};
        const auto defenderStat = battle::GetSingleStatsModifier(defender, defendingStat, false);
        const auto defenderBoost{getBoost(defender, defendingStat)};
        return std::make_tuple(attackerStat * attackerBoost, defenderStat * defenderBoost); //attack / defence
    }
}