#pragma once

#include "moves.h"
#include "types.h"
#include "stats.h"
#include "mockmon_exp.h"
#include "speciesId.h"
#include "interfaces.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>

//this is the base class of each mockmon, the shared data between them.
namespace mockmon
{

    class MockmonSpecies: public IdentifiybleModule<MockmonSpeciesId>
    {   
        public:
        explicit MockmonSpecies()=delete;
        explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,LevelUpGroup speciesLevelUpGroup,int speciesExp, const Stats && speciesStats, std::map<int,std::vector<moves::MoveId>> && levelUpMoves):
        IdentifiybleModule(speciesId),
        SpeciesType(type),
        SpeciesLevelUpGroup(speciesLevelUpGroup),
        SpeciesExp(speciesExp),
        SpeciesStats(speciesStats),
        LevelUpMoves(levelUpMoves)     
        {
        }
        virtual ~MockmonSpecies()=default; //we might want some inheritance for special mockmon cases, who knows 
        const types::Types SpeciesType;
        const LevelUpGroup SpeciesLevelUpGroup;
        const int SpeciesExp; // how much exp this mockmon gives
        const Stats SpeciesStats; // this belongs to the pokemon base class, not the indvidual;
        const std::map<int,std::vector<moves::MoveId>> LevelUpMoves;

        static const std::map<MockmonSpeciesId,MockmonSpecies> AllMockmons;
    };
}