//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   02-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef BINARY_SEARCH_TREE_HPP
#define BINARY_SEARCH_TREE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <cstddef>
#include <iostream>
#include <vector>
//--------------------------------------------------------------------------------------------------

namespace bst // binary search tree
{

enum class AlgId : int
{
    QUICK_FIND = 100,
    QUICK_UNION,
    QUICK_UNION_BALANCED,
};


template<typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree() : root_(nullptr) {}
    ~BinarySearchTree() { clear_(root_); }

    void    put(Key k, Value v)       { root_ = put_(root_, k, v); }
    Value   get(Key k)          const { return get_(root_, k); }
    void    deleteNode(Key k)         { root_ = deleteNode_(root_, k); }
    void    forgetMin()               { root_ = forgetMin_(root_); }

    Key     min()         const { return min_(root_)->key; }
    Key     max()         const { return max_(root_)->key; }
    size_t  size()        const { return size_(root_); }
    bool    isEmpty()     const { return size() != 0; }
    Value   valueSum()    const { return valueSum_(root_); }

    Key    floor(Key k)   const { Node * n = floor_(root_, k); return n ? n->key : nullptr; }
    Key    ceiling(Key k) const { Node * n = ceiling_(root_, k); return n ? n->key : nullptr; }
    Key    select(int r)  const { Node * n = select_(root_, r); return n ? n->key : nullptr; }
    size_t rank(Key k)    const { return rank_(root_, k); }
    void   print()        const { print_(root_); }
    std::vector<Key> keys (Key lo, Key hi) const;
    std::vector<Key> keys()                const { return keys_(min(), max()); }

private:
    struct Node
    {
        Node(Key k, Value v) : key(k), val(v), left(nullptr), right(nullptr), size(1) {}
        Key    key;
        Value  val;
        Node*  left;
        Node*  right;
        size_t size; // Number of nodes in a subtree of the current node, including itself
    };

    Node* root_; // Root node of the binary search tree

    Value  get_(Node * n, Key k) const;
    Node*  put_(Node * n, Key k, Value v);
    Node*  deleteNode_(Node * n, Key k);
    Node*  forgetMin_(Node * n);
    void   clear_(Node * n);

    Node*  min_(Node * n) const;
    Node*  max_(Node * n) const;
    size_t size_(Node * n) const;
    Value  valueSum_(Node * n) const;

    Node*  floor_(Node * n, Key k) const;
    Node*  ceiling_(Node * n, Key k) const;
    Node*  select_(Node * n, int k) const;
    size_t rank_(Node * n, Key k) const;

    void   print_(Node * n) const;
    void   keys_(Node * n, std::vector<Key>& v, Key lo, Key hi) const;

};


template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::put_(Node * n,  Key k, Value v)
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
Value BinarySearchTree<Key, Value>::get_(Node * n,  Key k) const
{
    if(n == nullptr)
        return nullptr;

    if (k < n->key)
        return get_(n->left, k);
    if (k > n->key)
        return get_(n->right, k);
    return n->val;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::deleteNode_(Node * n,  Key k)
{
    if(n == nullptr)
        return nullptr;

    if (k < n->key)
        n->left = deleteNode_(n->left, k);
    else if (k > n->key)
        n->right = deleteNode_(n->right, k);
    else
    {
        if (n->left == nullptr)
            return n->left;
        if (n->right == nullptr)
            return n->right;
        Node* t = n;
        n = min_(t->right);
        n->right = forgetMin_(t->right);
        n->left = t->left;
    }

    n->count = size(n->left) + size(n->right) + 1;
    return n;
}

template< typename Key, typename Value >
void BinarySearchTree<Key, Value>::clear_(Node* n)
{
    if(n == nullptr)
        return;

    if (n->left)
        clear_(n->left);
    if (n->right)
        clear_(n->right);

    delete n;
    n = nullptr;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::min_(Node * n) const
{
    if (n->left)
        return min_(n->left);
    else
        return n;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::max_(Node * n) const
{
    if (n->right)
        return max_(n->right);
    else
        return n;
}

template<typename Key, typename Value>
size_t BinarySearchTree<Key, Value>::size_(Node * n) const
{
    return n ? n->count : 0;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::forgetMin_(Node * n) \
{
    if(n->left == nullptr)
        return n->right;

    n->left = forgetMin_(n->left);
    n->count = size(n->left) + size(n->right) + 1;
    return n;
}

template<typename Key, typename Value>
Value BinarySearchTree<Key, Value>::valueSum_(Node * n) const
{
    if(n == nullptr)
        return 0;

    Value i = 0;
    if (n->left)
        i += valueSum_(n->left);
    if (n->right)
        i += valueSum_(n->right);

    i += n->val;

    return i;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::floor_(Node * n, Key k) const
{
    if (n == nullptr)
        return nullptr;

    if (n->key == k)
        return n;

    if (n->key > k)
        return floor_(n->left, k);

    Node* t = floor_(n->right, k);
    return t ? t : n;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::ceiling_(Node * n, Key k) const
{
    if (n == nullptr)
        return nullptr;

    if (n->key == k)
        return n;

    if (n->key < k)
        return ceiling_(n->right, k);

    Node* t = ceiling_(n->left, k);
    return t ? t : n;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::select_(Node * n, int k) const
{
    if (n == nullptr)
        return nullptr;

    int t = size(n->left);

    if (t > k)
        return select_(n->left, k);
    else
        if (t < k)
            return select_(n->right, k - t - 1);
        else
            return n;
}

template<typename Key, typename Value>
size_t BinarySearchTree<Key, Value>::rank_(Node * n,  Key k) const
{
    if(n == nullptr)
        return 0;

    if (k < n->key)
        return rank_(n->left, k);
    else
        if (k > n->key)
            return 1 + size_(n->left) + rank_(n->right, k);
        else
            return size_(n->left);
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print_(Node * n) const
{
    if(n == nullptr)
        return;

    print(n->left);
    std::cout << n->key << " ";
    print_(n->right);
}

template< typename Key, typename Value >
std::vector<Key> BinarySearchTree<Key, Value>::keys(Key lo, Key hi) const
{
    std::vector<Key> vec;
    keys_(root_, vec, lo, hi);
    return vec;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::keys_(Node * n, std::vector<Key>& v, Key lo, Key hi) const
{
    if (n == nullptr)
        return;

    if (n->key >= lo)
        keys_(n->left, v, lo, hi);

    if (n->key >= lo && n->key <= hi)
        v.push_back(n->key);

    if (n->key <= hi)
        keys_(n->right, v, lo, hi);
}

//// ------------------------------------------------------------------------------------------
//// Registry of the union-find algorithms
////
//template <typename T>
//std::map<AlgId, typename TestUnionFind<T>::Alg> TestUnionFind<T>::Algorithms =
//{
//      {AlgId::QUICK_FIND,           std::make_shared<UnionFind_QuickFind<T>>()}
//    , {AlgId::QUICK_UNION,          std::make_shared<UnionFind_QuickUnion<T>>()}
//    , {AlgId::QUICK_UNION_BALANCED, std::make_shared<UnionFind_QuickUnion_Balanced<T>>()}
//};

} // namespace bst

//--------------------------------------------------------------------------------------------------
#endif // BINARY_SEARCH_TREE_HPP
//--------------------------------------------------------------------------------------------------
