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
using namespace ::mockmon;

auto RequireMoves(const mockmon::Mockmon &m, std::initializer_list<mockmon::moves::MoveId> ids)
{
    const auto &mvs = m.ViewMoveSet();
    for (auto id : ids)
    {
        REQUIRE(ContainerHas<moves::EquipedMove>(mvs, MakePredicator<moves::EquipedMove>(id)));
    }
}
//test_casse(name[,tags])
TEST_CASE("Base Mockmon Mew State", "[MockmonTest]")
{
    const auto speciesId = MockmonSpeciesId::Mew;
    Mockmon m(speciesId, "Jrose");
    SECTION("changing a mockmon name!")
    {
        m.ChangeName("Garry");
        REQUIRE(m.GetName() != "Jrose");
        REQUIRE(m.GetName() == "Garry");
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

        REQUIRE(m.GetCurrentLevel() == 1);
        MockmonTestUtils::BringMockmonToLevel(m, 2);
        REQUIRE(m.GetCurrentLevel() == 2);
        const auto needexp = MockmonExp::TotalExperinceForLevel(3, levelUpGroup) - m.CheckExperiencePoints().CurrentExperience;
        m.GrantExperiencePoints(needexp - 5);
        REQUIRE(m.GetCurrentLevel() == 2);
        m.GrantExperiencePoints(5);
        REQUIRE(m.GetCurrentLevel() == 3);
    }
}

//remove the [!mayfail] tag when we're ready to validate that we defined all mockmons
TEST_CASE("All mockmons exist", "[MockmonTest][Coverage][!throws][!mayfail]")
{
    const auto numberOfMockmons{151};
    SECTION("Verify 151 mockmons species are defined")
    {
        CHECK(mockmon::MockmonSpecies::AllMockmons.size() == numberOfMockmons);
    }
    //ths +0 is required for some weird reason concernning lambda captures
    const auto mockmonSpecicesId = GENERATE(map([](int i)
                                                { return MockmonSpeciesId(i); },
                                                range<int>(0, numberOfMockmons + 0)));

    DYNAMIC_SECTION("verify mockmon Id " << static_cast<int>(mockmonSpecicesId) << " has a name " << Stringify(mockmonSpecicesId) << " and can be constructed into a mockmon")
    {
        const auto mockmonSpeciesName{Stringify(mockmonSpecicesId)};
        REQUIRE_THAT(mockmonSpeciesName, !Catch::Matchers::Contains("Unknown"));

        const auto match = std::find_if(std::begin(mockmon::MockmonSpecies::AllMockmons), std::end(mockmon::MockmonSpecies::AllMockmons),
                                        [&](const std::pair<MockmonSpeciesId, MockmonSpecies> &p)
                                        { return p.first == mockmonSpecicesId; });

        if (match != std::end(mockmon::MockmonSpecies::AllMockmons))
        {
            Mockmon m(mockmonSpecicesId, mockmonSpeciesName);
            SUCCEED(mockmonSpeciesName + std::string(" successfuly constrcutred"));
        }
        else
        {
            FAIL(mockmonSpeciesName + std::string(" is not defined"));
        }
    }
}
SCENARIO("Base Mockmon Weedle State", "[MockmonTest][levelUpMoves]")
{
    const auto speciesId = MockmonSpeciesId::Weedle;
    GIVEN("A weedle mockmon")
    {
        Mockmon m(speciesId, "weedy");
        THEN("it should be bug/poison type")
        {
            const auto species = m.GetMockmonSpeciesData();
            REQUIRE(species.IsSameAs(speciesId));
            REQUIRE(species.IsSpeciesOfType(types::Types::Bug));
            REQUIRE(species.IsSpeciesOfType(types::Types::Poison));
            REQUIRE_FALSE(species.IsSpeciesOfType(types::Types::Psychic));
        }
        AND_WHEN("its level one")
        {
            THEN("it should know two moves")
            {
                RequireMoves(m, {moves::MoveId::PoisonSting, moves::MoveId::StringShot});
            }
        }
        AND_WHEN("we level it up")
        {
            MockmonTestUtils::BringMockmonToLevel(m, 2);
            THEN("it should be a higher level")
            {
                REQUIRE(m.GetCurrentLevel() == 2);
            }
        }
    }
}

SCENARIO("Base Mockmon Ratata State", "[MockmonTest][levelUpMoves]")
{
    const auto speciesId = MockmonSpeciesId::Rattata;
    GIVEN("A ratata mockmon")
    {
        Mockmon m(speciesId, "ratata");
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
                RequireMoves(m, {moves::MoveId::Tackle, moves::MoveId::TailWhip});
            }
        }
        AND_WHEN("we level it up to level 7")
        {
            MockmonTestUtils::BringMockmonToLevel(m, 7);
            THEN("it should be a higher level and know more moves")
            {
                REQUIRE(m.GetCurrentLevel() == 7);
                RequireMoves(m, {moves::MoveId::QuickAttack});
            }
        }
    }
}

SCENARIO("Mockmon Evolution", "[MockmonTest][Evolution]")
{
    using std::make_tuple;
    const auto [baseFormSpeciesId, requiredLevel, evolvedFormSpeciesId] = GENERATE(
        make_tuple(MockmonSpeciesId::Rattata, 20, MockmonSpeciesId::Raticate),
        make_tuple(MockmonSpeciesId::Geodude, 20, MockmonSpeciesId::Graveler));
    const auto baseformNames{Stringify(baseFormSpeciesId)};
    const auto evolevedFormName{Stringify(evolvedFormSpeciesId)};
    GIVEN("A mockmon of type" + baseformNames);
    {
        Mockmon m(baseFormSpeciesId, "");
        WHEN("we level it up to the level before the correct level and try to evolve it")
        {
            MockmonTestUtils::BringMockmonToLevel(m, requiredLevel - 1);
            const auto preevolvedStats = MockmonTestUtils::XorredStats(m);
            m.TryEvolve();
            THEN("it should be still be " + baseformNames)
            {
                const auto unEvolvedStats = MockmonTestUtils::XorredStats(m);
                const auto speciesIdentifier = m.GetMockmonSpeciesData().Identifier();

                REQUIRE(speciesIdentifier == baseFormSpeciesId);
                REQUIRE(preevolvedStats == unEvolvedStats);

                AND_WHEN("we level it up to the correct level and evolve it")
                {
                    MockmonTestUtils::BringMockmonToLevel(m, requiredLevel);
                    const auto preevolvedStats = MockmonTestUtils::XorredStats(m);
                    m.TryEvolve();
                    THEN("it should be a " + evolevedFormName)
                    {
                        const auto EvolvedStats = MockmonTestUtils::XorredStats(m);
                        const auto speciesIdentifier = m.GetMockmonSpeciesData().Identifier();

                        REQUIRE_FALSE(speciesIdentifier == baseFormSpeciesId);
                        REQUIRE(speciesIdentifier == evolvedFormSpeciesId);
                        REQUIRE_FALSE(preevolvedStats == EvolvedStats);
                    }
                }
            }
        }
    }
}