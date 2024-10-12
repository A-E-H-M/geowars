# Copyright (c) 2024 Alex Hernandez Mann
#
# Distributed under the Boost Software License, Version 1.0
# (See accompanying file LICENSE.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# Include font and config file
file(	COPY ../../font/Ohyou.ttf
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ )

file(	COPY ../../config/config.txt 
		DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/ )

# Add dependencies
include( ../../cmake/download_cpm.cmake )

#CPMAddPackage ( "gh:SFML/SFML@2.6.0")

# Add executable
#add_executable(	geowars_game geowars.cpp )
#target_compile_features( geowars_game PRIVATE cxx_std_20 )

# Link dependencies
#target_link_libraries( geowars_game PUBLIC geowars)

# End of file
