/*=====================================================

    Test Suite for the Binary Search Tree

=====================================================*/

#include "include/catch.hpp"
#include "../b_tree.hpp"

namespace AVL::test
{
    //==========================================================

    TEST_CASE("b_tree construction test", "[b tree]")
    {
        auto t = b_tree<int>();
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

        REQUIRE(root.LeftChild()->LeftChild()->HasLeftChild());
        auto leftMostLeaf = root.LeftChild()->LeftChild()->LeftChild();

        REQUIRE(leftMostLeaf->Data() == 120);
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

        REQUIRE(t.Find(128));    
    }

    //=========================================================================
/*
    TEST_CASE("Test of Find FALSE", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175, 127, 135, 170, 177, 128, 120}};
        auto t {b_tree<int>(nums)};

        REQUIRE(!t.Contains(500));
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
        int five = 155;

        auto t {b_tree<int>()};
        t += five;

        REQUIRE(t);
    }

    //==========================================================================

    TEST_CASE("Deleting root node makes the tree return boolean false again", "[B tree]")
    {
        int five = 155;

        auto t {b_tree<int>()};
        t += five;
        t.Delete(155);

        REQUIRE(!t);
    }

    //==========================================================================

    TEST_CASE("Find successfully mutates the out variable", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        auto node = b_node<int, std::less<int>>();
        bool found = t.Find(130, &node);

        REQUIRE(node.Data() == 130);        
    }
*/

    //=========================================================================

    /*--------------------------------------

          BEFORE                AFTER      

            155                  155
           /   \                /
         130   [175]          130


    TEST_CASE("Root has not been mutated after delete", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        auto root1 = t.Root();

        t.Delete(175);

        auto root2 = t.Root();

        REQUIRE(root1 == root2);
    }
    --------------------------------------*/

    //=========================================================================

     /*--------------------------------------

          BEFORE                AFTER      

            155                  155
           /   \                /
         130   [175]          130


    TEST_CASE("Find is false after deleting right child", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        t.Delete(175);

        REQUIRE(!t.Contains(175));
    }   
    --------------------------------------*/

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

        // 30 is 50's left child

        auto leftChild = t.Root().LeftChild();
        REQUIRE(leftChild->Data() == 30);
    }    
    ----------------------------------*/

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