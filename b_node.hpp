/*==========================================================

    node class for binary tree


=========================================================*/

#include <memory>
#include <functional>

namespace AVL
{
    template<typename T, class invariant = std::less<T>>
    class b_node
    {
        protected: 

        invariant comp_;
        std::shared_ptr<T> data_;

        std::shared_ptr<b_node> leftChild_ {nullptr};
        std::shared_ptr<b_node> rightChild_ {nullptr};
        std::shared_ptr<b_node> parent_ {nullptr};

        public: 

        b_node(const T &obj, const invariant &comp) : 
            comp_ {comp},
            data_ {std::make_shared<T>(obj)}
        {}

        //------------------------------------------------

        virtual ~b_node()
        {}

        //===================================================

        bool operator > (const b_node &other) const
        {
            return(*data_ > other.Data());
        }

        //-------------------------------------------

        bool operator > (const T &obj) const
        {
            return(*data_ > obj);
        }

        //==================================================

        bool operator < (const b_node &other) const
        {
            return (*data_ < other.Data());
        }

        //-----------------------------------------

        bool operator < (const T &obj) const 
        {
            return (*data_ < obj);
        }

        //===================================================

        /*-----------------------------------------

            okay, after my troubles last time 
            I want to be a lot more specific here. 
            I want to make sure all pointers 
            are pointing to the same addresses. 

        ------------------------------------------*/

        bool operator == (const b_node &other) const
        {
            bool left = leftChild_ == other.leftChild_;
            bool right = rightChild_ == other.rightChild_;
            bool parent = parent_ == other.parent_;
            bool data = data_ == other.data_;

            if(left and right and parent and data)
            {
                return true;
            }

            else
            {
                return false;
            }
        }

        //===================================================

        const T & Data() const
        {
            return *data_;
        }

        //====================================================

        /*----------------------------------------------------

            Public API of the left child property

            I got myself in a lot of trouble last time here. 
            the b_tree needs to be able to touch the pointers, 
            not just copies of the pointers, or else none of 
            the parent / child pointers are pointing to the 
            correct objects and I'm just in shared_ptr hell.

            I don't need a Setter accepting a shared pointer,
            I will handle that direclty in the rotation calls 
            by simply assigning this pointer = to another one.

        ----------------------------------------------------*/

        bool HasLeftChild() const
        {
            return(leftChild_) ? true : false;
        }

        //--------------------------------------

        b_node & LeftChild()
        {
            return *leftChild_;
        }

        //--------------------------------------

        void SetLeftChild(const T &obj)
        {
            leftChild_ = std::make_shared<b_node<T, invariant>>(obj, comp_);
        }

        void SetLeftChild(std::shared_ptr<b_node<T, invariant>> &other)
        {
            leftChild_ = other;
        }
    };
}