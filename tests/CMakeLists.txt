# Copyright (c) 2025 by Alexandria Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

# Create project
project ( geowars_build_tests
	LANGUAGES CXX
	DESCRIPTION "Build test suite for geowars using Catch2 framework" )

# Add executable
add_executable ( geowars_tests
	components_geowars_test.cpp
	entity_geowars_test.cpp
	entity_manager_geowars_test.cpp
	entity_manager_test.cpp
	terrain_geowars_test.cpp
	vec2_geowars_test.cpp )
target_compile_features ( geowars_tests PRIVATE cxx_std_20 )

# Add dependencies
include ( ../cmake/download_cpm.cmake )

CPMAddPackage ( "gh:catchorg/Catch2@3.6.0" )

# Link dependencies
target_link_libraries ( geowars_tests PRIVATE geowars Catch2::Catch2WithMain )

enable_testing ()

add_test ( NAME run_geowars_tests COMMAND geowars_tests )
set_tests_properties ( run_geowars_tests PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed" )
