#--------------------------------------------------------
# Top-Level: LetterMaker
#
# @author: Wild Boar
#
# @Date Created: 2023-06-07
#--------------------------------------------------------

cmake_minimum_required(VERSION 3.0.0)
project(LetterMaker VERSION 0.1.0)

# Set the base path of the libraries
set(LIBRARY_BASE "/home/trevor/Libraries")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add OpenCV to the solution
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add OpenSSL to the solution
find_package(OpenSSL REQUIRED)


# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Create the executable
add_executable(LetterMaker
    Source.cpp
    PathHelper.cpp
)

# Add link libraries                               
target_link_libraries(LetterMaker NVLib ${OpenCV_LIBS} OpenSSL::SSL uuid )

# Copy Resources across
add_custom_target(resource_copy ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}
    DEPENDS ${MY_TARGET}
)