# Copyright (c) 2025 Alex Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

project(	geowars
	VERSION 1.0.0
	LANGUAGES CXX
	DESCRIPTION "A single-player point and click, 2D game written in C++" )

# Optional flags
#option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
option( GEOWARS_BUILD_TESTS "Build unit tests" OFF )

# Add dependencies
include( cmake/download_cpm.cmake )

CPMAddPackage( "gh:SFML/SFML#2.6.x" )

# Add library targets
add_library(	geowars
	src/physics/vec2.cpp
	src/entities/entity.cpp
	src/entities/entity_manager.cpp
	src/environment/terrain.cpp
	src/core/game.cpp	)
target_include_directories( geowars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_link_libraries( geowars PUBLIC sfml-graphics sfml-window sfml-system )
target_compile_features( geowars PRIVATE cxx_std_20 )

# Include font and config file
file(	COPY font/Ohyou.ttf
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

file(	COPY config/config.txt 
	DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

# Add executable
add_executable(	geowars_game src/main/geowars_main.cpp )
target_link_libraries( geowars_game PRIVATE geowars )
target_compile_features( geowars_game PRIVATE cxx_std_20 )

# Build game
#add_subdirectory( build )

# Check to build unit tests
if ( ${GEOWARS_BUILD_TESTS} )
		enable_testing ()
		add_subdirectory ( tests )
endif ()

# End of file
