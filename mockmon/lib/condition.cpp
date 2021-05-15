#include "condition.h"
#include <algorithm>
#include <functional>
namespace mockmon::condition
{
    struct PredicateConditionId
    {
        const ConditionId conditionId;
        bool operator()(const pulser_uq_ptr & conditionPulse) const
        {
            return (conditionPulse->conditonId == conditionId);
        }
    };

    bool Condition::IsAffiliatedWithCondition(ConditionId conditionId) const
    {
        const PredicateConditionId pred{conditionId};
        return std::any_of(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),pred);
    }

    void Condition::CauseCondition(pulser_uq_ptr && pulser)
    {
       m_spesific_conditions.push_back(std::move(pulser));
    }

    void Condition::RemoveCondition(ConditionId conditionId)
    {
        //erase remove idiom
        const PredicateConditionId pred{conditionId};
        m_spesific_conditions.erase(
            std::remove_if(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),pred)
            , std::end(m_spesific_conditions));
    }

    void Condition::RemoveAllConditions()
    {
        //erase all
        m_spesific_conditions.clear();
    }

    void Condition::RemoveAllDueConditions()
    {
         m_spesific_conditions.erase(
        std::remove_if(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),[](const pulser_uq_ptr & pulser){return pulser->CanBeRemoved();})
        , std::end(m_spesific_conditions));
    }

    void Condition::PulseBeforeTurn() // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
    {
        std::for_each(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),[](pulser_uq_ptr & pulser){pulser->PulseBeforeTurn();});
        RemoveAllDueConditions();

    }

    void Condition::PulseAfterTurn() // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
    {
        std::for_each(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),[](pulser_uq_ptr & pulser){pulser->PulseAfterTurn();});
        RemoveAllDueConditions();
    }

}