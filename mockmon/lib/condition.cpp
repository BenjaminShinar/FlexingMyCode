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

    double Condition::GetConditionalBoost(StatsTypes requestStat,bool attacking) const
    {
        double boost{1.0};
        switch (requestStat)
        {
        case StatsTypes::Attack:
        {
            if (attacking && IsAffiliatedWithCondition(condition::ConditionId::Burn))
                boost *= 0.5; //inflict half damage when burned
            break;
        }
        case StatsTypes::Defence:
        {
            if (!attacking && IsAffiliatedWithCondition(condition::ConditionId::Reflect))
                boost *= 2.0; //reflect dobules physical defence!
            break;
        }
        case StatsTypes::Special:
        {
            if (!attacking && IsAffiliatedWithCondition(condition::ConditionId::LightScreen))
                boost *= 2.0; //light screens dobules special defence!
            break;
        }
        case StatsTypes::Speed:
        {
            if (IsAffiliatedWithCondition(condition::ConditionId::Paralysis))
                boost *= 0.25; //quarter speed when parayzed
            break;
        }
        case StatsTypes::Accuracy:
        {
            //any conditions effecting accuracy?
            break;
        }
        case StatsTypes::Evasion:
        {
            //any conditions effecting evasion?
            break;
        }
        default:
            break;
        }
        return boost;
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
             std::remove_if(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),std::mem_fn(ConditonPulseEffect::CanBeRemoved))
        , std::end(m_spesific_conditions));
    }

    void Condition::PulseBeforeTurn() // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
    {
        std::for_each(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),std::mem_fn(ConditonPulseEffect::PulseBeforeTurn));
        RemoveAllDueConditions();

    }

    void Condition::PulseAfterTurn() // cause all the effects of the afflicated conditions, remove conditions that aren't relevent anymore.
    {
        std::for_each(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),std::mem_fn(ConditonPulseEffect::PulseAfterTurn));
        RemoveAllDueConditions();
    }

}