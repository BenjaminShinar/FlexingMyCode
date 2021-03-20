#include "condition.h"

namespace mockmon
{
    void Condition::ChangeHealth(int amount )
    {
        m_HP += amount;
    }
}