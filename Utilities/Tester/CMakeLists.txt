#--------------------------------------------------------
# Top-Level: Tester
#
# @author: Wild Boar
#
# @Date Created: 2023-06-08
#--------------------------------------------------------

cmake_minimum_required(VERSION 3.0.0)
project(Tester VERSION 0.1.0)

# Set the base path of the libraries
set(LIBRARY_BASE "/home/trevor/Libraries")

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Add OpenCV to the solution
find_package( OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Add the NVLib library to the folder
add_library(NVLib STATIC IMPORTED)
set_target_properties(NVLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/NVLib/build/NVLib/libNVLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/NVLib"
)

# Add OpenSSL to the solution
find_package(OpenSSL REQUIRED)

# Create the executable
add_executable(Tester
    Source.cpp
    Kernel.cpp
    PathHelper.cpp
    ImageLoader.cpp
)

# Add link libraries                               
target_link_libraries(Tester NVLib ${OpenCV_LIBS} OpenSSL::SSL uuid)

# Copy Resources across
add_custom_target(resource_copy ALL
	COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/Resources ${CMAKE_BINARY_DIR}
    DEPENDS ${MY_TARGET}
)