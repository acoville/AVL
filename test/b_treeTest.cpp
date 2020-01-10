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
        auto t {b_tree<int>()};

        REQUIRE(t.Size() == 0);
    }

    //============================================================

    TEST_CASE("Construction using a vector", "[B Tree]")
    {
        auto v {std::vector<int>{12, 55, 125, 225, 275}};
        auto t {b_tree<int>(v)};

        REQUIRE(t.Size() == 4);
    }

    //============================================================

    TEST_CASE("Insert to an empty Tree Test", "[B Tree]")
    {
        int i {25};
        auto t = b_tree<int>();

        t.Insert(i);

        auto root = t.Root();
        REQUIRE(root.Data() == 25);
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

        REQUIRE(t.Root().HasLeftChild());
        REQUIRE(t.Root().LeftChild().Data() == 12);
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

        REQUIRE(root.LeftChild().LeftChild().HasLeftChild());

        auto leftMostLeaf = root.LeftChild().LeftChild().LeftChild();

        REQUIRE(leftMostLeaf.Data() == 120);
    }

    //========================================================================

    /*-----------------------------------

                      155
                 ____/   \____ 
               /              \
             130               175
            /  \              /   \
          127   135        170     177
         /   \
       120   [128]

    ------------------------------------*/

    TEST_CASE("Test of Find TRUE", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120}};
        auto t {b_tree<int>(nums)};

        b_node<int, std::less<int>> out {};
        bool found = t.Find(128, out);

        REQUIRE(found);    
    }

    //=========================================================================

    TEST_CASE("Test of Find FALSE", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120}};
        auto t {b_tree<int>(nums)};

        b_node<int, std::less<int>> out {};
        bool found = t.Find(500, out);

        REQUIRE(!found);
    }

    //==========================================================================

    TEST_CASE("An empty tree returns boolean false", "[B tree]")
    {
        auto t {b_tree<int>()};
        REQUIRE(!t);
    }

    //==========================================================================

    TEST_CASE("A tree with 1 node returns boolean true", "[B tree]")
    {
        auto t {b_tree<int>()};
        t += 155;

        REQUIRE(t);
    }

    //==========================================================================

    TEST_CASE("Deleting root node makes the tree return boolean false again", "[B tree]")
    {
        auto t {b_tree<int>()};
        t += 155;
        t.Delete(155);

        REQUIRE(!t);
    }

    //==========================================================================

    /*--------------------------------------

          BEFORE                AFTER      

            155                  155
           /   \                /
         130   [175]          130
    
    --------------------------------------*/

    TEST_CASE("Test of FIND returns false after a delete in right subtree", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        b_node<int, std::less<int>> out {};
        bool found = t.Find(175, out);
        REQUIRE(found);

        bool leaf = out.IsLeaf();
        REQUIRE(leaf);

        t.Delete(175);

        found = t.Find(175, out);
        REQUIRE(!found);
/*
*/
    }

    //==========================================================================

    /*------------------------------------

          BEFORE                AFTER      

            155                  155
           /   \                    \
        [130]   175                 175


    TEST_CASE("Test of FIND false after a delete in left subtree", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
                
        auto t {b_tree<int>()};

        for(auto &n : nums)
            t += n;

        b_node<int, std::less<int>> out {};
        bool found = t.Find(175, out);

        t.Delete(130);
        auto root = t.Root();

        found = t.Find(130, out);
        REQUIRE(!found);
    }
    -----------------------------------*/

    //==============================================================

    /*----------------------------------

        BEFORE:         AFTER: 

           50             50
          /              /
       [40]             30
        /
      30

    ----------------------------------*/

/*
    TEST_CASE("Delete Left Child case 2: 1 granchild", "[B tree]")
    {
        auto nums = std::vector<int>{50, 40, 30};

        auto t = b_tree<int>{nums};

        // 30 can be found 

        b_node<int, std::less<int>> out {};
        bool found = t.Find(30, out);

        REQUIRE(found);       
        
        t.Delete(40);

        // 30 can still be found 

        found = t.Find(30, out);

        // 50 still has a left child

        auto root = t.Root();

        //REQUIRE(t.Root().HasLeftChild());


        // 30 is 50's left child

        auto leftChild = t.Root().LeftChild();
        REQUIRE(leftChild.Data() == 30);
    }    
*/

    //===============================================================

    /*----------------------------------

        BEFORE:         AFTER: 

           50             50
             \              \
             [70]            80
                \
                 80


    TEST_CASE("Delete Right Child case 2: 1 granchild", "[B tree]")
    {

    }    
    ----------------------------------*/
}