#include "condition.h"

namespace mockmon::condition
{
        bool Condition::IsAffiliatedWithCondition(ConditionId conditionId) const
        {
            if (conditionId == ConditionId::Poison)
                return m_isPoisioned;
            return false;
        }
        void Condition::CauseCondition(ConditionId conditionId)
        {
            if (conditionId == ConditionId::Poison)
                m_isPoisioned = true;
            
        }
        void Condition::RemoveCondition(ConditionId conditionId)
        {
            if (conditionId == ConditionId::Poison)
                m_isPoisioned = false;
        }
}