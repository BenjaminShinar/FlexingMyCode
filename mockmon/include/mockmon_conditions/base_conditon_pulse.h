#pragma once
#include "../identifiers/condition_id.h"
#include <numeric>
namespace mockmon::condition
{
    // a functor that does something to the mockmon each turn, like take damage?
    class ConditonPulseEffect
    {
        protected:
        explicit ConditonPulseEffect(ConditionId condition):
        conditonId(condition)
        {}

        bool m_conditionFinished{false};

        public:
                virtual ~ConditonPulseEffect() = default;

        virtual void PulseAfterTurn() = 0; //virtual abstract       
        virtual void PulseBeforeTurn() = 0; //virtual abstract       
        bool CanBeRemoved() const {return m_conditionFinished;} //stuff that removes itself after X turns?
        const ConditionId conditonId;
        
    };

}