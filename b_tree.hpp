/*======================================================

    Binary Search Tree


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

            //=====================================================

            /*------------------------------

                Constructor accpepting a 
                vector of objects to insert
                into the tree.

            ------------------------------*/

            b_tree(std::vector<T> &objs)
            {
                for(auto &o : objs)
                    Insert(o);
            }
            
            //==========================================

            virtual ~b_tree()
            {}

            //==========================================

            // getters

            b_node<T, invariant> & Root()
            {
                return *root_;
            }

            //------------------------------------

            operator bool() const
            {
                return(root_ == nullptr) ? false : true;
            }

            //------------------------------------
            
            void operator += (const T &obj)
            {
                Insert(obj);
            }

            //------------------------------------

            int Size() const
            {
                return size_;
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
                auto It {root_};

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

            /*----------------------------------------

                Delete

            ----------------------------------------*/

            virtual void Delete(const T &obj)
            {
                auto it {root_};

                if(root_->Data() == obj)
                {
                    root_->Reset();
                }

                // otherwise, we are deleting a child node
                // the node class will handle how to reassign
                // its own child/ren

                else
                {
                    auto found = Find(obj, *it);
                    auto parent = it->Parent();

                    // is it parent's left child? 

                    if(it->Data() < parent.Data())
                    {
                        parent.DeleteLeftChild();
                    }

                    // must be parent's right child,
                    // equal nodes are undefined in a BST

                    else
                    {
                        parent.DeleteRightChild();
                    }
                }
            }

            //=========================================================

            /*-------------------------------------

                corner case: what to do if 
                obj isn't found? 

            -------------------------------------*/

            bool Find(const T &obj, b_node<T, invariant> &out)
            {
                // exit if root_ is null

                if(!root_)
                {
                    return false;
                }

                auto it = root_;

                BEGIN:

                if(it->Data() == obj)
                {
                    out = *it;
                    return true;
                }

                // left subtree

                if(obj < it->Data())
                {
                    if(it->HasLeftChild())
                    {
                        it = it->LeftChildPtr();
                        goto BEGIN;
                    }
                }

                // right subtree

                else
                {
                    if(it->HasRightChild())
                    {
                        it = it->RightChildPtr();
                        goto BEGIN;
                    }
                }

                return false;
            }
    };
}

#endif