# Copied from CPM.cmake GitHub site
# Download CPM.cmake

file (
	DOWNLOAD
	https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.39.0/CPM.cmake
	${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
)

include (${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)
