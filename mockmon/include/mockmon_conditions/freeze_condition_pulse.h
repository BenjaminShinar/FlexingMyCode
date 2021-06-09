#pragma once
#include "base_condition_mockmon_effecting.h"
#include "../random_gen.h"
#include <numeric>
namespace mockmon::condition
{

    class FreezeCondition : public MockmonEffectingCondition
    {
        public:
        explicit FreezeCondition(Mockmon & frozenMockmon):
        MockmonEffectingCondition{PulsingConditionId::Freeze,frozenMockmon}
        {
        }


        void PulseBeforeTurn() override
        {
            r_effected_mockmon.m_currentCondtion.StoreChargedMove(moves::MoveId::FreezeCantMove);
        }
    };
}