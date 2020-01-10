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