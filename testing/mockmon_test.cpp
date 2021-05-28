#include <catch2/catch.hpp>
#include "../mockmon/include/mockmon_data.h"
#include <cmath>
#include <algorithm>

template<typename V,typename T>
auto MakePredicator(T t)
{
    return ([t](const V & el){return el.IsSameAs(t);});
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
        auto needexp = MockmonExp::TotalExperinceForLevel(2,levelUpGroup);
        m.GrantExperiencePoints(needexp);
        REQUIRE( m.GetCurrentLevel()==2);
        needexp = MockmonExp::TotalExperinceForLevel(3,levelUpGroup)-m.CheckExperiencePoints().CurrentExperience;
        m.GrantExperiencePoints(needexp-5);
        REQUIRE( m.GetCurrentLevel()==2);
        m.GrantExperiencePoints(5);
        REQUIRE( m.GetCurrentLevel()==3);
    }
}

SCENARIO( "Base Mockmon Weedle State", "[MockmonTest]" ) 
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
                const auto & mvs = m.ViewMoveSet();
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,MakePredicator<moves::EquipedMove>(moves::MoveId::PoisonSting)));
                REQUIRE(VectorContains(mvs,MakePredicator<moves::EquipedMove>(moves::MoveId::StringShot)));
            }
        }
        AND_WHEN("we level it up")
        {
            const auto levelUpGroup = m.GetMockmonSpeciesData().SpeciesLevelUpGroup;
            auto needexp = MockmonExp::TotalExperinceForLevel(2,levelUpGroup);
            m.GrantExperiencePoints(needexp);
            THEN("it should be a higher level")
            {
                REQUIRE( m.GetCurrentLevel()==2);
            }
        }
    }
}

SCENARIO( "Base Mockmon Ratata State", "[MockmonTest]" ) 
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
                const auto & mvs = m.ViewMoveSet();
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,MakePredicator<moves::EquipedMove>(moves::MoveId::Tackle)));
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,MakePredicator<moves::EquipedMove>(moves::MoveId::TailWhip)));
            }
        }
        AND_WHEN("we level it up to level 7")
        {
            const auto levelUpGroup = m.GetMockmonSpeciesData().SpeciesLevelUpGroup;
            auto needexp = MockmonExp::TotalExperinceForLevel(7,levelUpGroup);
            m.GrantExperiencePoints(needexp);
            THEN("it should be a higher level and know more moves")
            {
                REQUIRE( m.GetCurrentLevel()==7);
                const auto & mvs = m.ViewMoveSet();
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,MakePredicator<moves::EquipedMove>(moves::MoveId::QuickAttack)));
            }
        }
    }
}