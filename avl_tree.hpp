/*==============================================

    AVL Tree Definition


===============================================*/

#include "b_tree.hpp"
#include "avl_node.hpp"

namespace AVL
{
    template <typename T, class invariant = std::less<T>>
    class avl_tree : public b_tree<T, invariant>
    {
        protected: 

            

        public:

            avl_tree() = default;

            //========================================================

            virtual ~avl_tree()
            {}

            //========================================================

            virtual Insert(const T &obj)
            {

            }

            //=======================================================

            virtual Delete(const T &obj)
            {

            }
    };
}