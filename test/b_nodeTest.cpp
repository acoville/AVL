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

    TEST_CASE("Copy Assignment Operator equality test", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto node2 = node1;

        REQUIRE(node1 == node2);
    }

    //================================================================

    TEST_CASE("Copy Constructor equality test", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(25, comp)};
        auto node2(node1);

        REQUIRE(node2 == node1);
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

    TEST_CASE("Has Right Child TRUE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};

        root.SetRightChild(29);

        REQUIRE(root.HasRightChild());
    }

    //===================================================================

    TEST_CASE("Has Right Child FALSE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(25, comp)};

        REQUIRE(!root.HasRightChild());
    }

        //=========================================================================

    /*------------------------------

        BEFORE          AFTER

         10             10
        /   
      [7]

    ------------------------------*/

    TEST_CASE("Left Child Deletion Test, case 1: leaf", "[B node]")
    {
        auto root = b_node<int, std::less<int>>(10, comp);
        
        REQUIRE(!root.HasLeftChild());

        root.SetLeftChild(7);

        REQUIRE(root.HasLeftChild());

        root.DeleteLeftChild();

        REQUIRE(!root.HasLeftChild());
    }

    //=========================================================================

    /*-------------------------------

          BEFORE           AFTER

            10              10
              \             
              [15]         
          
    --------------------------------*/

    TEST_CASE("Right Child Deletion Test, case 1: leaf", "[B node]")
    {
        auto root = b_node<int, std::less<int>>(10, comp);
        
        REQUIRE(!root.HasRightChild());
        root.SetRightChild(15);
        REQUIRE(root.HasRightChild());

        root.DeleteRightChild();
        REQUIRE(!root.HasRightChild());
    }

    //=====================================================================

    /*----------------------------------

        BEFORE:         AFTER: 

           50             50
          /              /
       [40]             30
        /
      30

    ----------------------------------*/

    TEST_CASE("Delete Left Child case 2: 1 grandchild", "[B node]")
    {
        auto root = b_node<int, std::less<int>>(50, comp);
        root.SetLeftChild(40);
        root.LeftChild().SetLeftChild(30);

        REQUIRE(root.LeftChild().HasLeftChild());

        root.DeleteLeftChild();

        REQUIRE(root.HasLeftChild());
        REQUIRE(root.LeftChild().Data() == 30);
    }

    //=====================================================================

    /*----------------------------------

        BEFORE:         AFTER: 

           50             50
             \              \
             [70]            80
                \
                 80

    ----------------------------------*/

    TEST_CASE("Delete Right Child case 2: 1 grandchild", "[B node]")
    {
        auto root = b_node<int, std::less<int>>(50, comp);
        root.SetRightChild(70);
        root.RightChild().SetRightChild(80);

        REQUIRE(root.RightChild().HasRightChild());

        root.DeleteRightChild();

        REQUIRE(root.HasRightChild());
        REQUIRE(root.RightChild().Data() == 80);
    }

    //==========================================================================

    /*-------------------------------

        BEFORE:            AFTER:

            40               40
           /                /
         [35]              37
         /  \             /
        30   37          30   

    -------------------------------*/

    TEST_CASE("Delete Left Child case 3: 2 granchildren nodes", "[B node]")
    {
        auto root = b_node<int, std::less<int>>(40, comp);
        root.SetLeftChild(35);
        root.LeftChild().SetLeftChild(30);
        root.LeftChild().SetRightChild(37);

        //---------------------------------------

        root.DeleteLeftChild();

        REQUIRE(root.HasLeftChild());
        REQUIRE(root.LeftChild().Data() == 37);
        
        REQUIRE(root.LeftChild().HasLeftChild());
        REQUIRE(root.LeftChild().LeftChild().Data() == 30);
    }

    //============================================================================

    /*------------------------------------

        BEFORE:         AFTER:

          40              40
            \               \
           [50]             45
           /  \               \
         45    55             55

    -------------------------------------*/

    TEST_CASE("Delete Right Child case 3: 2 grandchildren nodes", "[B node]")
    {
        auto root = b_node<int, std::less<int>>(40, comp);
        root.SetRightChild(50);
        root.RightChild().SetLeftChild(45);
        root.RightChild().SetRightChild(55);

        //---------------------------------------------------

        root.DeleteRightChild();

        REQUIRE(root.RightChild().HasRightChild());
        REQUIRE(root.RightChild().RightChild().Data() == 55);
    }

    //=============================================================================

    /*---------------------------------

        Educational Test Only: 
            I would like to know if 
            adding children increases
            the reference count

    ----------------------------------*/

    
}