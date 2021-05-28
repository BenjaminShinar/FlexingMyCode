#pragma once
#include "base_conditon_pulse.h"
#include "../interfaces.h"
#include "../mockmon_data.h"
namespace mockmon::condition
{

    /**
     * @brief 
     * a base abstract class for conditions?, i guess?
     * hopefully this can be merged with the base class?
     */
    class MockmonEffectingCondition : public ConditonPulseEffect
    {
        protected:
        explicit MockmonEffectingCondition(ConditionId effectingCondition,Mockmon & effectedMockmon):
        ConditonPulseEffect{effectingCondition},
        r_effected_mockmon(effectedMockmon)
        {
        }

        ~MockmonEffectingCondition()
        {
            
            std::cout << AppendAll({r_effected_mockmon.GetName(), "is no longer" , Stringify(conditonId)}) <<'\n';
        }
        
        Mockmon & r_effected_mockmon; // the mockmon effected by the condition
        
    };
}