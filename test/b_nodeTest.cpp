#include "include/catch.hpp"
#include "../b_node.hpp"

namespace AVL::test
{
    auto comp {std::less<int>()};
    int five {5};
    int seven {7};

    TEST_CASE("B_Node Construction Test", "[B node]")
    {
        auto node {b_node<int, std::less<int>>(five, comp)};
    }

    //===========================================================

    TEST_CASE(" < operator (object of type T)", "[B node]")
    {
        auto node {b_node<int, std::less<int>>(five, comp)};

        REQUIRE(node < 40);
    }

    //----------------------------------

    TEST_CASE(" < operator (node)", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(seven, comp)};
        auto node2 {b_node<int, std::less<int>>(five, comp)};

        REQUIRE(node1 > node2);
    }

    //===========================================================

    TEST_CASE(" > operator (object of type T)", "[B node]")
    {
        auto node {b_node<int, std::less<int>>(seven, comp)};

        REQUIRE(node > 5);
    }

    //----------------------------------

    TEST_CASE(" > operator (node)", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(seven, comp)};
        auto node2 {b_node<int, std::less<int>>(five, comp)};

        REQUIRE(node1 > node2);
    }

    //==============================================================

    TEST_CASE("Equality Operator TRUE Test (raw pointer) ", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(five, comp)};
        auto nodePtr {&node1};

        REQUIRE(node1 == *nodePtr);
    }

    //================================================================

    TEST_CASE("Copy Assignment Operator equality test", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(five, comp)};
        auto node2 = node1;

        REQUIRE(node1 == node2);
    }

    //================================================================

    TEST_CASE("Copy Constructor equality test", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(five, comp)};
        auto node2(node1);

        REQUIRE(node2 == node1);
    }

    //================================================================

    TEST_CASE("Equality Operator FALSE test", "[B node]")
    {
        auto node1 {b_node<int, std::less<int>>(five, comp)};
        auto node2 {b_node<int, std::less<int>>(seven, comp)};

        bool equal {node1 == node2};

        REQUIRE(!equal);
    }

    //===================================================================

    TEST_CASE("Has Left Child TRUE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(five, comp)};

        root.SetLeftChild(seven);

        REQUIRE(root.HasLeftChild());
    }

    //===================================================================

    TEST_CASE("Has Left Child FALSE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(five, comp)};
        REQUIRE(!root.HasLeftChild());
    }

    //===================================================================

    TEST_CASE("Has Parent TRUE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(seven, comp)};
        root.SetLeftChild(five);
        auto left = root.LeftChild();

        REQUIRE(left->HasParent());
    }

    //===================================================================

    TEST_CASE("Has Parent FALSE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(five, comp)};
        REQUIRE(!root.HasParent());
    }

    //===================================================================

    TEST_CASE("Has Right Child TRUE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(five, comp)};
        root.SetRightChild(seven);

        REQUIRE(root.HasRightChild());
    }

    //===================================================================

    TEST_CASE("Has Right Child FALSE test", "[B node]")
    {
        auto root {b_node<int, std::less<int>>(five, comp)};
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
        auto root = b_node<int, std::less<int>>(seven, comp);
        REQUIRE(!root.HasLeftChild());

        root.SetLeftChild(five);

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
        auto root = b_node<int, std::less<int>>(five, comp);
        
        REQUIRE(!root.HasRightChild());
        root.SetRightChild(seven);
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
        auto nums = std::vector<int>{50, 40, 30};

        auto root = b_node<int, std::less<int>>(nums[0], comp);
        root.SetLeftChild(nums[1]);
        root.LeftChild()->SetLeftChild(nums[2]);

        REQUIRE(root.LeftChild()->HasLeftChild());

        root.DeleteLeftChild();

        REQUIRE(root.HasLeftChild());
        REQUIRE(root.LeftChild()->Data() == nums[2]);
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
        auto nums = std::vector<int>{50, 70, 80};

        auto root = b_node<int, std::less<int>>(nums[0], comp);
        root.SetRightChild(nums[1]);
        root.RightChild()->SetRightChild(nums[2]);

        REQUIRE(root.RightChild()->HasRightChild());

        root.DeleteRightChild();

        REQUIRE(root.HasRightChild());
        REQUIRE(root.RightChild()->Data() == nums[2]);
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
        auto nums = std::vector<int>{40, 35, 30, 37};

        auto root = b_node<int, std::less<int>>(nums[0], comp);
        root.SetLeftChild(nums[1]);
        root.LeftChild()->SetLeftChild(nums[2]);
        root.LeftChild()->SetRightChild(nums[3]);

        //---------------------------------------

        root.DeleteLeftChild();

        REQUIRE(root.HasLeftChild());
        REQUIRE(root.LeftChild()->Data() == nums[3]);
        
        REQUIRE(root.LeftChild()->HasLeftChild());
        REQUIRE(root.LeftChild()->LeftChild()->Data() == nums[2]);
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
        auto nums = std::vector<int>{40, 50, 45, 55};

        auto root = b_node<int, std::less<int>>(nums[0], comp);
        root.SetRightChild(nums[1]);
        root.RightChild()->SetLeftChild(nums[2]);
        root.RightChild()->SetRightChild(nums[3]);

        //---------------------------------------------------

        root.DeleteRightChild();

        REQUIRE(root.RightChild()->HasRightChild());
        REQUIRE(root.RightChild()->RightChild()->Data() == nums[3]);
    }    
}