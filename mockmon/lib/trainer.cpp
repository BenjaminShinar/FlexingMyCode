#include "interfaces.h"
#include "trainer.h"

namespace mockmon
{
    /**
     * @brief 
     * this should eventually be a unique_id something
     */
    std::size_t Trainer::LastTrainerId = 100;

    void Trainer::GiveBadge(badges::IndigoBadge badge)
    {
        m_Indigo_Badges.set(static_cast<std::size_t>(badge));
    }

    bool Trainer::CheckBadge(badges::IndigoBadge badge) const
    {
        return m_Indigo_Badges.test(static_cast<std::size_t>(badge));
    }
}