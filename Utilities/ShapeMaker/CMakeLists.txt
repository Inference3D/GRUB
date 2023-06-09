#--------------------------------------------------------
# Top-Level: ShapeMaker
#
# @author: Wild Boar
#
# @Date Created: 2023-06-02
#--------------------------------------------------------

cmake_minimum_required(VERSION 3.0.0)
project(ShapeMaker VERSION 0.1.0)

# Set the base path of the libraries
set(LIBRARY_BASE "/home/trevor/Libraries")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add opencv to the solution
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Create the executable
add_executable(ShapeMaker
    Source.cpp
)

# Add link libraries                               
target_link_libraries(ShapeMaker NVLib ${OpenCV_LIBS} )