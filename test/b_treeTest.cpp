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

    TEST_CASE("Lambda invariant construction Test", "[B tree]")
    {
        auto t = b_tree<int, [](const int &lhs, const int &rhs)
        {
            return lhs < rhs;
        }>();
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

        REQUIRE(t.Contains(128));    
    }

    //=========================================================================

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

    TEST_CASE("Find successfully mutates the out variable", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        auto node = b_node<int, std::less<int>>();
        bool found = t.Find(130, node);

        REQUIRE(node.Data() == 130);        
    }

    //=========================================================================

    /*--------------------------------------

          BEFORE                AFTER      

            155                  155
           /   \                /
         130   [175]          130

    --------------------------------------*/

    TEST_CASE("Root has not been mutated after delete", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        auto root1 = t.Root();

        t.Delete(175);

        auto root2 = t.Root();

        REQUIRE(root1 == root2);
    }


    //==========================================================================

    /*--------------------------------------

          BEFORE                AFTER      

            155                  155
           /   \                /
         130   [175]          130

    --------------------------------------*/

    TEST_CASE("Parent has no right child after deleting right child", "[B tree]")
    {
        auto nums {std::vector<int>{155, 130, 175}};
        auto t {b_tree<int>(nums)};

        int refcount = t.Root().LeftChildPtr().use_count(); // 3
        t.Delete(130);
        refcount = t.Root().LeftChildPtr().use_count(); // still 2

        REQUIRE(!t.RootPtr()->HasLeftChild());        
    }

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