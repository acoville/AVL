#include "include/catch.hpp"
#include "../b_node.hpp"

namespace AVL::test
{
    auto comp {std::less<int>()};

    TEST_CASE("B_Node Construction Test", "[B node]")
    {
        auto node {b_node<int, std::less<int>>(25, comp)};
    }

    //===========================================================

    TEST_CASE(" < operator (object of type T)", "[B node]")
    {
        auto node {b_node<int, std::less<int>>(25, comp)};

        REQUIRE(node < 40);
    }

    //----------------------------------

    TEST_CASE(" < operator (node)", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto node2 {b_node<int, std::less<int>>(15, comp)};

        REQUIRE(node1 > node2);
    }

    //===========================================================

    TEST_CASE(" > operator (object of type T)", "[B node]")
    {
        auto node {b_node<int, std::less<int>>(25, comp)};

        REQUIRE(node > 15);
    }

    //----------------------------------

    TEST_CASE(" > operator (node)", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto node2 {b_node<int, std::less<int>>(15, comp)};

        REQUIRE(node1 > node2);
    }

    //===========================================================

    TEST_CASE("Left Child bool operator", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        
        REQUIRE(!node1.HasLeftChild());

        node1.SetLeftChild(15);

        REQUIRE(node1.HasLeftChild());
    }

    //==============================================================

    TEST_CASE("Equality Operator TRUE Test (raw pointer) ", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto nodePtr {&node1};

        REQUIRE(node1 == *nodePtr);
    }

    //==============================================================

    TEST_CASE("Equality Operator TRUE Test (smart pointer)", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto nodePtr {std::make_shared<b_node<int, std::less<int>>>(node1)};

        REQUIRE(node1 == *nodePtr);
    }

    //================================================================

    TEST_CASE("Equality Operator FALSE test", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto node2 {b_node<int, std::less<int>>(15, comp)};

        bool equal {node1 == node2};

        REQUIRE(!equal);
    }

    //===================================================================

    TEST_CASE("Has Left Child TRUE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};

        root.SetLeftChild(15);

        REQUIRE(root.HasLeftChild());
    }

    //===================================================================

    TEST_CASE("Has Left Child FALSE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};

        REQUIRE(!root.HasLeftChild());
    }

    //===================================================================

    TEST_CASE("Has Parent TRUE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};
        root.SetLeftChild(15);
        auto left = root.LeftChild();

        REQUIRE(left.HasParent());
    }

    //===================================================================

    TEST_CASE("Has Parent FALSE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};
        REQUIRE(!root.HasParent());
    }

    //===================================================================

/*

    TEST_CASE("Set Child to a smart pointer Test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};

        root.SetLeftChild(15);


        auto left = root.LeftChild();


                
    }
*/

    //===================================================================


}