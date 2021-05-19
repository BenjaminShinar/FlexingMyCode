#pragma once
#include "base_conditon_pulse.h"
#include "../mockmon_data.h"
#include "../interfaces.h"

namespace mockmon::condition
{

   class ReflectCondition : public ConditonPulseEffect
    {
        public:
        explicit ReflectCondition(Mockmon & reflectedMockmon):
        ConditonPulseEffect{ConditionId::Reflect},
        r_reflected_mockmon(reflectedMockmon)
        {
        }

        ~ReflectCondition()
        {
            std::cout << r_reflected_mockmon.GetName() << " is no longer under " << conditonId <<'\n';
        }

        private:
        Mockmon & r_reflected_mockmon;

    };
}