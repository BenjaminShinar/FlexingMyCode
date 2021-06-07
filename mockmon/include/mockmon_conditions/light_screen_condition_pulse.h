#pragma once
#include "base_condition_mockmon_effecting.h"

namespace mockmon::condition
{

   class LightScreenCondition : public MockmonEffectingCondition
    {
        public:
        explicit LightScreenCondition(Mockmon & reflectedMockmon):
        MockmonEffectingCondition{PulsingConditionId::LightScreen,reflectedMockmon}
        {
        }

    };
}