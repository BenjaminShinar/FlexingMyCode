#pragma once
#include "base_condition_mockmon_effecting.h"
#include "../random_gen.h"
#include <numeric>
namespace mockmon::condition
{

    class SleepCondition : public MockmonEffectingCondition
    {
        public:
        explicit SleepCondition(Mockmon & sleepingmockmon,int sleepMaxDuration):
        MockmonEffectingCondition{PulsingConditionId::Sleep,sleepingmockmon}
        ,m_sleep_duration(sleepMaxDuration),m_wake_up_chance(20)
        {
        }


        void PulseBeforeTurn() override
        {
            if(m_sleep_duration <=0 || random::Randomer::CheckPercentage(m_wake_up_chance))
            {
                m_conditionFinished = true;
                r_effected_mockmon.m_currentCondtion.StoreChargedMove(moves::MoveId::WakeUp);
            }
            else
            {
                r_effected_mockmon.m_currentCondtion.StoreChargedMove(moves::MoveId::KeepSleeping);
            }

        }

        void PulseAfterTurn() override
        {
            --m_sleep_duration;
        }
        private:

        int m_sleep_duration;
        unsigned int m_wake_up_chance;

    };
}