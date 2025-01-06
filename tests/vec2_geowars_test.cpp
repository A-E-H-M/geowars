#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <vector>

#include "geowars/vec2.hpp"

TEST_CASE( "Initialize vec2", "[vec2]" ) {
	Vec2 vec2;
	REQUIRE( vec2.x == 0 );
	REQUIRE( vec2.y == 0 );
	
	Vec2 a_vec2( 3.0, 5.0 );
	REQUIRE( a_vec2.x == 3.0 );
	REQUIRE( a_vec2.y != 4.0 );

	Vec2 b_vec2( 10.0, 5.5 );

	SECTION( "Testing overloaded + operator" ) {
		auto c_vec2 = a_vec2 + b_vec2;
		REQUIRE( c_vec2.x == 13.0 );
		REQUIRE( c_vec2.y == 10.5 );

		auto d_vec2( a_vec2 + b_vec2 );
		REQUIRE( d_vec2.x == 13.0 );
		REQUIRE( d_vec2.y == 10.5 );

	SECTION( "Testing overloaded - operator" ) {
		//
	}
	}
}
