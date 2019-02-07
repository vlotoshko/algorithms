/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 28-May-2018
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
 * @struct UnionFindInfo
 * @brief The UnionFindInfo template struct holds information how elements are connected
 * one with other.
 */
template<typename T>
struct UnionFindInfo
{
    /**
     * @brief UnionFindInfo constructor inits data with initial values.
     * @param[in] count count of the elements
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
 * @class UnionFind
 * @brief The UnionFind template class is the base class for all UnionFind classes.
 *
 * The UnionFind template class is the base class for all UnionFind classes.
 * It uses NVI-technique to provide polymorphism
 */
template <typename T>
class UnionFind
{
public:
    /**
     * @brief Unions two clusters of given components into one if they were not connected before.
     * Decreases clasters count by 1.
     * @param[out] ufDate UnionFindInfo structure to union
     * @param[in] p component 1 of the UnionFindInfo structure
     * @param[in] q component 2 of the UnionFindInfo structure
     *
     */
    void unionComponents(UnionFindInfo<T> & ufData, const T & p, const T & q)
    {
        ++ufData.unionInvokes;
        if (union_(ufData, p, q))
        {
            --ufData.clasters;
        }
    }

    /**
     * @brief Finds claster ID of a given component.
     * @param[in] ufDate UnionFindInfo structure to search in
     * @param[in] p component of the UnionFindInfo structure
     * @returns claster ID of a given component.
     */
    T find(const UnionFindInfo<T> & ufData, const T & p) { ufData.findInvokes++; return find_(ufData, p); }

    /**
     * @brief Checks wether two components belongs to the same claster, i.e. connected.
     * @param[in] ufData UnionFindInfo structure to check connection
     * @param[in] p component 1 of the UnionFindInfo structure
     * @param[in] q component 2 of the UnionFindInfo structure
     * @returns true if components are connected.
     */
    bool connected(const UnionFindInfo<T> & ufData,const T & p, const T & q) {return find(ufData, p) == find(ufData, q); }

    /// default virtual constructor for the base polymorphic class
    virtual ~UnionFind() = default;
private:
    /// pure virtual method to redefine union implementation
    virtual bool union_(UnionFindInfo<T> & ufData, const T & p, const T & q) = 0;

    /// pure virtual method to redefine find implementation
    virtual T find_(const UnionFindInfo<T> & ufData, T p) = 0;
};


/**
 * @class UnionFind_QuickFind
 * @brief The UnionFind_QuickFind template class implements 'quick find / slow union'
 * strategy
 */
template <typename T>
class UnionFind_QuickFind : public UnionFind<T>
{
public:
    /// class name
    static char const * name;

private:
    /**
     * @brief Unions two clusters of two components into one if they were not connected before.
     * @param[out] ufData  UnionFindInfo structure to union
     * @param[in] p component 1 of the UnionFindInfo structure
     * @param[in] q component 2 of the UnionFindInfo structure
     * @returns true if not connected components become connected.
     *
     * Assings cluster ID of the firts component to the second component, also assings this ID
     * claster to all compomemts connected with the second component.
     */
    bool union_(UnionFindInfo<T> & ufData, const T & p, const T & q) override;

    /**
     * @brief Finds claster ID of a given component.
     * @param[in] ufData UnionFindInfo structure to search in
     * @param[in] p component 1 of the UnionFindInfo structure
     * @returns claster ID of a given component.
     */
    T find_(const UnionFindInfo<T> & ufData, T p) override { return ufData.elements[p]; }
};


/**
 * @class UnionFind_QuickUnion
 * @brief The UnionFind_QuickUnion template class implements 'quick union / slow find'
 * strategy
 */
template <typename T>
class UnionFind_QuickUnion : public UnionFind<T>
{
public:
    /// class name
    static char const * name;

private:
    /**
     * @brief Unions two clusters of two components into one if they were not connected before.
     * @param[out] ufData UnionFindInfo structure to union
     * @param[in] p component 1 of the UnionFindInfo structure
     * @param[in] q component 2 of the UnionFindInfo structure
     * @returns true if not connected components become connected.
     *
     * Assings cluster ID of the firts component to the second component. Thus such IDs
     * forms a tree of connection.
     */
    bool union_(UnionFindInfo<T> & ufData, const T & p, const T & q) override;

    /**
     * @brief Finds claster ID of a given component.
     * @param[in] ufData UnionFindInfo structure to search in
     * @param[in] p component of the UnionFind structure
     * @returns claster ID of a given component.
     *
     * Finds claster ID from the root of the 'tree of connection'. It will be the
     * claster ID of the tree.
     */
    T find_(const UnionFindInfo<T> & ufData, T p) override;
};


/**
 * @class UnionFind_QuickUnion_Balanced
 * @brief The UnionFind_QuickUnion_Balanced template class implements 'quick union /
 * slow find' strategy and uses additional data to generate balanced tree of connections.
 */
template <typename T>
class UnionFind_QuickUnion_Balanced : public UnionFind<T>
{
public:
    /// class name
    static char const * name;

private:
    /**
     * @brief Unions two clusters of two components into one if they were not connected before.
     * @param[out] ufData UnionFindInfo structure to union
     * @param[in] p component 1 of the UnionFindInfo structure
     * @param[in] q component 2 of the UnionFindInfo structure
     * @returns true if not connected components become connected.
     *
     * Assings cluster ID of the firts component to the second component. Thus such IDs
     * forms a balanced tree of connections.
     */
    bool union_(UnionFindInfo<T> & ufData,const T & p, const T & q) override;

    /**
     * @brief Finds claster ID of a given component.
     * @param[in] ufData UnionFindInfo structure to search in
     * @param[in] p component of the UnionFind structure
     * @returns claster ID of a given component.
     *
     * Finds claster ID from the root of the 'tree of connection'. It will be the
     * claster ID of the tree.
     */
    T find_(const UnionFindInfo<T> & ufData, T p) override;
};



// -------------------------------------------------------------------------------
// ---------------- Template classes definitions ---------------------------------
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
bool UnionFind_QuickFind<T>::union_(UnionFindInfo<T> & ufData, const T & p, const T & q)
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
bool UnionFind_QuickUnion<T>::union_(UnionFindInfo<T> & ufData, const T & p, const T & q)
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
// ----- UnionFind_QuickUnion_Balanced -----
//

template <typename T>
bool UnionFind_QuickUnion_Balanced<T>::union_(UnionFindInfo<T> & ufData, const T & p, const T & q)
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
