/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 02-Jun-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef BST_HELPER_FUNCTIONS_HPP
#define BST_HELPER_FUNCTIONS_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <cmath>
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
 * @brief Gets value by key.
 * @param[in] n root of the tree.
 * @param[in] k key of the node
 * @return node or nullptr.
 */
template<typename Node>
Node* get(Node * n,  typename Node::KeyType k)
{
    if(n == nullptr)
        return nullptr;

    if (k < n->key)
        return get(n->left, k);
    if (k > n->key)
        return get(n->right, k);
    return n;
}

/**
 * @brief Returns node with mininal key.
 * @param[in] n root of the tree.
 * @return node with mininal key.
 */
template<typename Node>
Node* min(Node * n)
{
    if (n->left)
        return min(n->left);
    else
        return n;
}

/**
 * @brief Returns node with maxinmal key.
 * @param[in] n root of the tree
 * @return node with maxinmal key.
 */
template<typename Node>
Node* max(Node * n)
{
    if (n->right)
        return max(n->right);
    else
        return n;
}

/**
 * @brief valueSum Calculates sum of all nodes in the tree.
 * @param[in] n root of the tree
 * @return sum of all nodes in the tree.
 */
template<typename Node>
typename Node::ValueType valueSum(Node * n)
{
    if (n == nullptr)
        return 0;

    typename Node::ValueType i{};
    if (n->left)
        i += valueSum(n->left);
    if (n->right)
        i += valueSum(n->right);

    i += n->val;
    return i;
}

/**
 * @brief Returns nearest node smaller then given.
 * @param[in] n root of the tree
 * @param[in] k key of the node
 * @return nearest node smaller then given.
 */
template<typename Node>
Node* floor(Node * n, typename Node::KeyType k)
{
    if (n == nullptr)
        return nullptr;

    if (n->key == k)
        return n;

    if (n->key > k)
        return floor(n->left, k);

    Node* t = floor(n->right, k);
    return t ? t : n;
}

/**
 * @brief Gets nearest node bigger then given.
 * @param[in] n root of the tree
 * @param[in] k key of the node
 * @return nearest node bigger then given.
 */
template<typename Node>
Node* ceiling(Node * n, typename Node::KeyType k)
{
    if (n == nullptr)
        return nullptr;

    if (n->key == k)
        return n;

    if (n->key < k)
        return ceiling(n->right, k);

    Node* t = ceiling(n->left, k);
    return t ? t : n;
}

/**
 * @brief Gets the node by its rank.
 * @param[in] n root of the tree
 * @param[in] r rank
 * @return the node by its rank.
 *
 * Rank - the count of nodes less then given.
 */
template<typename Node>
Node* select(Node * n, size_t r)
{
    if (n == nullptr)
        return nullptr;

    size_t t = size(n->left);

    if (t > r)
        return select(n->left, r);
    else
        if (t < r)
            return select(n->right, r - t - 1);
        else
            return n;
}

/**
 * @brief Gets the rank of the node.
 * @param[in] n root of the tree
 * @param[in] k key of the node
 * @return the rank of the node.
 *
 * Rank - the count of nodes less then given.
 */
template<typename Node>
size_t rank(Node * n, typename Node::KeyType k)
{
    if (n == nullptr)
        return 0;

    if (k < n->key)
        return rank(n->left, k);
    else
        if (k > n->key)
            return 1 + size(n->left) + rank(n->right, k);
        else
            return size(n->left);
}

/**
 * @brief Returns size of the tree.
 * @param[in] n root of the tree
 * @return size of the tree.
 */
template<typename Node>
size_t size(Node * n)
{
    return n ? n->size : 0;
}

/**
 * @brief Clears the tree.
 * @param[in] n root of the tree
 */
template<typename Node>
void clear(Node * n)
{
    if (n == nullptr)
        return;

    if (n->left)
        clear(n->left);
    if (n->right)
        clear(n->right);

    delete n;
}

/**
 * @brief Prints all keys of the tree into cout.
 * @param[in] n root of the tree
 */
template<typename Node>
void print(Node * n)
{
    if (n == nullptr)
        return;

    print(n->left);
    std::cout << n->key << " ";
    print(n->right);
}

/**
 * @brief Gets sorted keys within lo-hi interval.
 * @param[out] v container for the keys
 * @param[in] lo low boundary of the inveral
 * @param[in] hi high boundary of the interval
 */
template<typename Node>
void keys(Node * n, std::vector<typename Node::Key>& v, typename Node::Key lo, typename Node::Key hi)
{
    if (n == nullptr)
        return;

    if (n->key >= lo)
        keys(n->left, v, lo, hi);

    if (n->key >= lo && n->key <= hi)
        v.push_back(n->key);

    if (n->key <= hi)
        keys(n->right, v, lo, hi);
}

} // namespace bst

//--------------------------------------------------------------------------------------------------
#endif // BST_HELPER_FUNCTIONS_HPP
//--------------------------------------------------------------------------------------------------
