# Copyright (c) 2024 Alex Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

project( geowars
		 VERSION 1.0.0
		 LANGUAGES CXX
		 DESCRIPTION "A single-player point and click, 2D game written in C++" )
# Tell CMake to a directory called 'bin' inside the build folder and put the executable there
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin )
option( BUILD_SHARED_LIBS "Build shared libraries" OFF )

include( FetchContent )
FetchContent_Declare(SFML
	GIT_REPOSITORY https://github.com/SFML/SFML.git
	GIT_TAG 2.6.x
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL_SYSTEM)
FetchContent_MakeAvailable(SFML)

# Add library targets
add_library(	geowars
				src/physics/vec2.cpp
				src/entities/entity.cpp
				src/entities/entity_manager.cpp
				src/game/game.cpp )
target_include_directories( geowars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/geowars/ )
target_compile_features( geowars PRIVATE cxx_std_20 )

# Build game
add_subdirectory( src/run_game )

# Add executable
add_executable( geowars_game src/run_game/geowars.cpp)
target_link_libraries( geowars_game PRIVATE geowars sfml-graphics sfml-window sfml-system )
target_compile_features( geowars_game PRIVATE cxx_std_20 )

# End of file
