//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   01-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTFACTORY_HPP
#define TESTFACTORY_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort/TestSort.hpp"
#include "Search/TestUnionFind.hpp"
#include "tools.hpp"

#include <map>
#include <memory>
//--------------------------------------------------------------------------------------------------

namespace tests
{




enum class AlgCategoty : int
{
    SORT = 0,
    UNION_FIND,
    BINARY_SEARCH_TREE,
    GRAPH,
    UNKNOWN,
};

AlgCategoty getAlgCategory(unsigned id)
{
    if (id < 100)     // range [0, 100)
    {
        return AlgCategoty::SORT;
    }
    else if(id < 200) // range [100, 200)
    {
        return AlgCategoty::UNION_FIND;
    }
    else if(id < 300) // range [200, 300)
    {
        return AlgCategoty::BINARY_SEARCH_TREE;
    }
    else if(id < 400) // range [300, 400)
    {
        return AlgCategoty::GRAPH;
    }

    return AlgCategoty::UNKNOWN;
}



// ------------------------------------------------------------------------------------------
struct ITestFactory
{
    using   Test = std::shared_ptr<ITestable>;
    virtual Test createTest(const tools::InputParameters parameters, unsigned count) = 0;
    virtual      ~ITestFactory()                                              = default;
};

template <typename T>
struct SortTestBuilder : public ITestFactory
{
    Test createTest(const tools::InputParameters parameters, unsigned count) override
    {
        return std::make_shared<sort::TestSort<T>>(static_cast<sort::AlgId>(parameters.algId), count);
    }
};


template <typename T>
struct UnionFindTestBuilder : public ITestFactory
{
    Test createTest(const tools::InputParameters parameters, unsigned count) override
    {
        return std::make_shared<uf::TestUnionFind<T>>(static_cast<uf::AlgId>(parameters.algId), count);
    }
};


template <typename T>
struct Registry
{
    static std::shared_ptr<ITestFactory> getBuilder(unsigned id)
    {
        auto iter = testBuilders.find(getAlgCategory(id));
        if(iter != testBuilders.end())
        {
            return iter->second;
        }
        else
        {
            return std::shared_ptr<ITestFactory>();
        }
    }

    static bool algorithmExists(unsigned id)
    {
        auto category = getAlgCategory(id);
        switch (category)
        {
        case AlgCategoty::SORT:
            return sort::TestSort<T>::Algorithms.find(static_cast<sort::AlgId>(id))
                    != sort::TestSort<T>::Algorithms.end();
        case AlgCategoty::UNION_FIND:
            return uf::TestUnionFind<T>::Algorithms.find(static_cast<uf::AlgId>(id))
                    != uf::TestUnionFind<T>::Algorithms.end();
        case AlgCategoty::BINARY_SEARCH_TREE:
        case AlgCategoty::GRAPH:
        case AlgCategoty::UNKNOWN:
            return false;
        }
    }

    static std::map<AlgCategoty, std::shared_ptr<ITestFactory>> testBuilders;
};

template <typename T>
std::map<AlgCategoty, std::shared_ptr<ITestFactory>> Registry<T>::testBuilders =
{
    {AlgCategoty::SORT,       std::make_shared<SortTestBuilder<T>>()}
  , {AlgCategoty::UNION_FIND, std::make_shared<UnionFindTestBuilder<T>>()}
};

} // namespace tests
//--------------------------------------------------------------------------------------------------
#endif // TESTFACTORY_HPP
//--------------------------------------------------------------------------------------------------