#pragma once
#include "base_condition_mockmon_effecting.h"

namespace mockmon::condition
{

   class ReflectCondition : public MockmonEffectingCondition
    {
        public:
        explicit ReflectCondition(Mockmon & reflectedMockmon):
        MockmonEffectingCondition{PulsingConditionId::Reflect,reflectedMockmon}
        {
        }

    };
}