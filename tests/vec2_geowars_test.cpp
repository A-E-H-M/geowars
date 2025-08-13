//#include <catch2/generators/catch_generators.hpp>
//#include <vector>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "geowars/vec2.hpp"

using namespace GWars;

TEMPLATE_TEST_CASE( "Vec2 operations", "[vec2]", 
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