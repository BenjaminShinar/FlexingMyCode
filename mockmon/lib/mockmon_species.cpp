#include "mockmon_species.h"
#include <cmath>
#include <algorithm>

namespace mockmon
{
    std::string speciesToStr(const MockmonSpeciesId speceis)
    {
        switch (speceis)
        {
        case MockmonSpeciesId::Mew : return "Mew";break;
        case MockmonSpeciesId::Ratata : return "Ratata";break;
        default: return "Unknown mockmon!"; break;
        }
    }

    std::ostream& operator<<(std::ostream& os,const MockmonSpeciesId& speceis)
    {
        os << speciesToStr(speceis);
        return os;
    }

    const std::map<MockmonSpeciesId,MockmonSpecies> MockmonSpecies::AllMockmons
    {
        //explicit MockmonSpecies(MockmonSpeciesId speciesId,types::Types type,long speciesExp,Stats & sepeciesStats,const std::map<int,moves::MoveId> & levelUpMovesList);
        {MockmonSpeciesId::Mew, MockmonSpecies(MockmonSpeciesId::Mew,types::Types::Normal,64,LevelUpGroup::MediumSlowLevelUp,{100,100,100,100,100},{{1,{moves::MoveId::WaterGun,moves::MoveId::Guillotine}}})},
        {MockmonSpeciesId::Ratata, MockmonSpecies(MockmonSpeciesId::Ratata,types::Types::Normal,57,LevelUpGroup::MediumFastLevelUp,{30,56,35,25,72},{{5,{moves::MoveId::Tackle}}})},

        //{MockmonSpeciesId::Ratata, MockmonSpecies()},
        //{MockmonSpeciesId::Ratata, MockmonSpecies(MockmonSpeciesId::Ratata,types::Types::Water,100,40,25,40)},
    };

}