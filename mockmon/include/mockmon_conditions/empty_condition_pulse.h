#pragma once
#include "base_conditon_pulse.h"
namespace mockmon::condition
{

    class EmptyCondition : public ConditonPulseEffect
    {
        public:
        explicit EmptyCondition():
        ConditonPulseEffect(ConditionId::Flinch)
        {
        }


    };
}