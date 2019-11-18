/*======================================================

    Binary Tree


======================================================*/

#ifndef B_TREE_HPP
#define B_TREE_HPP

#include "b_node.hpp"

namespace AVL
{
    template <typename T, class invariant = std::less<T>>
    class b_tree
    {
        protected: 

            std::shared_ptr<b_node<T, invariant>> root_ {nullptr};

            int height_ {0};
            int size_ {0};
            invariant comp_;

        public: 

            b_tree() = default;
            
            //------------------------------------

            virtual ~b_tree()
            {}

            //------------------------------------

            std::shared_ptr<b_node<T, invariant>> Root()
            {
                return root_;
            }

            //------------------------------------
            
            void operator += (const T &obj)
            {
                Insert(obj);
            }

            //========================================================

            virtual void Insert(const T &obj)
            {
                if(!root_)
                {
                    root_ = std::make_shared<b_node<T, invariant>>(obj, comp_);
                    return;
                }

                size_++;
                auto It = root_;

                INSERT:

                // left subtree

                if(*It > obj)
                {
                    if(It->HasLeftChild())
                    {
                        It = It->LeftChildPtr();
                        goto INSERT;
                    }
                    else
                    {
                        It->SetLeftChild(obj);
                    }
                }

                // right subtree

                else
                {
                    if(It->HasRightChild())
                    {
                        It = It->RightChildPtr();
                        goto INSERT;
                    }
                    else
                    {
                        It->SetRightChild(obj);
                    }
                }
            }

            //========================================================
            
            virtual void Delete(const T &obj)
            {

            }

            //=========================================================

            b_node<T, invariant> & Find(const T &obj)
            {

            }
    };
}

#endif