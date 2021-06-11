#include <catch2/catch.hpp>
#include "mockmon_test_utils.h"
#include <cmath>
#include <algorithm>

/**
 * @brief 
 * check that it has all moves
 * @param m 
 * @param ids 
 * @return auto 
 */
auto RequireMoves(const mockmon::Mockmon & m, std::initializer_list<mockmon::moves::MoveId> ids)
{    
    using namespace::mockmon;
    const auto & mvs = m.ViewMoveSet();
    for (auto id : ids)
    {
        REQUIRE(VectorContains<moves::EquipedMove>(mvs,MockmonTestUtils::MakePredicator<moves::EquipedMove>(id)));
    }
}
//test_casse(name[,tags])
TEST_CASE( "Base Mockmon Mew State", "[MockmonTest]" ) 
{
    using namespace::mockmon;
    const auto speciesId = MockmonSpeciesId::Mew;
    Mockmon m(speciesId,"Jrose");
    SECTION("changing a mockmon name!")
    {
        m.ChangeName("Garry");
        REQUIRE( m.GetName()!="Jrose");
        REQUIRE( m.GetName()=="Garry");
    }
    SECTION("verify mockmon species")
    {
        //todo: 
        // make this thing into a function somehow? give it types to check and deduce the rest from the types list
        const auto species = m.GetMockmonSpeciesData();
        REQUIRE(species.IsSameAs(speciesId));
        REQUIRE(species.IsSpeciesOfType(types::Types::Psychic));
        REQUIRE_FALSE(species.IsSpeciesOfType(types::Types::Fighting));
    }
    SECTION("verify mockmon levelup")
    {
        const auto levelUpGroup = m.GetMockmonSpeciesData().SpeciesLevelUpGroup;
        
        REQUIRE( m.GetCurrentLevel()==1);
        MockmonTestUtils::BringMockmonToLevel(m,2);
        REQUIRE( m.GetCurrentLevel()==2);
        const auto needexp = MockmonExp::TotalExperinceForLevel(3,levelUpGroup)-m.CheckExperiencePoints().CurrentExperience;
        m.GrantExperiencePoints(needexp-5);
        REQUIRE( m.GetCurrentLevel()==2);
        m.GrantExperiencePoints(5);
        REQUIRE( m.GetCurrentLevel()==3);
    }
}

SCENARIO( "Base Mockmon Weedle State", "[MockmonTest][levelUpMoves]" ) 
{
    using namespace::mockmon;
    const auto speciesId = MockmonSpeciesId::Weedle;
    GIVEN("A weedle mockmon")
    {
        Mockmon m(speciesId,"weedy");
        THEN("it should be bug/poison type")
        {
            const auto species = m.GetMockmonSpeciesData();
            REQUIRE(species.IsSameAs(speciesId));
            REQUIRE(species.IsSpeciesOfType(types::Types::Bug));
            REQUIRE(species.IsSpeciesOfType(types::Types::Poison));
            REQUIRE_FALSE(species.IsSpeciesOfType(types::Types::Psychic));
        }
        WHEN("its level one")
        {
            THEN("it should know two moves")
            {
                RequireMoves(m,{moves::MoveId::PoisonSting,moves::MoveId::StringShot});
            }
        }
        AND_WHEN("we level it up")
        {
            MockmonTestUtils::BringMockmonToLevel(m,2);
            THEN("it should be a higher level")
            {
                REQUIRE( m.GetCurrentLevel()==2);
            }
        }
    }
}

SCENARIO( "Base Mockmon Ratata State", "[MockmonTest][levelUpMoves]" ) 
{
    using namespace::mockmon;
    const auto speciesId = MockmonSpeciesId::Rattata;
    GIVEN("A ratata mockmon")
    {
        Mockmon m(speciesId,"ratata");
        THEN("it should be Normal type")
        {
            const auto species = m.GetMockmonSpeciesData();
            REQUIRE(species.IsSameAs(speciesId));
            REQUIRE(species.IsSpeciesOfType(types::Types::Normal));
            REQUIRE_FALSE(species.IsSpeciesOfType(types::Types::Fire));
        }
        AND_WHEN("its level one")
        {
            THEN("it should know two moves")
            {
                RequireMoves(m,{moves::MoveId::Tackle,moves::MoveId::TailWhip});
            }
        }
        AND_WHEN("we level it up to level 7")
        {
            MockmonTestUtils::BringMockmonToLevel(m,7);
            THEN("it should be a higher level and know more moves")
            {
                REQUIRE( m.GetCurrentLevel()==7);
                RequireMoves(m,{moves::MoveId::QuickAttack});
            }
        }
    }
}