#--------------------------------------------------------
# CMake for generating the GeneticLib
#
# @author: Wild Boar
#
# Date Created: 2023-06-02
#--------------------------------------------------------

# Setup includes directories
include_directories("../" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library (GeneticLib STATIC
	Tools/PathHelper.cpp
	Tools/ImageLoader.cpp
	ArgUtils.cpp
	Population.cpp
	FilterClassifier.cpp
)