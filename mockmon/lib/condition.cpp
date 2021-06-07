#include "condition.h"
#include <algorithm>
#include <functional>
namespace mockmon::condition
{
    struct PredicatePulsingConditionId
    {
        const PulsingConditionId conditionId;
        bool operator()(const pulser_uq_ptr & conditionPulse) const
        {
            return (conditionPulse->conditonId == conditionId);
        }
    };


/**
 * @brief 
 * think about how to remove this. or push it upward into interfaces...
 */
    struct PredicateNonPulsingConditionId
    {
        const NonPulsingConditionId nonePulsingConditionId;
        bool operator()(NonPulsingConditionId target) const
        {
            return (target == nonePulsingConditionId);
        }
    };

    bool Condition::IsAffiliatedWithCondition(PulsingConditionId conditionId) const
    {
        const PredicatePulsingConditionId pred{conditionId};
        return std::any_of(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),pred);
    }

    bool Condition::IsAffiliatedWithCondition(NonPulsingConditionId nonepulsingConditiondId) const
    {
        const PredicateNonPulsingConditionId pred{nonepulsingConditiondId};
        return std::any_of(std::begin(m_nonPulseCondtions),std::end(m_nonPulseCondtions),pred);
        return true;
    }

    double Condition::GetConditionalBoost(StatsTypes requestStat,bool attacking) const
    {
        double boost{1.0};
        switch (requestStat)
        {
        case StatsTypes::Attack:
        {
            if (attacking && IsAffiliatedWithCondition(condition::PulsingConditionId::Burn))
                boost *= 0.5; //inflict half damage when burned
            break;
        }
        case StatsTypes::Defence:
        {
            if (!attacking && IsAffiliatedWithCondition(condition::NonPulsingConditionId::Reflect))
                boost *= 2.0; //reflect dobules physical defence!
            break;
        }
        case StatsTypes::Special:
        {
            if (!attacking && IsAffiliatedWithCondition(condition::NonPulsingConditionId::LightScreen))
                boost *= 2.0; //light screens dobules special defence!
            break;
        }
        case StatsTypes::Speed:
        {
            if (IsAffiliatedWithCondition(condition::PulsingConditionId::Paralysis))
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
            // minimized is normal boosting.
            break;
        }
        case StatsTypes::CriticalHitChance:
        {
            if (IsAffiliatedWithCondition(condition::NonPulsingConditionId::FocusEnergy))
                boost *= 0.25; //chance critical hit chance. GEN I glitch
            break;
        }
        default:
            break;
        }
        return boost;
    }

    void Condition::CausePulsingCondition(pulser_uq_ptr && pulser)
    {
       m_spesific_conditions.push_back(std::move(pulser));
    }

    void Condition::CauseNonPulsingCondition(NonPulsingConditionId nonepulsingConditiondId)
    {
        m_nonPulseCondtions.emplace(nonepulsingConditiondId);
    }


    void Condition::RemovePulsingCondition(PulsingConditionId pulsingConditiondId)
    {
        //erase remove idiom
        const PredicatePulsingConditionId pred{pulsingConditiondId};
        m_spesific_conditions.erase(
            std::remove_if(std::begin(m_spesific_conditions),std::end(m_spesific_conditions),pred)
            , std::end(m_spesific_conditions));
    }

    void Condition::RemoveAllConditions()
    {
        //erase all
        m_spesific_conditions.clear();
        m_nonPulseCondtions.clear();
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

    /**
     * @brief Get the Charged Move object
     * if there is a stored move, take it's identifier.
     * @return std::optional<moves::MoveId> 
     */       
    std::optional<moves::MoveId> Condition::GetChargedMove()
    {
        if (m_chargedMoves.empty()) 
        {
            return {};
        }
        else
        {
            auto mv = m_chargedMoves.top();
            m_chargedMoves.pop();
            return mv;
        }
    }

    /**
     * @brief 
     * add the charged move to the stack of next usable moves.
     * @param mvId 
     */
    void Condition::StoreChargedMove(moves::MoveId mvId)
    {
        m_chargedMoves.push(mvId);
    }

}