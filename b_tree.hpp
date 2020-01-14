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

            std::unique_ptr<b_node<T, invariant>> root_ {nullptr};
            invariant comp_;


        public:

            b_tree() = default;
            
            virtual ~b_tree()
            {}

            //====================================================

            /*---------------------------

                Insert

            ---------------------------*/

            void Insert(const T &obj)
            {

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

            b_node<T, invariant> * Find(T key)
            {

            }
    };
}

#endif