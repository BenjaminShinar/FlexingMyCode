#include <catch2/catch.hpp>

#include <cmath>


TEST_CASE( "std::abs is computed", "[SampleTest]" ) {
    REQUIRE( std::abs(-1) == 1 );
    REQUIRE( std::abs(1) == 1 );
    REQUIRE( std::abs(-2) == 2 );
    REQUIRE( std::abs(3) == 3 );
    REQUIRE( std::abs(-3) == 3 );
    REQUIRE( std::abs(10) == 10 );
    REQUIRE( std::abs(-10) == 10 );
}

// TEST_CASE( "failing test", "[SampleTest]" ) 
// {
//     REQUIRE( std::abs(-11) != 11 );
// }