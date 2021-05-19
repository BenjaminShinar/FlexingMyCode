#pragma once
#include "base_conditon_pulse.h"
#include "../mockmon_data.h"
#include "../interfaces.h"
#include <numeric>
namespace mockmon::condition
{

    class BurnCondition : public ConditonPulseEffect
    {
        public:
        explicit BurnCondition(Mockmon & burnedMockmon,double damagePortion):
        ConditonPulseEffect{ConditionId::Burn},
        r_burned_mockmon(burnedMockmon),m_damagePortion(damagePortion)
        {
            //add attack drop
        }

        ~BurnCondition()
        {
            //remove attack drop from burn
            std::cout << r_burned_mockmon.GetName() << " is no longer " << conditonId <<'\n';
        }
        void PulseBeforeTurn() override
        {

        }

        void PulseAfterTurn() override
        {
            const auto damage = static_cast<int>(std::max(r_burned_mockmon.CurrentBattleStats.Health.GetMaxStat() / m_damagePortion,1.0));
            r_burned_mockmon.CurrentBattleStats.Health.ChangeHealth(-1 * damage);
            std::cout << AppendAll({r_burned_mockmon.GetName(), "takes",std::to_string(damage),"damage from the burn!"}) <<'\n';
        }
        private:
        Mockmon & r_burned_mockmon;
        const double m_damagePortion;

    };
}