/*==========================================

    Test Suite for Binary Search Tree


===========================================*/

#include "include/catch.hpp"
#include "../b_tree.hpp"
#include <vector>

namespace AVL::test
{

    TEST_CASE("B Tree Construction Test", "[B Tree]")
    {
        auto t = b_tree<int, std::less<int>>();
    }

    //============================================================

    TEST_CASE("Insert to an empty Tree Test", "[B Tree]")
    {
        int i {25};
        auto t = b_tree<int, std::less<int>>();

        t.Insert(i);

        auto root = t.Root();
        REQUIRE(root->Data() == 25);
    }

    //============================================================

    /*---------------------------

                25
               /  
             12

    ----------------------------*/

    TEST_CASE("Insert Left Child Test", "[B Tree]")
    {
        auto nums = std::vector<int>{25, 12};
        auto t = b_tree<int, std::less<int>>();

        for(auto &n : nums)
            t.Insert(n);

        REQUIRE(t.Root()->HasLeftChild());
        REQUIRE(t.Root()->LeftChild().Data() == 12);
    }

    //============================================================

    /*-----------------------------------

                      155
                 ____/   \____ 
               /              \
             130               175
            /  \              /   \
          127   135        170     177
         /   \
       120   128

    ------------------------------------*/

    TEST_CASE("Smallish Insertion Accuracy Test", "[B Tree]")
    {
        auto nums = std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120};
        auto t = b_tree<int, std::less<int>>();

        for(auto &n : nums)
            t += n;

        auto root = t.Root();

        REQUIRE(root->LeftChild().LeftChild().HasLeftChild());

        auto leftMostLeaf = root->LeftChild().LeftChild().LeftChild();

        REQUIRE(leftMostLeaf.Data() == 120);
    }

    
}