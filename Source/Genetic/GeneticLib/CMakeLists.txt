#--------------------------------------------------------
# CMake for generating the GeneticLib
#
# @author: Wild Boar
#
# Date Created: 2023-06-02
#--------------------------------------------------------

# Setup include directories
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library(GeneticLib STATIC
    ArgUtils.cpp
)
