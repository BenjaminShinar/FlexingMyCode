#pragma once
#include "../identifiers/pulsing_conditions_id.h"
#include "../interfaces.h"
namespace mockmon::condition
{

    /**
     * @brief 
     * a functor that does something to the mockmon each turn, like take damage?
     * can we store the mockmon in the base class?
     * some conditions don't do anything when they're pulsed, they
     */
    class ConditonPulseEffect : public IdentifiybleModule<PulsingConditionId>
    {
    protected:
        explicit ConditonPulseEffect(PulsingConditionId condition) : IdentifiybleModule(condition)
        {
        }

        bool m_conditionFinished{false};

    public:
        virtual ~ConditonPulseEffect() = default;
        virtual void PulseAfterTurn(){};                                                  //virtual function
        virtual void PulseBeforeTurn(){};                                                 //virtual function
        [[nodiscard]] bool constexpr CanBeRemoved() const { return m_conditionFinished; } //stuff that removes itself after X turns?
    };

}