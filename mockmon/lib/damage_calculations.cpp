
#include "damage_calculations.h"
#include "random_gen.h"

#include <algorithm>
#include <numeric>

namespace mockmon::battle
{

    double GetSingleStatsModifier(const Mockmon &mockmon, const StatsTypes statType, bool isAttacking)
    {
        const auto stat = mockmon.CurrentBattleStats.m_battleStats.at(statType).GetStat() * mockmon.m_currentCondtion.GetConditionalBoost(statType, isAttacking);
        return stat;
    }

    double GetDamageRanges()
    {
        const auto r = random::Randomer::GetRandom(16);
        return ((100.0 - r) / 100.0);
    }

    double GetLevelDamageModifier(const Mockmon &m)
    {
        return 2 + ((2 * m.GetCurrentLevel()) / 5);
    }

    double GetLevelCriticalDamageModifier(const Mockmon &m)
    {
        const auto level = m.GetCurrentLevel();
        auto damageBoost = (5.0 + (level * 2.0)) / (level + 5.0);
        if (m.DisplayEvent())
        {
            std::cout << m.GetName() << " scored a critical hit"
                      << " boost factor: " << damageBoost << '\n';
        }
        return damageBoost;
    }

    double GetStabDamageModifier(bool isStab)
    {
        return isStab ? 1.5 : 1.0;
    }

    double GetTypeEffetivenessModifier(types::TypeEffectivenessModifier modifier)
    {
        using types::TypeEffectivenessModifier;
        switch (modifier)
        {
        case TypeEffectivenessModifier::NotEffective:
            return 0.0;
            break;
        case TypeEffectivenessModifier::VeryNotEffective:
            return 0.25;
            break;
        case TypeEffectivenessModifier::NotVeryEffective:
            return 0.5;
            break;
        case TypeEffectivenessModifier::NormalEffective:
            return 1.0;
            break;
        case TypeEffectivenessModifier::VeryEffective:
            return 2.0;
            break;
        case TypeEffectivenessModifier::SuperEffective:
            return 4.0;
            break;
        default:
            break;
        }

        return 1.0;
    } //how an attack effects this pokemon

}