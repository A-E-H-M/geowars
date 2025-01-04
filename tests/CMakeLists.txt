# Copyright (c) 2025 by Alexandria Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

# Create project
project ( geowars_test
	LANGUAGES CXX )

# Add executable
add_executable ( geowars_test geowars_test.cpp )
target_compile_features ( geowars_test PRIVATE cxx_std_20 )

# Add dependencies
include ( ../cmake/download_cpm.cmake )

CPMAddPackage ( "gh:catchorg/Catch2@3.6.0" )

# Link dependencies
target_link_libraries ( geowars_test PRIVATE geowars Catch2::Catch2WithMain )

enable_testing ()

add_test ( NAME run_geowars_test COMMAND geowars_test )
set_tests_properties ( run_geowars_test PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed" )
