/*==============================================

    AVL Tree Definition


===============================================*/

#ifndef AVL_TREE_HPP
#define AVL_TREE_HPP

#include "b_tree.hpp"

namespace AVL
{
    template <typename T, class invariant = std::less<T>>
    class avl_tree : public b_tree <T, invariant>
    {
        protected: 

            

        public:

            avl_tree() = default;

            //========================================================

            virtual ~avl_tree()
            {}

            //========================================================

            virtual void Insert(const T &obj)
            {

            }

            //=======================================================

            virtual void Delete(const T &obj)
            {

            }
    };
}

#endif