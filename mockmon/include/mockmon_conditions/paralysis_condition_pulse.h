#pragma once
#include "base_condition_mockmon_effecting.h"
#include "../random_gen.h"
#include <numeric>
namespace mockmon::condition
{

    class ParalysisCondition : public MockmonEffectingCondition
    {
        public:
        explicit ParalysisCondition(Mockmon & paralyzedMockmon):
        MockmonEffectingCondition{PulsingConditionId::Paralysis,paralyzedMockmon},m_full_paralysis_chance(25)
        {
        }


        void PulseBeforeTurn() override
        {
            if(random::Randomer::CheckPercentage(m_full_paralysis_chance))
            {
                r_effected_mockmon.m_currentCondtion.StoreChargedMove(moves::MoveId::ParalysisCantMove);
            }
        }
        private:

        unsigned int m_full_paralysis_chance;

    };
}