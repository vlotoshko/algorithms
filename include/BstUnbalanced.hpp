/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 02-Jun-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef BST_UNBALANCED_HPP
#define BST_UNBALANCED_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "BstHelperFunctions.hpp"
//--------------------------------------------------------------------------------------------------

namespace bst // binary search tree
{

/**
 * @class BinarySearchTree
 * @brief The BinarySearchTree class is the implementation of binary tree structure
 * @tparam Key key type of the tree
 * @tparam Value value type of the tree
 */
template<typename Key, typename Value>
class BinarySearchTree
{
public:
    struct Node //: public ObjectCounter
    {
        using KeyType = Key;
        using ValueType = Value;
        Node(Key k, Value v) : key(k), val(v), left(nullptr), right(nullptr), size(1) {}
        Key    key;
        Value  val;
        Node*  left;
        Node*  right;
        size_t size; // Number of nodes in a subtree of the current node, including itself
    };

    /// @brief The BinarySearchTree default constructor..
    BinarySearchTree() : root_(nullptr) {}
    ~BinarySearchTree() { bst::clear(root_); }

    /// @brief Puts new element into the tree.
    void put(Key k, Value v) { root_ = put_(root_, k, v); }

    /// @brief Gets from the tree value by key.
    Value get(Key k) const { return bst::get(root_, k); }

    /// @brief Deletes element with the given key.
    void deleteNode(Key k) { root_ = deleteNode_(root_, k); }

    /// @brief Returns mininal key in the tree.
    Key min() const { return bst::min(root_)->key; }

    /// @brief Defines maxinmal key in the tree.
    Key max() const { return bst::max(root_)->key; }

    /// @brief Defines size of the tree.
    size_t size() const { return bst::size(root_); }

    /// @brief Defines whether tree is empty.
    bool isEmpty() const { return size() != 0; }

    /// @brief Calculates sum of all elements in the tree.
    Value valueSum() const { return bst::valueSum(root_); }

    /// @brief Gets nearest element smaller then given.
    Key floor(Key k) const { Node * n = bst::floor(root_, k); return n ? n->key : nullptr; }

    /// @brief Gets nearest element bigger then given.
    Key ceiling(Key k) const { Node * n = bst::ceiling(root_, k); return n ? n->key : nullptr; }

    /// @brief Gets the element by its rank.
    Key select(size_t r) const { Node * n = bst::select(root_, r); return n ? n->key : nullptr; }

    /// @brief Gets the rank of the element.
    size_t rank(Key k)  const { return bst::rank(root_, k); }

    /// @brief Prints all elements of the tree.
    void print() const { print_(root_); }

    /// @brief Returns sorted keys within lo-hi interval.
    std::vector<Key> keys (Key lo, Key hi) const;

    /// @brief Returns all keys sorted.
    std::vector<Key> keys() const { return keys(min(), max()); }

    /// @brief Returns true if tree is balanced keys sorted.
    bool isBalanced() const { return bst::isBalanced(root_); }

private:
    Node* root_; // Root node of the binary search tree

    Node*  put_(Node * n, Key k, Value v);
    Node*  deleteNode_(Node * n, Key k);
    Node*  forgetMin_(Node * n);
};

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node*
BinarySearchTree<Key, Value>::put_(BinarySearchTree::Node * n, Key k, Value v)
{
    if(n == nullptr)
        n = new Node(k, v);

    if (k < n->key)
        n->left = put_(n->left, k, v);
    else
        if (k > n->key)
            n->right = put_(n->right, k, v);
        else
            if (k == n->key)
                ++n->val; // Value have to do prefix increment
    n->size = (n->left ? n->left->size : 0) + (n->right ? n->right->size : 0) + 1;
    return n;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node*
BinarySearchTree<Key, Value>::deleteNode_(BinarySearchTree::Node * n,  Key k)
{
    if(n == nullptr)
        return nullptr;

    if (k < n->key)
        n->left = deleteNode_(n->left, k);
    else if (k > n->key)
        n->right = deleteNode_(n->right, k);
    else
    {
        if (n->right == nullptr)
        {
            Node * t = n->left;
            delete n;
            return t;
        }
        if (n->left == nullptr)
        {
            Node * t = n->right;
            delete n;
            return t;
        }

        Node* t = n;
        n = bst::min(t->right);
        n->right = forgetMin_(t->right);
        n->left = t->left;
        delete t;
    }

    n->size = bst::size(n->left) + bst::size(n->right) + 1;
    return n;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node*
BinarySearchTree<Key, Value>::forgetMin_(BinarySearchTree::Node * n)
{
    if (n->left == nullptr)
        return n->right;

    n->left = forgetMin_(n->left);
    n->size = bst::size(n->left) + bst::size(n->right) + 1;
    return n;
}

template<typename Key, typename Value>
std::vector<Key> BinarySearchTree<Key, Value>::keys(Key lo, Key hi) const
{
    std::vector<Key> vec;
    bst::keys(root_, vec, lo, hi);
    return vec;
}

} // namespace bst

//--------------------------------------------------------------------------------------------------
#endif // BST_UNBALANCED_HPP
//--------------------------------------------------------------------------------------------------
