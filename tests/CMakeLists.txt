# first test
add_executable(test_matrix test_matrix.cpp)
target_link_libraries(test_matrix PRIVATE matrices GTest::gtest_main)

# second test
add_executable(test_array test_array.cpp)
target_link_libraries(test_array PRIVATE matrices GTest::gtest_main)

# third test
add_executable(test_huffman test_huffman.cpp)
target_link_libraries(test_huffman PRIVATE  huffman GTest::gtest_main)

# discover tests
include(GoogleTest)
gtest_discover_tests(test_matrix)
gtest_discover_tests(test_array)
gtest_discover_tests(test_huffman)
