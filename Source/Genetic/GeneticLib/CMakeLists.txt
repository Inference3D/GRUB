#--------------------------------------------------------
# CMake for generating the GeneticLib
#
# @author: Wild Boar
#
# Date Created: 2023-06-02
#--------------------------------------------------------

# Setup includes directories
include_directories("../" "../GeneticLib/" "${LIBRARY_BASE}/NVLib")

# Create Library
add_library (GeneticLib STATIC
	Tools/PathHelper.cpp
	Tools/ImageLoader.cpp
	Instance/ImageClassifier/LearnWrapper.cpp
	Instance/ImageClassifier/Kernel.cpp
	ArgUtils.cpp
	Population.cpp
)
	