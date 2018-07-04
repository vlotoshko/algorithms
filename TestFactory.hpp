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
#include "TestSort.hpp"
#include "TestUnionFind.hpp"
#include "TestBinarySearchTree.hpp"
#include "TestGraph.hpp"
#include "TestRegistry.hpp"

#include <map>
#include <memory>
//--------------------------------------------------------------------------------------------------

namespace tests
{

using TestSettings = registry::TestSettings;
using AlgCategory = registry::AlgCategory;

// ------------------------------------------------------------------------------------------
struct ITestFactory
{
    using   Test = std::shared_ptr<ITestable>;
    virtual Test createTest(const TestSettings parameters) = 0;
    virtual      ~ITestFactory()                                              = default;
};

template <typename T>
struct SortTestBuilder : public ITestFactory
{
    Test createTest(const TestSettings parameters) override
    {
        return std::make_shared<sort::TestSort<T>>(static_cast<sort::AlgId>(parameters.algId), parameters.elementsCount);
    }
};

template <typename T>
struct UnionFindTestBuilder : public ITestFactory
{
    Test createTest(const TestSettings parameters) override
    {
        return std::make_shared<uf::TestUnionFind<T>>(static_cast<uf::AlgId>(parameters.algId), parameters.elementsCount);
    }
};

struct BinarySearchTreeTestBuilder : public ITestFactory
{
    Test createTest(const TestSettings parameters) override
    {
        return std::make_shared<bst::TestBST>(parameters.fileName, 0);
    }
};

struct GraphTestBuilder : public ITestFactory
{
    Test createTest(const TestSettings parameters) override
    {
        return std::make_shared<graph::TestGraph>(parameters.algId, parameters.fileName);
    }
};

template <typename T>
static std::map<AlgCategory, std::shared_ptr<ITestFactory>> testBuilders =
{
    {AlgCategory::SORT,               std::make_shared<SortTestBuilder<T>>()}
  , {AlgCategory::UNION_FIND,         std::make_shared<UnionFindTestBuilder<T>>()}
  , {AlgCategory::BINARY_SEARCH_TREE, std::make_shared<BinarySearchTreeTestBuilder>()}
  , {AlgCategory::GRAPH,              std::make_shared<GraphTestBuilder>()}
};

template <typename T>
static std::shared_ptr<ITestFactory> getTestBuilder(size_t id)
{
    auto iter = testBuilders<T>.find(registry::getAlgCategory(id));
    if (iter != testBuilders<T>.end())
    {
        return iter->second;
    }
    return std::shared_ptr<ITestFactory>();
}

} // namespace tests
//--------------------------------------------------------------------------------------------------
#endif // TESTFACTORY_HPP
//--------------------------------------------------------------------------------------------------
