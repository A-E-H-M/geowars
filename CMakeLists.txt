# Copyright (c) 2025 Alexandria Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

project( geowars
	VERSION 1.0.0
	LANGUAGES CXX
	DESCRIPTION "A single-player point and click, 2D game written in C++" )

# Optional flags
option( BUILD_GAME "Build game executable" OFF)
option( GEOWARS_BUILD_TESTS "Build unit tests" OFF )

if ( CMAKE_BUILD_TYPE MATCHES "Debug" )
		if ( CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang" )
				set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fsanitize=undefined" )
				#target_link_libraries ( geowars PRIVATE asan ubsan )
		endif ()
endif ()

# Add dependencies
include( cmake/download_cpm.cmake )

CPMAddPackage( "gh:SFML/SFML#2.6.x" )

# Add library targets
add_library( geowars
	src/physics/vec2.cpp
	src/entities/entity_manager.cpp
	src/environment/terrain.cpp
	src/core/game.cpp )
target_include_directories( geowars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries( geowars PUBLIC sfml-graphics sfml-window sfml-system )

target_compile_features( geowars PRIVATE cxx_std_20 )
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang" )
	target_compile_options( geowars PRIVATE -Wall -Werror )
endif ()
if ( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( geowars PRIVATE /Wall /WL /W4 /wd"4100" )
endif ()

# Build game
if ( ${BUILD_GAME} )
	add_subdirectory ( build )
endif ()

# Check to build unit tests
if ( ${GEOWARS_BUILD_TESTS} )
		enable_testing ()
		add_subdirectory ( tests )
endif ()

# End of file
