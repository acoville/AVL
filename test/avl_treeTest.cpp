#include "include/catch.hpp"
#include "../avl_tree.hpp"

namespace AVL::test
{
    TEST_CASE("AVL Tree Construction Test", "[AVL Tree]")
    {
        auto t = avl_tree<int>();
    }
}