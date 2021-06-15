#pragma once

#include "mockmon_data.h"

#include <functional>

namespace mockmon
{
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
    /*
    class MockmonEvolution
    {
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
    };
    */
}