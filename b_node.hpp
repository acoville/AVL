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

        const T & Data() const
        {
            return *data_;
        }


    };
}