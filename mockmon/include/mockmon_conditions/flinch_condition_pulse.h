#pragma once
#include "base_condition_mockmon_effecting.h"
#include "../random_gen.h"
#include <numeric>
namespace mockmon::condition
{

    class FlinchCondition : public MockmonEffectingCondition
    {
        public:
        explicit FlinchCondition(Mockmon & flinchingMockmon):
        MockmonEffectingCondition{PulsingConditionId::Flinch,flinchingMockmon}
        {
        }


        void PulseBeforeTurn() override
        {
            r_effected_mockmon.m_currentCondtion.StoreChargedMove(moves::MoveId::Flinch);
        }

        void PulseAfterTurn() override
        {
            m_conditionFinished = true;
        }

    };
}