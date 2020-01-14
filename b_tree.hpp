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

            b_node<T, invariant> *root_ {nullptr};
            int height_ {0};
            int size_ {0};
            invariant comp_;

            //=====================================================
/*
            void Destroy(b_node<T, invariant> * leaf)
            {


                if(leaf)
                {
                    Destroy(leaf->LeftChild());
                    Destroy(leaf->RightChild());
                    delete leaf;
                }
            }
*/

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
            {
                //Destroy(root_);
            }

            //==========================================

            // getters

            b_node<T, invariant> * Root()
            {
                return root_;
            }

            //------------------------------------

            operator bool() const
            {
                return(root_ == nullptr) ? false : true;
            }

            //------------------------------------
            
            void operator += (T &obj)
            {
                Insert(obj);
            }

            //------------------------------------

            int Size() const
            {
                return size_;
            }

            //========================================================

            virtual void Insert(T &obj)
            {
                if(!root_)
                {
                    root_ = new b_node<T, invariant>(obj, comp_);
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
                        It = It->LeftChild();
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
                        It = It->RightChild();
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
                auto *it = root_;

                // if this is the root node, delete the 
                // whole tree

                if(root_->Data() == obj)
                {
                    delete root_;
                    root_ = nullptr;
                }

                // otherwise, we are deleting a child node
                // the node class will handle how to reassign
                // its own child/ren

                else
                {
                    if(Find(obj, it))
                    {
                        //auto parent = it.Parent();
                 
                        it = &it->Parent();

                        // is it parent's left child? 

                        if(obj < it->Data())
                        {
                            it->DeleteLeftChild();
                        }

                        // must be parent's right child,
                        // equal nodes are undefined in a BST

                        else
                        {
                            it->DeleteRightChild();
                        }
                    }
                }
            }

            //=========================================================

            bool Contains(const T &obj)
            {
                auto out = root_;
                return(Find(obj, out));
            }

            //=========================================================

            /*---------------------------------------

                Binary Search Find function

                returns T if the value is found, 
                and modifies the out parameter
                to the node containing the value

            ---------------------------------------*/

            bool Find(const T &obj, b_node<T, invariant> *out)
            {
                // exit if root_ is null

                if(!root_)
                {
                    return false;
                }

                // otherwise, begin binary search at root node

                auto it = root_;

                BEGIN:

                if(it->Data() == obj)
                {
                    out = it;
                    return true;
                }

                // left subtree

                if(obj < it->Data())
                {
                    if(it->HasLeftChild())
                    {
                        it = it->LeftChild();
                        goto BEGIN;
                    }
                    else
                    {
                        goto END;
                    }
                }

                // right subtree

                else
                {
                    if(it->HasRightChild())
                    {
                        it = it->RightChild();
                        goto BEGIN;
                    }
                    else
                    {
                        goto END;
                    }
                    
                }

                // if we have reached a leaf node, then the 
                // value is not in the tree.

                END:

                return false;
            }
    };
}

#endif