#pragma once
#include "base_condition_mockmon_effecting.h"
#include <numeric>
namespace mockmon::condition
{

    class PoisonCondition : public MockmonEffectingCondition
    {
        public:
        explicit PoisonCondition(Mockmon & poisonedMockmon,double damagePortion):
        MockmonEffectingCondition{PulsingConditionId::Poison,poisonedMockmon},
        m_damagePortion(damagePortion)
        {
        }

        void PulseAfterTurn() override
        {
            const auto damage = static_cast<int>(std::max(r_effected_mockmon.CurrentBattleStats.Health.GetMaxStat() / m_damagePortion,1.0));
            r_effected_mockmon.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
            std::cout << AppendAll({r_effected_mockmon.GetName(), "takes",std::to_string(damage),"damage from",Stringify(conditonId)}) <<'\n';
        }
        private:
        const double m_damagePortion; //percentage of damage max health each turn

    };
}