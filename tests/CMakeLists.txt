# Copyright (c) 2025 by Alexandria Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

# Create project
project ( geowars_build_tests
	LANGUAGES CXX
	DESCRIPTION "Build test suite for geowars using Catch2 framework" )

# Add dependencies
include ( ../cmake/download_cpm.cmake )

CPMAddPackage ( "gh:catchorg/Catch2@3.6.0" )

# Test file names
set ( test_geowars_names
	#config_geowars_test
	#components_geowars_test
	#entity_geowars_test
	#entity_manager_geowars_test
	#entity_manager_test
	#terrain_geowars_test
	vec2_geowars_test )

# Add individual executables
foreach ( test_geowars_name IN LISTS test_geowars_names )
	message ( "Creating test executable: ${test_geowars_name}" )
	add_executable ( ${test_geowars_name} ${test_geowars_name}.cpp )
	target_compile_features ( ${test_geowars_name} PRIVATE cxx_std_20 )
	target_link_libraries ( ${test_geowars_name} PRIVATE geowars Catch2::Catch2WithMain )
endforeach()

enable_testing ()

foreach ( test_geowars_name IN LISTS test_geowars_names )
	message ( "Creating test: run_${test_geowars_name}" )
	add_test ( NAME run_${test_geowars_name} COMMAND ${test_geowars_name} )
	if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang" )
		set_tests_properties ( run_${test_geowars_name} PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed" )
	endif ()
	if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
		# Environment modification required IN LISTS test properities for ctest to run tests, otherwise it can not find the tests
		set_tests_properties ( run_${test_geowars_name} PROPERTIES PASS_REGULAR_EXPRESSION "All tests passed" ENVIRONMENT_MODIFICATION PATH=path_list_append:$<TARGET_RUNTIME_DLL_DIRS:${test_geowars_name}>)
	endif ()
endforeach()
