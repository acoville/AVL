/*==========================================================

    node class for binary tree


=========================================================*/

#ifndef B_NODE_HPP
#define B_NODE_HPP

#include <memory>
#include <functional>

namespace AVL
{
    template <typename T, class invariant>
    class b_node
    {
        protected: 

        invariant comp_;
        std::shared_ptr<T> data_ {nullptr};

        std::shared_ptr<b_node> leftChild_ {nullptr};
        std::shared_ptr<b_node> rightChild_ {nullptr};
        std::shared_ptr<b_node> parent_ {nullptr};

        int height_ {0};
        bool leaf_ {true};

        public: 

        //======================================================

        // constructors

        b_node() = default;
        
        b_node(const T &obj, const invariant comp) : 
            comp_ {comp},
            data_ {std::make_shared<T>(obj)}
        {}

        //------------------------------------------------

        // (shallow) copy semantics

        b_node(const b_node &other) : 
            comp_ {other.comp_},
            data_ {other.data_},
            leftChild_ {other.leftChild_},
            rightChild_ {other.rightChild_},
            parent_ {other.parent_},
            height_ {other.height_}
        {}

        //----------------------------------------------

        b_node& operator = (const b_node &other)
        {
            data_ =  other.data_;
            leftChild_ = other.leftChild_;
            rightChild_ = other.rightChild_;
            parent_ = other.parent_;
            comp_ = other.comp_;
            height_ = other.height_;

            return *this;
        }

        //------------------------------------------------

        virtual ~b_node()
        {
        }

        //===================================================

        /*-----------------------------

            Reset function releases
            calling object's claim to the 
            shared pointer

        -----------------------------*/

        void Reset()
        {
            data_.reset();
            parent_.reset();
            leftChild_.reset();
            rightChild_.reset();
        }

        //===================================================

        bool operator > (const b_node &other) const
        {
            return comp_(other.Data(), *data_);
        }

        //-------------------------------------------

        bool operator > (const T &obj) const
        {
            return comp_(obj, *data_);
        }

        //==================================================

        bool operator < (const b_node &other) const
        {
            return comp_(*data_, other.Data());
        }

        //-----------------------------------------

        bool operator < (const T &obj) const 
        {
            return comp_(*data_, obj);
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
            bool left {leftChild_ == other.leftChild_};
            bool right {rightChild_ == other.rightChild_};
            bool parent {parent_ == other.parent_};
            bool data {data_ == other.data_};

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

        operator bool () const
        {
            return(data_ == nullptr) ? false : true;
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
            return(leftChild_ == nullptr) ? false : true;
        }

        //--------------------------------------

        b_node & LeftChild()
        {
            return *leftChild_;
        }

        //------------------------

        std::shared_ptr<b_node> & LeftChildPtr()
        {
            return leftChild_;
        }

        //---------------------------------------------

        // create a new node pointing to obj

        virtual void SetLeftChild(const T &obj)
        {
            leftChild_ = std::make_shared<b_node>(obj, comp_);
            leftChild_->SetHeight(height_ + 1);
            leftChild_->parent_ = std::make_shared<b_node>(*this);

            if(leaf_)
                leaf_ = false;
        }

        //---------------------------------------------

        // overload directly reassigning the left child pointer

        virtual void SetLeftChild(std::shared_ptr<b_node> &other)
        {
            leftChild_ = other;
            leftChild_->SetHeight(height_ + 1);
            leftChild_->parent_ = std::make_shared<b_node>(*this);

            if(leaf_)
                leaf_ = false;            
        }

        //============================================================

        bool IsLeaf() const
        {
            return leaf_;
        }

        //============================================================

        /*--------------------------------

            Right Child Property

        ---------------------------------*/

        bool HasRightChild() const
        {
            return (rightChild_ == nullptr) ? false : true;
        }

        //-----------------------------------------------

        b_node & RightChild()
        {
            return *rightChild_;
        }

        std::shared_ptr<b_node> & RightChildPtr()
        {
            return rightChild_;
        }

        //-----------------------------------------------

        virtual void SetRightChild(const T &obj)
        {
            rightChild_ = std::make_shared<b_node>(obj, comp_);
            rightChild_->SetHeight(height_ + 1);
            rightChild_->parent_ = std::make_shared<b_node>(*this);

            if(leaf_)
                leaf_ = false;
        }

        //-------------------------------------------------

        void SetRightChild(std::shared_ptr<b_node> &other)
        {
            rightChild_ = other;
            rightChild_->SetHeight(height_ + 1);
            rightChild_->parent_ = std::make_shared<b_node>(*this);

            if(leaf_)
                leaf_ = false;
        }

        //============================================================

        /*---------------------------------

            Parent Property

        ----------------------------------*/

        bool HasParent() const
        {
            return (parent_ == nullptr) ? false : true;
        }

        //-------------------------------------

        b_node & Parent()
        {
            return *parent_; 
        }

        //-------------------------------------

        std::shared_ptr<b_node<T, invariant>> & ParentPtr()
        {
            return parent_;
        }

        //============================================================

        int Height() const
        {
            return height_;
        }

        //--------------------------------

        void SetHeight(int newHeight)
        {
            height_ = newHeight;

            if(leftChild_)
                leftChild_->SetHeight(newHeight);

            if(rightChild_)
                rightChild_->SetHeight(newHeight);
        }

        //==============================================================

        /*-----------------------------

            Delete Left Child

        ------------------------------*/

        void DeleteLeftChild()
        {
            /*-----------------------------------------

                    BEFORE:            AFTER:

                        40              40
                       /  \               \
                    [35]   55              55

            --------------------------------------------*/

            if(leftChild_->IsLeaf())
            {
                leftChild_.reset();
                leftChild_ = nullptr;
                return;
            }

            int children {0};

            if(leftChild_->HasLeftChild())
                children++;

            if(leftChild_->HasRightChild())
                children++;

            switch(children)
            {
                /*------------------------------------------------
            
                case 2: left child has 1 child

                    BEFORE:         AFTER:

                        40              40
                       /  \            /  \
                    [35]   55        30    75
                    /       
                  30        

                ------------------------------------------------*/

                case(1):
                {
                    if(leftChild_->HasLeftChild())
                    {
                        SetLeftChild(leftChild_->leftChild_);
                    }
                    else
                    {
                        SetLeftChild(leftChild_->rightChild_);
                    }

                    break;
                }

                /*------------------------------------------------
                    
                    case 3: child has 2 children

                            BEFORE:         AFTER:

                              40              40
                             /  \            /  \
                          [35]   50        39    50
                          /  \             / 
                        30    39         30   

                --------------------------------------------------*/

                case(2):
                {
                    auto LeftLeft = leftChild_->LeftChildPtr();
                    auto LeftRight = leftChild_->RightChildPtr();

                    if(*LeftLeft > *LeftRight)
                    {
                        SetLeftChild(LeftLeft);
                        leftChild_->SetLeftChild(LeftRight);
                    }
                    else
                    {
                        SetLeftChild(LeftRight);
                        leftChild_->SetLeftChild(LeftLeft);
                    }

                    break;
                }
            }
        }       

        //==================================================================

        /*----------------------------

            Delete Right Child

        ---------------------------*/

        void DeleteRightChild()
        { 
            /*-------------------------------------

                case 1: R child is a leaf

                    BEFORE:             AFTER:

                        40              40
                       /  \            /
                     35    [55]       35
    
            -------------------------------------*/

            if(rightChild_->IsLeaf())
            {
                rightChild_.reset();
                //rightChild_ = nullptr;
                return;
            }

            // there are children nodes that need to 
            // be reassigned.

            int children {0};

            if(rightChild_->HasLeftChild())
                children++;

            if(rightChild_->HasRightChild())
                children++;

            switch(children)
            {
                /*-----------------------------------------

                        case 2: child has 1 child

                            BEFORE:         AFTER:

                              40              40
                             /  \            /  \
                          [35]   55        30    55
                          /
                         30

                ------------------------------------------*/

                case(1):
                {
                    if(rightChild_->HasLeftChild())
                    {
                        SetRightChild(rightChild_->leftChild_);
                    }
                    else
                    {
                        SetRightChild(rightChild_->rightChild_);
                    }

                    break;
                }

                /*--------------------------------------------

                    case 3: R child has 2 children

                            BEFORE:             AFTER:

                            40                  40
                              \                  \
                             [50]                 45
                             /  \                  \
                            45   55                 55

                ---------------------------------------------*/

                case(2):
                {
                    auto RightLeft = rightChild_->LeftChildPtr();
                    auto RightRight = rightChild_->RightChildPtr();

                    if(*RightLeft < *RightRight)
                    {
                        SetRightChild(RightLeft);
                        rightChild_->SetRightChild(RightRight);
                    }
                    else
                    {
                        SetRightChild(RightRight);
                        rightChild_->SetRightChild(RightLeft);
                    }

                    break;
                }
            }
        }     
    };
}

#endif