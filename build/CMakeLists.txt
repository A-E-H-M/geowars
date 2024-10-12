# Copyright (c) 2024 Alex Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../run_game)

# Include font and config file
file(	COPY ../font/Ohyou.ttf
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

file(	COPY ../config/config.txt 
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

# Add dependencies
include( ../cmake/download_cpm.cmake )

CPMAddPackage("gh:SFML/SFML#2.6.1")

# Add executable
add_executable(	geowars_game ../src/main/geowars_main.cpp )
target_link_libraries( geowars_game PUBLIC geowars sfml-graphics sfml-window sfml-system )
target_compile_features( geowars_game PRIVATE cxx_std_20 )

# Link dependencies

# End of file
