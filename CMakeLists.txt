cmake_minimum_required(VERSION 3.5)
project (AVL VERSION 2.0)

add_compile_options(-Wall -Wextra -g -std=c++1z)

cmake_policy (SET CMP0079 NEW)

enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/test")
add_subdirectory(test)

add_executable(unit_test.out
                test/testrunner.cpp
                test/b_nodeTest.cpp
                test/b_treeTest.cpp
                test/avl_treeTest.cpp)

#target_link_libraries(unit_test.out unit_tests)

#target_include_directories(unit_test.out PUBLIC "${PROJECT_BINARY_DIR}/test")