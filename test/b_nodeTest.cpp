#include "include/catch.hpp"
#include "../b_node.hpp"

namespace AVL::test
{
    auto comp = std::less<int>();

    TEST_CASE("B_Node Construction Test", "[B node]")
    {
        auto node = b_node<int, std::less<int>>(25, comp);
    }

    //===========================================================

    TEST_CASE(" < operator (object of type T)", "[B node]")
    {
        auto node = b_node<int, std::less<int>>(25, comp);

        REQUIRE(node < 40);
    }

    //----------------------------------

    TEST_CASE(" < operator (node)", "[B node]")
    {
        auto node1 = b_node<int, std::less<int>>(25, comp);
        auto node2 = b_node<int, std::less<int>>(15, comp);

        REQUIRE(node1 > node2);
    }

    //===========================================================

    TEST_CASE(" > operator (object of type T)", "[B node]")
    {
        auto node = b_node<int, std::less<int>>(25, comp);

        REQUIRE(node > 15);
    }

    //----------------------------------

    TEST_CASE(" > operator (node)", "[B node]")
    {
        auto node1 = b_node<int, std::less<int>>(25, comp);
        auto node2 = b_node<int, std::less<int>>(15, comp);

        REQUIRE(node1 > node2);
    }

}