#pragma once

#include "mockmon_species.h"
#include "mockmon_data.h"
#include <optional>
#include <functional>

namespace mockmon::evolution
{

    ev_fn CreateEvolveByLevelFunction(MockmonSpeciesId evolvedForm, unsigned int requriedLevel);

    enum class MockmonEvolutionType
    {
        NoEvolutions,
        Level,
        // UsedItem,
        // HeldItemLevelUp,
        // Trade,
        // Friendship
    };

    //this belongs to the mockmon species data,
    // mockmon of type[s?] A can evolve to types B,C,D
    // can this mockmon species evolve at all?
    // can this individual mockmon evolve at the moment? to which mockmons?
    // perform evolution - consume whatever, the evolving mockmon must replace it's base type with the evolved type.
    // a function that says which evolutions are possible
    // returning a set of options?
    //

    // maybe this should hold a weak refernce to the mockmon?
    // what if someone saved this to a varible and things changed?
    //
    class MockmonEvolution
    {
        using ApplyEvolution = std::function<void(Mockmon &mockmon)>;

    public:
        bool CanEvolve(Mockmon &mockmon) const;
        std::pair<MockmonSpeciesId, MockmonSpeciesId> EvolutionPair;

    private:
        /*
        using ApplyEvolution = std::function<void(Mockmon & mockmon)>;
        using CheckEvolution = std::function<MockmonSpeciesId(const Mockmon & mockmon)>;
        public:
        explicit MockmonEvolution(MockmonSpeciesId speciesId, bool evolutionPossible = false)
        :CurrentSpeciesId(speciesId),SpeciesCanEvolve(evolutionPossible)
        {}

        explicit MockmonEvolution(MockmonSpeciesId speciesId, bool evolutionPossible,CheckEvolution & f1,ApplyEvolution & f2)
        :CurrentSpeciesId(speciesId),SpeciesCanEvolve(evolutionPossible),MockmonCanEvolve(f1),PerformEvolution(f2)
        {}
        const MockmonSpeciesId CurrentSpeciesId;
        const bool SpeciesCanEvolve;
        
        bool CanMockmonEvolve(const Mockmon & mockmon) const;

        const CheckEvolution MockmonCanEvolve = 
        [](const auto & m){return MockmonSpeciesId::UknownSpecies;};
        const ApplyEvolution PerformEvolution = [](auto & m){};
        */
    };
}