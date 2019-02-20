/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 02-Jun-2018
 */

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

/**
 * @struct ObjectCounter
 * @brief The ObjectCounter struct counts constructed and destroyed objects.
 */
struct ObjectCounter
{
    ObjectCounter()  { std::cout << "{=} <<< exists " << ++count << std::endl; }
    ~ObjectCounter() { std::cout << "{=} >>> left "   << --count << std::endl; }
    /// count of created objects
    static size_t count;
};

size_t ObjectCounter::count = 0;

/**
 * @class BinarySearchTree
 * @brief The UnionFind template class is the base class for all UnionFind classes.
 * @tparam Key key type of the tree
 * @tparam Value value type of the tree
 */
template<typename Key, typename Value>
class BinarySearchTree
{
public:
    /**
     * @brief The BinarySearchTree constructor. Default.
     */
    BinarySearchTree() : root_(nullptr) {}
    ~BinarySearchTree() { clear_(root_); }

    /**
     * @brief put Puts new element into the tree.
     * @param[in] k key
     * @param[in] v value
     */
    void put(Key k, Value v) { root_ = put_(root_, k, v); }

    /**
     * @brief Gets element from the tree.
     * @param[in] k key of the element
     * @return value of the element.
     */
    Value get(Key k) const { return get_(root_, k); }

    /**
     * @brief Deletes element with the given key.
     * @param[in] k key of the element
     */
    void deleteNode(Key k) { root_ = deleteNode_(root_, k); }

    /**
     * @brief Defines mininal key in the tree.
     * @return minimal key.
     */
    Key min() const { return min_(root_)->key; }

    /**
     * @brief Defines maxinmal key in the tree.
     * @return maxinmal key.
     */
    Key max() const { return max_(root_)->key; }

    /**
     * @brief size Defines size of the tree.
     * @return size of the tree.
     */
    size_t size() const { return size_(root_); }

    /**
     * @brief isEmpty Defines whether tree is empty.
     * @return true if tree is empty.
     */
    bool isEmpty() const { return size() != 0; }

    /**
     * @brief valueSum Calculates sum of all elements in the tree.
     * @return sum of all elements in the tree.
     */
    Value valueSum() const { return valueSum_(root_); }

    /**
     * @brief Gets nearest element smaller then given.
     * @param[in] k key of the element
     * @return nearest element smaller then given.
     */
    Key floor(Key k)  const { Node * n = floor_(root_, k); return n ? n->key : nullptr; }

    /**
     * @brief Gets nearest element bigger then given.
     * @param[in] k key of the element
     * @return nearest element bigger then given.
     */
    Key ceiling(Key k) const { Node * n = ceiling_(root_, k); return n ? n->key : nullptr; }

    /**
     * @brief Gets the element by its rank.
     * @param[in] r key of the element
     * @return the element by its rank.
     *
     * Rank - the count of elements less then given.
     */
    Key select(size_t r) const { Node * n = select_(root_, r); return n ? n->key : nullptr; }

    /**
     * @brief Gets the rank of the element.
     * @param[in] k key of the element
     * @return the rank of the element.
     *
     * Rank - the count of elements less then given.
     */
    size_t rank(Key k)  const { return rank_(root_, k); }

    /**
     * @brief Prints all elements fo the tree.
     */
    void print() const { print_(root_); }

    /**
     * @brief Gets sorted keys within lo-hi interval.
     * @param[in] lo low boundary of the inveral
     * @param[in] hi high boundary of the interval
     * @return sorted keys within lo-hi interval.
     */
    std::vector<Key> keys (Key lo, Key hi) const;

    /**
     * @brief Returns all keys sorted.
     * @return all keys, sorted.
     */
    std::vector<Key> keys() const { return keys_(min(), max()); }

private:
    struct Node //: public ObjectCounter
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
    Node*  select_(Node * n, size_t k) const;
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
//        return static_cast<Value>(nullptr);
        return 0;

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
        n = min_(t->right);
        n->right = forgetMin_(t->right);
        n->left = t->left;
        delete t;
    }

    n->size = size_(n->left) + size_(n->right) + 1;
    return n;
}

template< typename Key, typename Value >
void BinarySearchTree<Key, Value>::clear_(Node * n)
{
    if (n == nullptr)
        return;

    if (n->left)
        clear_(n->left);
    if (n->right)
        clear_(n->right);

    delete n;
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
    return n ? n->size : 0;
}

template<typename Key, typename Value>
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::forgetMin_(Node * n) \
{
    if (n->left == nullptr)
        return n->right;

    n->left = forgetMin_(n->left);
    n->size = size_(n->left) + size_(n->right) + 1;
    return n;
}

template<typename Key, typename Value>
Value BinarySearchTree<Key, Value>::valueSum_(Node * n) const
{
    if (n == nullptr)
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
typename BinarySearchTree<Key, Value>::Node* BinarySearchTree<Key, Value>::select_(Node * n, size_t k) const
{
    if (n == nullptr)
        return nullptr;

    size_t t = size_(n->left);

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
    if (n == nullptr)
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
    if (n == nullptr)
        return;

    print_(n->left);
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

} // namespace bst

//--------------------------------------------------------------------------------------------------
#endif // BINARY_SEARCH_TREE_HPP
//--------------------------------------------------------------------------------------------------
