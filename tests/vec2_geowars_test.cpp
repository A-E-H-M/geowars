//#include <catch2/generators/catch_generators.hpp>
//#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "geowars/vec2.hpp"

TEMPLATE_TEST_CASE("Vec2 operations", "[vec2]", 
    int, long, short,                     // Integer types
    float, double, long double,           // Floating point types
    unsigned int, unsigned long           // Unsigned types
) {
    Vec2<TestType> v1(static_cast<TestType>(2), static_cast<TestType>(3));
    Vec2<TestType> v2(static_cast<TestType>(3), static_cast<TestType>(4));
    
    SECTION("Basic operations") {
        // Test addition
        auto sum = v1 + v2;
        REQUIRE(sum.x == static_cast<TestType>(5));
        REQUIRE(sum.y == static_cast<TestType>(7));

        // Test subtraction
        auto diff = v2 - v1;
        REQUIRE(diff.x == static_cast<TestType>(1));
        REQUIRE(diff.y == static_cast<TestType>(1));

        // Test scalar multiplication
        auto mult = v1 * 2.0f;
        if constexpr (std::is_floating_point_v<TestType>) {
            REQUIRE(mult.x == Catch::Approx(static_cast<TestType>(4)));
            REQUIRE(mult.y == Catch::Approx(static_cast<TestType>(6)));
        } else {
            REQUIRE(mult.x == static_cast<TestType>(4));
            REQUIRE(mult.y == static_cast<TestType>(6));
        }

        // Test scalar division
        auto div = v2 / 2.0f;
        if constexpr (std::is_floating_point_v<TestType>) {
            REQUIRE(div.x == Catch::Approx(static_cast<TestType>(1.5)));
            REQUIRE(div.y == Catch::Approx(static_cast<TestType>(2)));
        } else {
            REQUIRE(div.x == static_cast<TestType>(1));
            REQUIRE(div.y == static_cast<TestType>(2));
        }

        // Test compound operators
        auto v3 = v1;
        v3 += v2;
        REQUIRE(v3.x == static_cast<TestType>(5));
        REQUIRE(v3.y == static_cast<TestType>(7));

        v3 = v1;
        v3 -= v2;
        REQUIRE(v3.x == static_cast<TestType>(-1));
        REQUIRE(v3.y == static_cast<TestType>(-1));

        v3 = v1;
        v3 *= 2.0f;
        if constexpr (std::is_floating_point_v<TestType>) {
            REQUIRE(v3.x == Catch::Approx(static_cast<TestType>(4)));
            REQUIRE(v3.y == Catch::Approx(static_cast<TestType>(6)));
        } else {
            REQUIRE(v3.x == static_cast<TestType>(4));
            REQUIRE(v3.y == static_cast<TestType>(6));
        }

        v3 = v2;
        v3 /= 2.0f;
        if constexpr (std::is_floating_point_v<TestType>) {
            REQUIRE(v3.x == Catch::Approx(static_cast<TestType>(1.5)));
            REQUIRE(v3.y == Catch::Approx(static_cast<TestType>(2)));
        } else {
            REQUIRE(v3.x == static_cast<TestType>(1));
            REQUIRE(v3.y == static_cast<TestType>(2));
        }

        // Test comparison operators
        Vec2<TestType> v4(static_cast<TestType>(2), static_cast<TestType>(3));
        REQUIRE(v1 == v4);
        REQUIRE(v1 != v2);
    }
}


/*
TEST_CASE( "Vec2 template instantiation", "[vec2]" ) {
	template <typename T>
	void Vec2_Test(Vec2<T> test_a, Vec2<T> test_b) {
		
		Vec2<T> test_c = test_a + test_b;
		CHECK( test_c.x == 3 );
		CHECK( test_c.y == 18 );
		
		test_c = test_b - test_a;
		CHECK( test_c.x == -1 );
		CHECK( test_c.y == 2 );

		test_c = test_a / test_b;
		CHECK( test_c.x == 2 );
		CHECK( test_c.y == 0 );

		test_c = test_a * b;
		CHECK( test_c.x == 2 );
		CHECK( test_c.y == 80 );
		
		CHECK( test_a.x == test_d.x );
		CHECK( test_a.y == test_d.y );
		
		CHECK( test_a.x != test_b.x );
		CHECK( test_a.y != test_b.y );

		test_c += test_b;
		CHECK( test_c.x == 1 );
		CHECK( test_c.y == 8 );

		test_a -= test_b;
		CHECK( test_a.x == 1 );
		CHECK( test_a.y == -2 );

		test_b *= test_a;
		CHECK( test_b.x == 2 );
		CHECK( test_b.y == 80 );



	};

	SECTION( "Vec2" ) {

	}
*/
	/*
	Vec2<int> test_a( 2, 8 );
	Vec2<int> test_b( 1, 10 );
	Vec2<int> test_c( 0, 0 );
	Vec2<int> test_d( 2, 8 );

	Vec2<double> test_e( 3.5, 11.5 );
	Vec2<double> test_f( 7.5, 11.5 );
	Vec2<double> test_g( 10.0, 2.0 );

	Vec2<float> test_e( 3.5, 11.5 );
	Vec2<float> test_f( 7.5, 11.5 );
	Vec2<float> test_g( 10.0, 2.0 );

		
	SECTION( "Vec2 int type", "[vec2<int>]") {
		test_c = test_a + test_b;
		CHECK( test_c.x == 3 );
		CHECK( test_c.y == 18 );
		
		test_c = test_b - test_a;
		CHECK( test_c.x == -1 );
		CHECK( test_c.y == 2 );

		test_c = test_a / test_b;
		CHECK( test_c.x == 2 );
		CHECK( test_c.y == 0 );

		test_c = test_a * b;
		CHECK( test_c.x == 2 );
		CHECK( test_c.y == 80 );
		
		CHECK( test_a.x == test_d.x );
		CHECK( test_a.y == test_d.y );
		
		CHECK( test_a.x != test_b.x );
		CHECK( test_a.y != test_b.y );

		test_c += test_b;
		CHECK( test_c.x == 1 );
		CHECK( test_c.y == 8 );

		test_a -= test_b;
		CHECK( test_a.x == 1 );
		CHECK( test_a.y == -2 );

		test_b *= test_a;
		CHECK( test_b.x == 2 );
		CHECK( test_b.y == 80 );

		test_a /= test_b;
		CHECK( test_b.x == 2 );
		CHECK( test_b.y == 0 );
	}

	SECTION( "Vec2 double type", "[vec2<double>]") {
		test_c = test_a + test_b;
		CHECK( test_c.x == 3 );
		CHECK( test_c.y == 18 );
		
		test_c = test_b - test_a;
		CHECK( test_c.x == -1 );
		CHECK( test_c.y == 2 );

		test_c = test_a / test_b;
		CHECK( test_c.x == 2 );
		CHECK( test_c.y == 0 );

		test_c = test_a * b;
		CHECK( test_c.x == 2 );
		CHECK( test_c.y == 80 );
///
		CHECK( test_a.x == test_d.x );
		CHECK( test_a.y == test_d.y );
		
		CHECK( test_a.x != test_b.x );
		CHECK( test_a.y != test_b.y );

		test_c += test_b;
		CHECK( test_c.x == 1 );
		CHECK( test_c.y == 8 );

		test_a -= test_b;
		CHECK( test_a.x == 1 );
		CHECK( test_a.y == -2 );

		test_b *= test_a;
		CHECK( test_b.x == 2 );
		CHECK( test_b.y == 80 );

		test_a /= test_b;
		CHECK( test_b.x == 2 );
		CHECK( test_b.y == 0 );
	}
	*/
	
	/*	Vec2 vec2;
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

	}

	SECTION( "Testing overloaded - operator" ) {
		//
	}
*/
}
