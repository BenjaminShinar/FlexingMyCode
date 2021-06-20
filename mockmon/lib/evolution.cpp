#include "evolution.h"
#include "mockmon_data.h"
#include <functional>
namespace mockmon::evolution
{
    using namespace std::placeholders; //import this for _1,_2,
    ev_fn CreateEvolveByLevelFunction(MockmonSpeciesId evolvedForm, unsigned int requriedLevel)
    {
        ev_fn evolveByLevelFunction = [=](const Mockmon &m) -> std::optional<MockmonSpeciesId>
        {
            if (m.GetCurrentLevel() >= requriedLevel)
            {
                return evolvedForm;
            }
            return {};
        };
        return evolveByLevelFunction;
    }

    ev_fn CreateEvolveByTradedFunction(MockmonSpeciesId evolvedForm)
    {
        ev_fn evolveByTradedFunction = [=](const Mockmon &m) -> std::optional<MockmonSpeciesId>
        {
            if (m.ViewAllPastTrainers().size() > 1)
            {
                return evolvedForm;
            }
            return {};
        };
        return evolveByTradedFunction;
    }
    // bool MockmonEvolution::CanMockmonEvolve(const Mockmon & mockmon) const
    // {
    //     if (SpeciesCanEvolve)
    //     {
    //         auto ev = MockmonCanEvolve(mockmon);

    //         return ev != MockmonSpeciesId::UknownSpecies;
    //     }
    //     return false;
    // }
}