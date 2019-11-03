/*============================================

    Node class for the AVL tree
    
    identical to the b_node except that
    it adds the RotateLeft and RotateRight
    functions and Balance Factor functionality.

============================================*/

#ifndef AVL_NODE_HPP
#define AVL_NODE_HPP

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
                : b_node <T, invariant>(obj, comp)
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

            /*-------------------------------------------

                RIGHT ROTATION

                       BEFORE:              AFTER:

                        [40]                 [35]
                       /   \                /    \
                     [35]   50            20      [40]
                     /  \                /  \     /  \
                   20   37              18  22   37  50
                  /  \
                18    22
            
            ---------------------------------------------*/

            void RotateRight()
            {

            }

            //======================================================

            /*----------------------------------------

                LEFT ROTATION

                    BEFORE:             AFTER: 




            ----------------------------------------*/

            void RotateLeft()
            {

            }

            //======================================================

            virtual void SetRightChild(const T &obj) override
            {
                *this->rightChild_ = std::make_shared<avl_node>(obj, *this->comp_);
                *this->rightChild_->SetHeight(*this->height_ + 1);
                *this->rightChild_->parent_ = std::make_shared<avl_node>(*this);

                if(*this->leaf_)
                    *this->leaf_ = false;
            }

            //=======================================================

            virtual void SetLeftChild(const T &obj) override
            {
                *this->leftChild_ = std::make_shared<avl_node>(obj, *this->comp_);
                *this->leftChild_->SetHeight(*this->height_ + 1);
                *this->leftChild_->parent_ = std::make_shared<avl_node>(*this);

                if(*this->leaf_)
                    *this->leaf_ = false;
            }
    };
}

#endif