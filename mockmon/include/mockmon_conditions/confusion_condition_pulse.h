#pragma once
#include "base_condition_mockmon_effecting.h"
#include "../random_gen.h"
#include <numeric>
namespace mockmon::condition
{

    class ConfusionCondition : public MockmonEffectingCondition
    {
        public:
        explicit ConfusionCondition(Mockmon & confusedMockmon,int confusionMaxDuration):
        MockmonEffectingCondition{PulsingConditionId::Confusion,confusedMockmon}
        ,m_confusion_duration(confusionMaxDuration),s_hit_self_chance(50)
        {
        }


        void PulseBeforeTurn() override
        {
            if(m_confusion_duration <=0)
            {
                m_conditionFinished = true;
            }
            else if (random::Randomer::CheckPercentage(s_hit_self_chance))
            {
                r_effected_mockmon.m_currentCondtion.StoreChargedMove(moves::MoveId::HitSelfInConfusion);
            }

        }

        void PulseAfterTurn() override
        {
            --m_confusion_duration;
        }
        private:

        int m_confusion_duration;
        unsigned int s_hit_self_chance;

    };
}