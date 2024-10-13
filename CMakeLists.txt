# Copyright (c) 2024 Alex Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required ( VERSION 3.14 FATAL_ERROR )

project( geowars
		 VERSION 1.0.0
		 LANGUAGES CXX
		 DESCRIPTION "A single-player point and click, 2D game written in C++" )

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# Add library targets
add_library(	geowars
				src/physics/vec2.cpp
				src/entities/entity.cpp
				src/entities/entity_manager.cpp
				src/core/game.cpp	)
target_include_directories( geowars PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/geowars )
target_compile_features( geowars PRIVATE cxx_std_20 )

# Build game
add_subdirectory( build )

# End of file
