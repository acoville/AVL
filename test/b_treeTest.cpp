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
        auto t = b_tree<int>();
    }

    //============================================================

    TEST_CASE("Insert to an empty Tree Test", "[B Tree]")
    {
        int i {25};
        auto t = b_tree<int>();

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
        auto t = b_tree<int>();

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
        auto t = b_tree<int>();

        for(auto &n : nums)
            t += n;

        auto root = t.Root();

        REQUIRE(root->LeftChild().LeftChild().HasLeftChild());

        auto leftMostLeaf = root->LeftChild().LeftChild().LeftChild();

        REQUIRE(leftMostLeaf.Data() == 120);
    }

    //========================================================================

    TEST_CASE("Test of Find TRUE", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120}};
                
        auto t {b_tree<int>()};

        for(auto &n : nums)
            t += n;

        b_node<int, std::less<int>> out {};
        bool found = t.Find(130, out);

        REQUIRE(found);
        REQUIRE(out.Data() == 130);
    }

    //=========================================================================

    TEST_CASE("Test of Find FALSE", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120}};
                
        auto t {b_tree<int>()};

        for(auto &n : nums)
            t += n;

        b_node<int, std::less<int>> out {};
        bool found = t.Find(500, out);

        REQUIRE(!found);
    }

    //==========================================================================

    TEST_CASE("Test of Delete Function", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120}};
                
        auto t {b_tree<int>()};

        for(auto &n : nums)
            t += n;

        int size_before {t.Size()};

        t.Delete(128);

        int size_after {t.Size()};
        b_node <int, std::less<int>> out {};

        REQUIRE(size_after == size_before -1);
        REQUIRE(!t.Find(128, out));
    }
}