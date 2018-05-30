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
//--------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------

template <typename T>
class UnionFind
{
public:
    UnionFind(unsigned count) : elements_(count), clasters_(count+1)
    {
        int inc = 0;
        for (auto & item : elements_)
        {
            item = inc++;
        }
    }

    void unionComponents(T p, T q)
    {
        if (union_(p, q))
        {
            clasters_--;
        }
    }

    int find(T p) const { return find_(p); }
    bool connected(T p, T q) const {return find(p) == find(q); }
protected:
    virtual bool union_(T p, T q) = 0;
    virtual T find_(T p) const = 0;
    std::vector<T> elements_;
    unsigned clasters_;
};


// ------------------------------------------------------------------------------------------
// Quick find / slow union
//
template <typename T>
class UnionFind_QuickFind : public UnionFind<T>
{
public:
    UnionFind_QuickFind(unsigned count) : UnionFind<T>(count) {}

private:
    bool union_(T p, T q) override
    {
        auto pId = UnionFind<T>::find(p);
        auto qId = UnionFind<T>::find(q);
        if (pId != qId)
        {
            for (auto & item : UnionFind<T>::elements_)
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

    T find_(T p) const override
    {
        return UnionFind<T>::elements_[p];
    }
};

// ------------------------------------------------------------------------------------------
// Quick union / slow find
//
template <typename T>
class UnionFind_QuickUnion : public UnionFind<T>
{
public:
    UnionFind_QuickUnion(unsigned count) : UnionFind<T>(count) {}

private:
    bool union_(T p, T q) override
    {
        auto pId = UnionFind<T>::find(p);
        auto qId = UnionFind<T>::find(q);
        if (pId != qId)
        {
            UnionFind<T>::elements_[qId] = pId;
            return true;
        }
        return false;
    }

    T find_(T p) const override
    {
        while (p != UnionFind<T>::elements_[p])
        {
            p = UnionFind<T>::elements_[p];
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
    UnionFind_QuickUnion_Balanced(unsigned count) : UnionFind<T>(count), sizes_(count)
    {
        for (auto & item : sizes_)
        {
            item = 1;
        }
    }

private:
    bool union_(T p, T q) override
    {
        auto pId = UnionFind<T>::find(p);
        auto qId = UnionFind<T>::find(q);
        if (pId != qId)
        {
            if (sizes_[pId] < sizes_[qId])
            {
                UnionFind<T>::elements_[pId] = qId;
                sizes_[qId] += sizes_[pId];
            }
            else
            {
                UnionFind<T>::elements_[qId] = pId;
                sizes_[pId] += sizes_[qId];
            }
            return true;
        }
        return false;
    }

    T find_(T p) const override
    {
        while (p != UnionFind<T>::elements_[p])
        {
            p = UnionFind<T>::elements_[p];
        }
        return p;
    }
    std::vector<unsigned> sizes_;
};


//--------------------------------------------------------------------------------------------------
#endif // UNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
