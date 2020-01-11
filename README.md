# AVL2.0
generic c++ binary and avl tree classes

Unfortunately the std library does not ship with BST or its more advanced alternative the AVL tree. These are quite useful and even necessary for some advanced and optimized algorithms. I wrote these classes to use in a sweep line algorithm, but I think anyone will find them easily adaptable to their project.

# Binary Search Tree

b_tree is a template class accepting 1 or 2 template parameters

* T (required) - the template type

* invariant (optional) - the rule governing < and > within this  tree. By default, this will be std::less<T>, which would require that T have < and > operators implemented. I did not want to commit one of my classes to implementing < and > just for this function, so any object with the () operator accepting lhs and rhs operands and returning bool may be substituted. 

        // default invariant declaration (std::less<T>)

        auto t = b_tree<int>();

        // custom invariant declaration

        auto t = b_tree<int, std::greater<int>>();

The tree does not "own" or store the raw underlying objects, it makes pointers referring to them. This allows existing structures to add binary search functionality without refactoring them. But it is therefore imperative that the binary tree be declared in the same or lower scope than the owning data structure. 

For convenience,I have included a constructor that accepts a vector of T as a parameter, which will automatically add all elements. 

    // adds all elements in nums to tree t

    auto nums = std::vector<int>{1, 2, 3, 4, 5};
    auto t = b_tree<int>(nums);

* Insert: 

Adding elements to a tree can be done using the .Insert() function, or its alias the += operator

    auto nums = std::vector<int>{1, 2, 3, 4, 5};
    auto t = b_tree<int>();

    for(auto num : nums)
    {
        t += num;

        // OR

        t.Insert(num);
    }

* Find: 

Return type of bool indicating weather or not the value was found within the tree. The first parameter is the value to search for, the 2nd parameter is an optional out variable which Find will reassign to the located node.

    auto node = b_node<int>();
    
    if(t.Find(155, node))
    {
        // do something
    }

A simpler Contains() function with no out variable can simply search for a value and return T or F.

* Delete: 

