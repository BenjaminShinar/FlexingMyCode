#include "evolution.h"
#include "mockmon_data.h"
#include <functional>
namespace mockmon::evolution
{
    using namespace std::placeholders; //import this for _1,_2,

    std::optional<MockmonSpeciesId> baseEvolutionFunction(const Mockmon &m, MockmonSpeciesId evolvedForm)
    {
        return {evolvedForm};
    }

    ev_fn CreateBaseEvoltuionFunction(MockmonSpeciesId evolvedForm)
    {
        auto bounded = std::bind(&baseEvolutionFunction, _1, evolvedForm);
        return bounded;
    }

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