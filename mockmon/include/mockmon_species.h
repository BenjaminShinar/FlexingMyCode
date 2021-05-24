#pragma once


#include "identifiers/mockmon_species_id.h"
#include "identifiers/level_up_groups_id.h"

#include "moves.h"
#include "types.h"
#include "stats/stats.h"
#include "mockmon_exp.h"

#include "interfaces.h"
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>

//this is the base class of each mockmon, the shared data between them.
namespace mockmon
{
    
    class MockmonSpecies: public IdentifiybleModule<MockmonSpeciesId>
    {   
        public:
        explicit MockmonSpecies()=delete;
        explicit MockmonSpecies(MockmonSpeciesId speciesId,const std::set<types::Types> & types,LevelUpGroup speciesLevelUpGroup,int speciesExp, const stats::SpeciesBaseStats & speciesStats,const std::map<int,std::vector<moves::MoveId>> & levelUpMoves):
        IdentifiybleModule(speciesId),
        SpeciesTypes(types),
        SpeciesLevelUpGroup(speciesLevelUpGroup),
        SpeciesExp(speciesExp),
        MockmonSpeciesStats(speciesStats),
        LevelUpMoves(levelUpMoves)     
        {
        }
        virtual ~MockmonSpecies()=default; //we might want some inheritance for special mockmon cases, who knows 

       #pragma region functions  
        
        bool IsSpeciesOfType(types::Types type) const;
        types::TypeEffectivenessModifier GetTypeEffetivenessModifier(types::Types attackingMoveType) const;
        
        #pragma endregion
        const std::set<types::Types> SpeciesTypes; //what types are the species (at least on, can be more)
        const LevelUpGroup SpeciesLevelUpGroup;
        const int SpeciesExp; // how much exp this mockmon gives
        const stats::SpeciesBaseStats MockmonSpeciesStats; // this belongs to the pokemon base class, not the indvidual;
        const std::map<int,std::vector<moves::MoveId>> LevelUpMoves; //which moves this species can learn naturally

        static const std::map<MockmonSpeciesId,MockmonSpecies> AllMockmons;
    };
}