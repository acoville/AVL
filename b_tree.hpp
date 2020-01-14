/*=========================================================

    C++ Data Structures Library
    Binary Tree class

    observing: does not own the underlying data, 
    declare in same or lower scope as the data it is
    referencing

    generic: accepts 2 template arguments
        1st: (mandatory) typename
        2nd: (optional) custom invariant, any class
            with an () operator accepting 2 params
            lhs and rhs and returning type bool may
            be supplied here. By default it will be
            std::less<T> and will control sorting 
            behavior within the tree. 

========================================================*/

#ifndef B_TREE_HPP
#define B_TREE_HPP

#include "b_node.hpp"
#include <memory>

namespace AVL
{
    template<typename T, class invariant = std::less<T>>
    class b_tree
    {
        protected:

            b_node<T, invariant> *root_ {nullptr};

            int height_ {0};
            int size_ {0};
            invariant comp_;


        public:

            b_tree() = default;

            //-------------------------------------

            b_tree(std::vector<T> data)
            {
                for(auto d : data)
                {
                    Insert(d);
                }
            }
            
            //------------------------------------

            virtual ~b_tree()
            {}

            b_node<T, invariant> & Root()
            {
                return *root_;
            }

            //------------------------------------

            std::shared_ptr<b_node<T, invariant>> & RootPtr()
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

            //============================================================

            /*---------------------------

                Insert

            ---------------------------*/

            virtual void Insert(T &obj)
            {
                if(root_ == nullptr)
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

            //===================================================

            /*-----------------------------

                Delete

            -----------------------------*/

            void Delete(T key)
            {

            }

            //===================================================

            /*----------------------------

                Search

            ----------------------------*/

            bool Find(T obj, b_node<T, invariant> *out = nullptr)
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
                    if(out != nullptr)
                    {
                        out = it;
                    }

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