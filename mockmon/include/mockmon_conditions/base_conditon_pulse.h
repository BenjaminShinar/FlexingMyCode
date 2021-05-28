#pragma once
#include "../identifiers/condition_id.h"
namespace mockmon::condition
{
 
    /**
     * @brief 
     * a functor that does something to the mockmon each turn, like take damage?
     * can we store the mockmon in the base class?
     */
    class ConditonPulseEffect
    {
        protected:
        explicit ConditonPulseEffect(ConditionId condition):
        conditonId(condition)
        {}

        bool m_conditionFinished{false};

        public:
        
        virtual ~ConditonPulseEffect() = default;
        virtual void PulseAfterTurn() {}; //virtual function       
        virtual void PulseBeforeTurn() {}; //virtual function       
        bool CanBeRemoved() const {return m_conditionFinished;} //stuff that removes itself after X turns?
        const ConditionId conditonId; //what is the condition itself.
    };

}