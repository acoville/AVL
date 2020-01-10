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

            b_tree(std::vector<T> &objs)
            {
                for(auto &o : objs)
                    Insert(o);
            }
            
            //------------------------------------

            virtual ~b_tree()
            {}

            //------------------------------------

            b_node<T, invariant> & Root()
            {
                return *root_;
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

                I wonder what happens
                if you delete the root node? Does
                root get reassigned or do we 
                lose the whole tree? 

            ----------------------------------------*/

            virtual void Delete(const T &obj)
            {
                auto it {root_};

                if(Find(obj, *it))
                {
                    if(it->Data() == obj)
                    {
                        root_.reset();
                    }

                    /*   
                        we will have to use the parent's 
                        delete L / R child() function to ensure
                        children are reassigned appropriately.

                    else
                    {
                        auto parent {it->ParentPtr()};

                        if(it->Data() < parent->Data())
                        {
                            parent->DeleteLeftChild();
                        }

                        else
                        {
                            parent->DeleteRightChild();
                        }

                        size_--;
                    }
                    */
                }
            }

            //=========================================================

            /*-------------------------------------

                corner case: what to do if 
                obj isn't found? 

            -------------------------------------*/

            bool Find(const T &obj, b_node<T, invariant> &out)
            {
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