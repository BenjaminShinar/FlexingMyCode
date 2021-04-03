#pragma once

#include "moves.h"
#include "types.h"
#include "stats.h"
#include "mockmon_exp.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>



//this is the base class of each mockmon, the shared data between them.
namespace mockmon
{
    enum class MockmonSpeciesId
    {      
        Ratata,
        Mew,
        UknownSpecies
    };

    std::ostream& operator<<(std::ostream& os,const MockmonSpeciesId& mockmonSpeciesId);

    class MockmonSpecies
    {   
        public:

        explicit MockmonSpecies()=delete;
        explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,int speciesExp,LevelUpGroup speciesLevelUpGroup ,const Stats && speciesStats, std::map<int,std::vector<moves::MoveId>> && levelUpMoves):
        SpeciesId(speciesId),
        SpeciesType(type),
        SpeciesExp(speciesExp),
        SpeciesLevelUpGroup(speciesLevelUpGroup),
        SpeciesStats(speciesStats),
        LevelUpMoves(levelUpMoves)     
        {
        }
        virtual ~MockmonSpecies()=default; //we might want some inheritance for special mockmon cases, who knows 
        
        const MockmonSpeciesId SpeciesId;
        const types::Types SpeciesType;
        const Stats SpeciesStats; // this belongs to the pokemon base class, not the indvidual;
        const int SpeciesExp; // how much exp this mockmon gives
        const std::map<int,std::vector<moves::MoveId>> LevelUpMoves;
        const LevelUpGroup SpeciesLevelUpGroup;
        static const std::map<MockmonSpeciesId,MockmonSpecies> AllMockmons;

    };
}