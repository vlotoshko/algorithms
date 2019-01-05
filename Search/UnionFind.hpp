//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   28-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef UNIONFIND_HPP
#define UNIONFIND_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <vector>
#include <string>
//--------------------------------------------------------------------------------------------------

namespace uf
{

// ------------------------------------------------------------------------------------------
// Union-find algorithms allow to find connections between two elements, connected direclty
// or indirectly (by some other elements). Connections are set as an array of connected pairs.
//
template<typename T>
struct UnionFindInfo
{
    explicit UnionFindInfo(size_t count)
        : elements(count), clasters(count+1), unionInvokes(0), findInvokes(0), sizes(count, 1)
    {
        int inc = 0;
        for (auto & item : elements)
        {
            item = inc++;
        }
    }

    std::vector<T>      elements;
    size_t              clasters;
    size_t              unionInvokes;
    size_t              findInvokes;
    std::vector<size_t> sizes; // used only by UnionFind_QuickUnion_Balanced
};

template <typename T>
class UnionFind
{
public:
    /*! \brief Unions 2 clusters of given components into one
     *  \param UnionFind structure to union
     *  \param component(node) 1 of the UnionFind structure
     *  \param component(node) 2 of the UnionFind structure
     */
    void unionComponents(UnionFindInfo<T> & ufData, T p, T q)
    {
        ++ufData.unionInvokes;
        if (union_(ufData, p, q))
        {
            --ufData.clasters;
        }
    }

    /*! \brief Returns claster ID of a given component
     *  \param UnionFind structure to search in
     *  \param component(node) of the UnionFind structure
     */
    T find(UnionFindInfo<T> & ufData, T p) const { ufData.findInvokes++; return find_(ufData, p); }

    /*! \brief Returns true if both components belongs to the same claster
     *  \param UnionFind structure to check connection
     *  \param component(node) 1 of the UnionFind structure
     *  \param component(node) 2 of the UnionFind structure
     */
    bool connected(UnionFindInfo<T> & ufData, T p, T q) const {return find(ufData, p) == find(ufData, q); }

    virtual ~UnionFind() = default;
private:
    virtual bool union_(UnionFindInfo<T> & ufData, T p, T q) = 0;
    virtual T find_(UnionFindInfo<T> & ufData, T p) const    = 0;
};


// ------------------------------------------------------------------------------------------
// Quick find / slow union
//
template <typename T>
class UnionFind_QuickFind : public UnionFind<T>
{
public:
    static char const * name;

private:
    bool union_(UnionFindInfo<T> & ufData, T p, T q) override
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

    T find_(UnionFindInfo<T> & ufData, T p) const override
    {
        return ufData.elements[p];
    }
};

template <typename T>
char const * UnionFind_QuickFind<T>::name = "UnionFind/QiuckFind";


// ------------------------------------------------------------------------------------------
// Quick union / slow find
//
template <typename T>
class UnionFind_QuickUnion : public UnionFind<T>
{
public:
    static char const * name;

private:
    bool union_(UnionFindInfo<T> & ufData, T p, T q) override
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

    T find_(UnionFindInfo<T> & ufData, T p) const override
    {
        while (p != ufData.elements[p])
        {
            p = ufData.elements[p];
        }
        return p;
    }
};

template <typename T>
char const * UnionFind_QuickUnion<T>::name = "UnionFind/QiuckUnion";


// ------------------------------------------------------------------------------------------
// Quick union (using balanced tree) / slow find
//
template <typename T>
class UnionFind_QuickUnion_Balanced : public UnionFind<T>
{
public:
    static char const * name;

private:
    bool union_(UnionFindInfo<T> & ufData, T p, T q) override
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

    T find_(UnionFindInfo<T> & ufData, T p) const override
    {
        while (p != ufData.elements[p])
        {
            p = ufData.elements[p];
        }
        return p;
    }
};

template <typename T>
char const * UnionFind_QuickUnion_Balanced<T>::name = "UnionFind/QiuckUnion balanced";


} // namespace unionfind

//--------------------------------------------------------------------------------------------------
#endif // UNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
