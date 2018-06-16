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
    UnionFindInfo(size_t count)
        : elements(count), clasters(count+1), unionInvokes(0), findInvokes(0)
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
    void unionComponents(UnionFindInfo<T> & ufData, T p, T q)
    {
        ufData.unionInvokes++;
        if (union_(ufData, p, q))
        {
            ufData.clasters--;
        }
    }

    int find(UnionFindInfo<T> & ufData, T p) const { ufData.findInvokes++; return find_(ufData, p); }
    bool connected(UnionFindInfo<T> & ufData, T p, T q) const {return find(ufData, p) == find(ufData, q); }

    virtual std::string name() const = 0;
protected:
    virtual bool union_(UnionFindInfo<T> & ufData, T p, T q) = 0;
    virtual T find_(UnionFindInfo<T> & ufData, T p) const = 0;

private:

};


// ------------------------------------------------------------------------------------------
// Quick find / slow union
//
template <typename T>
class UnionFind_QuickFind : public UnionFind<T>
{
public:
    std::string name() const { return "UnionFind / QiuckFind"; }

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


// ------------------------------------------------------------------------------------------
// Quick union / slow find
//
template <typename T>
class UnionFind_QuickUnion : public UnionFind<T>
{
public:
    std::string name() const { return "UnionFind / QiuckUnion"; }

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


// ------------------------------------------------------------------------------------------
// Quick union (using balanced tree) / slow find
//
template <typename T>
class UnionFind_QuickUnion_Balanced : public UnionFind<T>
{
public:
    std::string name() const { return "UnionFind / QiuckUnion balanced"; }

private:
    bool union_(UnionFindInfo<T> & ufData, T p, T q) override
    {
        if (ufData.sizes.size() < ufData.elements.size())
        {
            return false;
        }
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

} // namespace unionfind

//--------------------------------------------------------------------------------------------------
#endif // UNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
