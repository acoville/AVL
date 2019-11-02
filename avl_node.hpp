/*============================================

    Node class for the AVL tree
    
    identical to the b_node except that
    it adds the RotateLeft and RotateRight
    functions

============================================*/

#include "b_node.hpp"

namespace AVL
{
    template <typename T, class invariant> 
    class avl_node : public b_node <T, invariant>
    {
        protected:

            int leftChildren_ {0};
            int rightChildren_ {0};

        public:

            avl_node(const T &obj, const invariant &comp) 
                : b_node(obj, comp)
            {}

            //=====================================================

            virtual ~avl_node()
            {}

            //======================================================

            int BalanceFactor() const
            {
                return rightChildren_ - leftChildren_;
            }

            //======================================================

            void RotateRight()
            {

            }

            //======================================================

            void RotateLeft()
            {

            }
    };
}