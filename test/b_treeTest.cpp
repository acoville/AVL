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
}