
enable_testing()

# first test
add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE matrices GTest::gtest_main)

# second test
#add_executable(test_core core_functions_tests.cpp ../src/core_functions.cpp)
#target_link_libraries(Tests PRIVATE GTest::gtest_main)
#target_include_directories(Tests PRIVATE ../src)

include(GoogleTest)
gtest_discover_tests(test_matrix)
