/**
 * -------------------------------------------------------------------------------------------------
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @skype vlotoshko
 * @date 28-May-2018
 * -------------------------------------------------------------------------------------------------
 */

// -------------------------------------------------------------------------------------------------
#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
// -------------------------------------------------------------------------------------------------

namespace uf
{

/**
 * ----------------------------------------------------------------------------------------
 * @struct UnionFindInfo
 * @brief The UnionFindInfo template struct holds information how elements are connected
 * one with other
 * ----------------------------------------------------------------------------------------
 */
template<typename T>
struct UnionFindInfo
{
    /**
     * @brief UnionFindInfo constructor inits data with initial values
     * @param count of the elements
     */
    explicit UnionFindInfo(const size_t & count);

    /// information about elements connections
    std::vector<T> elements;

    /// count of the claster in the elements
    size_t clasters;

    /// count union function invokes
    mutable size_t unionInvokes;

    /// count find function invokes
    mutable size_t findInvokes;

    /// sizes of clasters to which elements belongs
    std::vector<size_t> sizes; // used only by UnionFind_QuickUnion_Balanced
};


/**
 * ----------------------------------------------------------------------------------------
 * @struct UnionFind
 * @brief The UnionFind template class is a base class for all UnionFind classes
 *
 * The UnionFind template class is a base class for all UnionFind classes.
 * It uses NVI-technique to provide polymorphism
 * ----------------------------------------------------------------------------------------
 */
template <typename T>
class UnionFind
{
public:
    /** @brief unions 2 clusters of given components into one
     *  @param UnionFindInfo structure to union
     *  @param component(node) 1 of the UnionFindInfo structure
     *  @param component(node) 2 of the UnionFindInfo structure
     *
     * Unions 2 clusters of given components into one if they were not connected before
     * and decreases clasters count by 1.
     */
    void unionComponents(UnionFindInfo<T> & ufData, T p, T q)
    {
        ++ufData.unionInvokes;
        if (union_(ufData, p, q))
        {
            --ufData.clasters;
        }
    }

    /** @brief finds claster ID of a given component
     *  @param UnionFindInfo structure to search in
     *  @param component(node) of the UnionFindInfo structure
     *  @returns claster ID of a given component
     */
    T find(const UnionFindInfo<T> & ufData, T p) { ufData.findInvokes++; return find_(ufData, p); }

    /** @brief checks wether two components belongs to the same claster, i.e. connected
     *  @param UnionFindInfo structure to check connection
     *  @param component(node) 1 of the UnionFindInfo structure
     *  @param component(node) 2 of the UnionFindInfo structure
     *  @returns true if components are connected
     */
    bool connected(const UnionFindInfo<T> & ufData, T p, T q) {return find(ufData, p) == find(ufData, q); }

    /// default virtual constructor for the base polymorphic class
    virtual ~UnionFind() = default;
private:
    /// pure virtual method to redefine union implementation
    virtual bool union_(UnionFindInfo<T> & ufData, T p, T q) = 0;

    /// pure virtual method to redefine find implementation
    virtual T find_(const UnionFindInfo<T> & ufData, T p) = 0;
};


/**
 * ----------------------------------------------------------------------------------------
 * @struct UnionFind_QuickFind
 * @brief The UnionFind_QuickFind template class implements 'quick find / slow union'
 * strategy
 * ----------------------------------------------------------------------------------------
 */
template <typename T>
class UnionFind_QuickFind : public UnionFind<T>
{
public:
    /// class name
    static char const * name;

private:
    /** @brief unions 2 clusters of two components into one if they were not connected before
     *  @param UnionFindInfo structure to union
     *  @param component(node) 1 of the UnionFindInfo structure
     *  @param component(node) 2 of the UnionFindInfo structure
     *
     * Assings cluster ID of the firts component to the second component, also assings this ID
     * claster to all compomemts connected with the second component.
     */
    bool union_(UnionFindInfo<T> & ufData, T p, T q) override;

    /** @brief finds claster ID of a given component
     *  @param UnionFindInfo structure to search in
     *  @param component(node) of the UnionFind structure
     *  @returns claster ID of a given component
     */
    T find_(const UnionFindInfo<T> & ufData, T p) override { return ufData.elements[p]; }
};


/**
 * ----------------------------------------------------------------------------------------
 * @struct UnionFind_QuickFind
 * @brief The UnionFind_QuickFind template class implements 'quick union / slow find'
 * strategy
 * ----------------------------------------------------------------------------------------
 */
template <typename T>
class UnionFind_QuickUnion : public UnionFind<T>
{
public:
    /// class name
    static char const * name;

private:
    /** @brief unions 2 clusters of two components into one if they were not connected before
     *  @param UnionFindInfo structure to union
     *  @param component(node) 1 of the UnionFindInfo structure
     *  @param component(node) 2 of the UnionFindInfo structure
     *
     * Assings cluster ID of the firts component to the second component. Thus such IDs
     * forms a tree of connection.
     */
    bool union_(UnionFindInfo<T> & ufData, T p, T q);

    /** @brief finds claster ID of a given component
     *  @param UnionFindInfo structure to search in
     *  @param component(node) of the UnionFind structure
     *  @returns claster ID of a given component
     *
     * Finds claster ID from the root of the 'tree of connection'. It will be the
     * claster ID of the tree.
     */
    T find_(const UnionFindInfo<T> & ufData, T p);
};


// ------------------------------------------------------------------------------------------
// Quick union (using balanced tree) / slow find
//

/**
 * ----------------------------------------------------------------------------------------
 * @struct UnionFind_QuickUnion_Balanced
 * @brief The UnionFind_QuickUnion_Balanced template class implements 'quick union /
 * slow find' strategy and uses additional data to generate balanced tree of connection
 * ----------------------------------------------------------------------------------------
 */
template <typename T>
class UnionFind_QuickUnion_Balanced : public UnionFind<T>
{
public:
    /// class name
    static char const * name;

private:
    /** @brief unions 2 clusters of two components into one if they were not connected before
     *  @param UnionFindInfo structure to union
     *  @param component(node) 1 of the UnionFindInfo structure
     *  @param component(node) 2 of the UnionFindInfo structure
     *
     * Assings cluster ID of the firts component to the second component. Thus such IDs
     * forms a balanced tree of connection.
     */
    bool union_(UnionFindInfo<T> & ufData, T p, T q) override;

    /** @brief finds claster ID of a given component
     *  @param UnionFindInfo structure to search in
     *  @param component(node) of the UnionFind structure
     *  @returns claster ID of a given component
     *
     * Finds claster ID from the root of the 'tree of connection'. It will be the
     * claster ID of the tree.
     */
    T find_(const UnionFindInfo<T> & ufData, T p) override;
};



// -------------------------------------------------------------------------------
// Template classes definitions
// -------------------------------------------------------------------------------


// -------------------------------------------------------------------------------
// ----- UnionFindInfo -----
//

template <typename T>
UnionFindInfo<T>::UnionFindInfo(const size_t & count)
    : elements(count), clasters(count+1), unionInvokes(0), findInvokes(0), sizes(count, 1)
{
    int inc = 0;
    for (auto & item : elements)
    {
        item = inc++;
    }
}


// -------------------------------------------------------------------------------
// ----- UnionFind_QuickFind -----
//

template <typename T>
bool UnionFind_QuickFind<T>::union_(UnionFindInfo<T> & ufData, T p, T q)
{
    auto pId = UnionFind<T>::find(ufData, p);
    auto qId = UnionFind<T>::find(ufData, q);
    if (pId != qId)
    {
        for (auto & item : ufData.elements)
        {
            if (item == qId)
            {
                item = pId;
            }
        }
        return true;
    }
    return false;
}

template <typename T>
char const * UnionFind_QuickFind<T>::name = "UnionFind/QiuckFind";


// -------------------------------------------------------------------------------
// ----- UnionFind_QuickUnion -----
//

template <typename T>
bool UnionFind_QuickUnion<T>::union_(UnionFindInfo<T> & ufData, T p, T q)
{
    auto pId = UnionFind<T>::find(ufData, p);
    auto qId = UnionFind<T>::find(ufData, q);
    if (pId != qId)
    {
        ufData.elements[qId] = pId;
        return true;
    }
    return false;
}

template <typename T>
T UnionFind_QuickUnion<T>::find_(const UnionFindInfo<T> & ufData, T p)
{
    while (p != ufData.elements[p])
    {
        p = ufData.elements[p];
    }
    return p;
}

template <typename T>
char const * UnionFind_QuickUnion<T>::name = "UnionFind/QiuckUnion";

// -------------------------------------------------------------------------------
// ----- UnionFind_QuickUnion -----
//

template <typename T>
bool UnionFind_QuickUnion_Balanced<T>::union_(UnionFindInfo<T> & ufData, T p, T q)
{
    auto pId = UnionFind<T>::find(ufData, p);
    auto qId = UnionFind<T>::find(ufData, q);
    if (pId != qId)
    {
        if (ufData.sizes[pId] < ufData.sizes[qId])
        {
            ufData.elements[pId] = qId;
            ufData.sizes[qId] += ufData.sizes[pId];
        }
        else
        {
            ufData.elements[qId] = pId;
            ufData.sizes[pId] += ufData.sizes[qId];
        }
        return true;
    }
    return false;
}

template <typename T>
T UnionFind_QuickUnion_Balanced<T>::find_(const UnionFindInfo<T> & ufData, T p)
{
    while (p != ufData.elements[p])
    {
        p = ufData.elements[p];
    }
    return p;
}

template <typename T>
char const * UnionFind_QuickUnion_Balanced<T>::name = "UnionFind/QiuckUnion balanced";

} // namespace unionfind

// -------------------------------------------------------------------------------------------------
#endif // UNIONFIND_HPP
// -------------------------------------------------------------------------------------------------
