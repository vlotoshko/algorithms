/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 23-Oct-2020
 */

//--------------------------------------------------------------------------------------------------
#ifndef BST_RED_BLACK_HPP
#define BST_RED_BLACK_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "BstHelperFunctions.hpp"
//--------------------------------------------------------------------------------------------------

namespace bst // binary search tree
{

/**
 * @class RedBlackBST
 * @brief The RedBlackBST class is the balanced implementation of binary tree structure
 * @tparam Key key type of the tree
 * @tparam Value value type of the tree
 */
template<typename Key, typename Value>
class BstRedBlack
{
public:
    enum class Color{ RED, BLACK };

    /// @brief The BstRedBlack default constructor..
    BstRedBlack() : root_(nullptr) {}
    ~BstRedBlack() { bst::clear(root_); }

    /// @brief Puts new element into the tree.
    void put(Key k, Value v) { root_ = put_(root_, k, v);  root_->color = Color::BLACK; }

    /// @brief Gets from the tree value by key.
    Value get(Key k) const { return bst::get(root_, k); }

    /// @brief Deletes element with the given key.
    void deleteNode(Key k) { root_ = deleteNode_(root_, k); }

private:
    struct Node //: public ObjectCounter
    {
        using KeyType = Key;
        using ValueType = Value;
        Node(Key k, Value v, Color c)
            : key(k), val(v), color(c), size(1), left(nullptr), right(nullptr) {}
        Key    key;
        Value  val;
        Color  color;
        size_t size;
        Node*  left;
        Node*  right;
    };

    static size_t size_(Node * n);

    Node* root_; // Root node of the binary search tree

    Node*  put_(Node * n, Key k, Value v);
    Node*  deleteNode_(Node * n, Key k);
    Node*  forgetMin_(Node * n);

    bool   isRed_(const Node * n) const;
    Node*  rotateLeft_(Node * n);
    Node*  rotateRight_(Node * n);
    void   flipColors_(Node * n);
};

template<typename Key, typename Value>
typename BstRedBlack<Key, Value>::Node* BstRedBlack<Key, Value>::put_(Node * n,  Key k, Value v)
{
    if(n == nullptr)
        n = new Node(k, v, Color::RED);

    if (k < n->key)
        n->left = put_(n->left, k, v);
    else
        if (k > n->key)
            n->right = put_(n->right, k, v);
        else
            if (k == n->key)
                // In the current impl value is the count of keys, so increment
                ++n->val;

    if (isRed_(n->right) && !isRed_(n->left))
        n = rotateLeft_(n);
    if (n->left != nullptr && isRed_(n->left) && isRed_(n->left->left))
        n = rotateRight_(n);
    if(isRed_(n->left) && isRed_(n->right))
        flipColors_(n);

    n->size = (n->left ? n->left->size : 0) + (n->right ? n->right->size : 0) + 1;
    return n;
}

template<typename Key, typename Value>
typename BstRedBlack<Key, Value>::Node* BstRedBlack<Key, Value>::deleteNode_(Node * n,  Key k)
{
    // TODO: implement node deleting
    return nullptr;
}

template<typename Key, typename Value>
typename BstRedBlack<Key, Value>::Node* BstRedBlack<Key, Value>::forgetMin_(BstRedBlack::Node * n)
{
    if (n->left == nullptr)
        return n->right;

    n->left = forgetMin_(n->left);
    n->size = bst::size(n->left) + bst::size(n->right) + 1;
    return n;
}


template<typename Key, typename Value>
bool BstRedBlack<Key, Value>::isRed_(const Node * n) const
{
    if (n == nullptr)
        return false;

    return n->color == Color::RED;
}

template<typename Key, typename Value>
typename BstRedBlack<Key, Value>::Node*  BstRedBlack<Key, Value>::rotateLeft_(Node * n)
{
    Node * x = n->right;
    n->right = x->left;
    x->left = n;
    x->color = n->color;
    n->color = Color::RED;
    x->size = n->size;
    n->size = bst::size(n->left) + bst::size(n->right) + 1;
    return x;
}

template<typename Key, typename Value>
typename BstRedBlack<Key, Value>::Node*  BstRedBlack<Key, Value>::rotateRight_(Node * n)
{
    Node * x = n->left;
    n->left = x->right;
    x->right = n;
    x->color = n->color;
    n->color = Color::RED;
    x->size = n->size;
    n->size = bst::size(n->left) + bst::size(n->right) + 1;
    return x;
}

template<typename Key, typename Value>
void BstRedBlack<Key, Value>::flipColors_(Node * n)
{
    n->color = Color::RED;
    if (n->left != nullptr)
        n->left->color = Color::BLACK;

    if (n->right != nullptr)
        n->right->color = Color::BLACK;
}

} // namespace bst

//--------------------------------------------------------------------------------------------------
#endif // BST_RED_BLACK_HPP
//--------------------------------------------------------------------------------------------------
