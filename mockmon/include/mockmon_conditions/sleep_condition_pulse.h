#pragma once
#include "base_conditon_pulse.h"
#include "../mockmon_data.h"
#include "../interfaces.h"
#include "../random_gen.h"
#include <numeric>
namespace mockmon::condition
{

    class SleepCondition : public ConditonPulseEffect
    {
        public:
        explicit SleepCondition(Mockmon & sleepingmockmon,int sleepMaxDuration):
        ConditonPulseEffect{ConditionId::Sleep},
        r_sleeping_mockmon(sleepingmockmon),m_sleep_duration(sleepMaxDuration),m_wake_up_chance(20)
        {
        }

        ~SleepCondition()
        {
            std::cout << r_sleeping_mockmon.GetName() << " is no longer " << conditonId <<'\n';
        }
        void PulseBeforeTurn() override
        {
            if(m_sleep_duration <=0 || random::Randomer::CheckPercentage(m_wake_up_chance))
            {
                m_conditionFinished = true;
            }
        }

        void PulseAfterTurn() override
        {
            --m_sleep_duration;
        }
        private:
        Mockmon & r_sleeping_mockmon;
        unsigned int m_wake_up_chance;
        int m_sleep_duration;

    };
}