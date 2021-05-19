#pragma once
#include "base_conditon_pulse.h"
#include "../mockmon_data.h"
#include "../interfaces.h"

namespace mockmon::condition
{

   class LightScreenCondition : public ConditonPulseEffect
    {
        public:
        explicit LightScreenCondition(Mockmon & reflectedMockmon):
        ConditonPulseEffect{ConditionId::LightScreen},
        r_screened_mockmon(reflectedMockmon)
        {
        }

        ~LightScreenCondition()
        {
            std::cout << r_screened_mockmon.GetName() << " is no longer under " << conditonId <<'\n';
        }
        private:
        Mockmon & r_screened_mockmon;

    };
}