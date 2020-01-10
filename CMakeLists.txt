cmake_minimum_required(VERSION 3.5)
project (AVL LANGUAGES CXX VERSION 2.0)

add_compile_options(-Wall -Wextra -g -std=c++1z)

cmake_policy (SET CMP0079 NEW)

find_package(Catch2 REQUIRED)
#enable_testing()

add_executable(unit_test.out
                test/testrunner.cpp
                test/b_nodeTest.cpp
                test/b_treeTest.cpp
                test/avl_treeTest.cpp)

target_link_libraries(unit_test.out Catch2::Catch2)

include(CTest)
include(Catch)
catch_discover_tests(unit_test.out)