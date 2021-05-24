#include <catch2/catch.hpp>
#include "../mockmon/include/mockmon_data.h"
#include <cmath>
#include <algorithm>

template<typename T,class UnaryPredicate>
bool VectorContains(const std::vector<T> & v,const UnaryPredicate & p)
{
    return std::any_of(std::begin(v),std::end(v),[&](const T & e){return p(e);});   
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
        const auto species = m.GetMockmonSpeciesData();
        REQUIRE(species.IsSameAs(speciesId));
        REQUIRE(species.IsSpeciesOfType(types::Types::Psychic));
        REQUIRE(!species.IsSpeciesOfType(types::Types::Fighting));
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
            REQUIRE(!species.IsSpeciesOfType(types::Types::Psychic));
        }
        WHEN("its level one")
        {
            THEN("it should know two moves")
            {
                const auto & mvs = m.ViewMoveSet();
                const auto pred1 =[](const moves::EquipedMove & eq){return eq.IsSameAs(moves::MoveId::PoisonSting);};
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,pred1));
                const auto pred2 =[](const moves::EquipedMove & eq){return eq.IsSameAs(moves::MoveId::StringShot);};
                REQUIRE(VectorContains(mvs,pred2));
            }
        }
        WHEN("we level it up")
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
            REQUIRE(!species.IsSpeciesOfType(types::Types::Fire));
        }
        WHEN("its level one")
        {
            THEN("it should know two moves")
            {
                const auto & mvs = m.ViewMoveSet();
                const auto pred1 =[](const moves::EquipedMove & eq){return eq.IsSameAs(moves::MoveId::Tackle);};
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,pred1));
                const auto pred2 =[](const moves::EquipedMove & eq){return eq.IsSameAs(moves::MoveId::TailWhip);};
                REQUIRE(VectorContains(mvs,pred2));
            }
        }
        WHEN("we level it up to level 7")
        {
            const auto levelUpGroup = m.GetMockmonSpeciesData().SpeciesLevelUpGroup;
            auto needexp = MockmonExp::TotalExperinceForLevel(7,levelUpGroup);
            m.GrantExperiencePoints(needexp);
            THEN("it should be a higher level")
            {
                REQUIRE( m.GetCurrentLevel()==7);
            }
            THEN("it should know more movs")
            {
                const auto & mvs = m.ViewMoveSet();
                const auto pred1 =[](const moves::EquipedMove & eq){return eq.IsSameAs(moves::MoveId::QuickAttack);};
                REQUIRE(VectorContains<moves::EquipedMove>(mvs,pred1));

            }
        }
    }
}