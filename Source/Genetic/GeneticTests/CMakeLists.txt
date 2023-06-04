#--------------------------------------------------------
# CMake for generating GeneticLib Testing Suite
#
# @author: Wild Boar
#
# Date Created: 2023-06-02
#--------------------------------------------------------

# Add Google Test to the test group
find_package(GTest REQUIRED)

# Setup the includes
include_directories("../")

# Add the UnitTestLib library to the folder
add_library(UnitTestLib STATIC IMPORTED)
set_target_properties(UnitTestLib PROPERTIES
    IMPORTED_LOCATION "${LIBRARY_BASE}/UnitTestLib/build/UnitTestLib/libUnitTestLib.a"
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRARY_BASE}/UnitTestLib"
)

# Create the executable
add_executable (GeneticTests
	Tests/Example_Tests.cpp
	Tests/Population_Tests.cpp
	Tests/ImageLoader_Tests.cpp
	Tests/FilterClassifier_Tests.cpp
)

# Add link libraries
target_link_libraries(GeneticTests GeneticLib NVLib ${OpenCV_LIBS} UnitTestLib OpenSSL::SSL uuid GTest::Main)

# Find the associated unit tests
gtest_discover_tests(GeneticTests)
