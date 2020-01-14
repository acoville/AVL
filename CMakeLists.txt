cmake_minimum_required(VERSION 3.5)
project (AVL LANGUAGES CXX VERSION 2.0)

add_compile_options(-Wall -Wextra -g -std=c++1z)

# CMake Policy 79 allows targets to scope source files outside
# this directory

cmake_policy (SET CMP0079 NEW)

find_package(Catch2 REQUIRED)

add_executable(avl_test
                test/testrunner.cpp
                test/b_nodeTest.cpp)
                #test/b_treeTest.cpp)
                #test/avl_treeTest.cpp)

target_link_libraries(avl_test Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(avl_test)