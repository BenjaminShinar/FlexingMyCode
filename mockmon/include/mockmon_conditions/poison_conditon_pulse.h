#pragma once
#include "base_conditon_pulse.h"
#include "../mockmon_data.h"
#include "../interfaces.h"
#include <numeric>
namespace mockmon::condition
{

    class PoisonCondition : public ConditonPulseEffect
    {
        public:
        explicit PoisonCondition(Mockmon & poisonedMockmon,double damagePortion):
        ConditonPulseEffect{ConditionId::Poison},
        r_poisoned_mockmon(poisonedMockmon),m_damagePortion(damagePortion)
        {
        }

        ~PoisonCondition()
        {
            std::cout << r_poisoned_mockmon.GetName() << " is no longer " << conditonId <<'\n';
        }
        void PulseBeforeTurn() override
        {

        }

        void PulseAfterTurn() override
        {
            const auto damage = static_cast<int>(std::max(r_poisoned_mockmon.CurrentStats.Health.GetMaxStat() / m_damagePortion,1.0));
            r_poisoned_mockmon.CurrentStats.Health.ChangeHealth(-1 * damage);
            std::cout << AppendAll({r_poisoned_mockmon.GetName(), "takes",std::to_string(damage),"damage from the poison!"}) <<'\n';
        }
        private:
        Mockmon & r_poisoned_mockmon;
        const double m_damagePortion;

    };
}