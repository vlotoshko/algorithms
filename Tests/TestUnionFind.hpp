//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   30-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTUNIONFIND_HPP
#define TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <map>
#include <memory>

#include "ITestable.hpp"
#include "UnionFind.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------

namespace uf // unionfind
{

enum class AlgId : int
{
    QUICK_FIND = 100,
    QUICK_UNION,
    QUICK_UNION_BALANCED,
};


// ------------------------------------------------------------------------------------------
// Runs union-find algorithm specified by the algorithm's id
//
template <typename T>
class TestUnionFind : public ITestable
{
public:
    using Alg = std::shared_ptr<UnionFind<T>>;
    TestUnionFind(AlgId algId, size_t count) : algId_(algId), elementsCount_(count) {}

    void runTest(tools::Timer & timer) override
    {
        auto iter = Algorithms.find(algId_);
        if (iter != Algorithms.end())
        {
            UnionFindInfo<T> uf(elementsCount_);

            // Generate pairs
//            std::cout << "generating data... " << std::flush;
            std::vector<std::pair<T, T>> pairs(elementsCount_);
            for (auto & item : pairs)
            {
                item.first  = tools::random<T>(0, static_cast<int>(elementsCount_));
                item.second = tools::random<T>(0, static_cast<int>(elementsCount_));
            }
            if (algId_ == AlgId::QUICK_UNION_BALANCED)
            {
                uf.sizes = std::vector<size_t>(elementsCount_, 1);
            }
//            std::cout << "Ok" << std::endl;1

            auto unionFind = iter->second;
            timer.start();
            for (auto & item : pairs)
            {
                unionFind->unionComponents(uf, item.first, item.second);
            }
            std::cout << unionFind->name() << std::endl;
            std::cout << "clasters: " << uf.clasters
                      << "; invoke find(): " << uf.findInvokes
                      << "; invoke union(): " << uf.unionInvokes
                      << std::endl;
        }
    }

    static std::map<AlgId, Alg> Algorithms;
private:
    AlgId algId_;
    size_t elementsCount_;
};


// ------------------------------------------------------------------------------------------
// Registry of the union-find algorithms
//
template <typename T>
std::map<AlgId, typename TestUnionFind<T>::Alg> TestUnionFind<T>::Algorithms =
{
      {AlgId::QUICK_FIND,           std::make_shared<UnionFind_QuickFind<T>>()}
    , {AlgId::QUICK_UNION,          std::make_shared<UnionFind_QuickUnion<T>>()}
    , {AlgId::QUICK_UNION_BALANCED, std::make_shared<UnionFind_QuickUnion_Balanced<T>>()}
};

} // namespace unionfind

namespace tests
{

template <typename T>
class TestUnionFind : public CppUnit::TestFixture
{
public:
    static CppUnit::Test * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestUnionFind");
        suiteOfTests->addTest(new CppUnit::TestCaller<TestUnionFind<T>>(
                                  "find_ShouldReturnClusterId_WhenGivenComponent",
                                  &TestUnionFind::find_ShouldReturnClusterId_WhenGivenComponent));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestUnionFind<T>>(
                                  "unionComponents_ShouldConnectComponentsIntoOneCluster",
                                  &TestUnionFind::unionComponents_ShouldConnectComponentsIntoOneCluster));
        return suiteOfTests;
    }

    void setUp()
    {
        uf_QuickUnion.unionComponents(ufData, 1, 3);
        uf_QuickUnion.unionComponents(ufData, 2, 8);
        uf_QuickUnion.unionComponents(ufData, 1, 7);
        uf_QuickUnion.unionComponents(ufData, 3, 9);
        uf_QuickUnion.unionComponents(ufData, 4, 8);
    }

protected:
    void find_ShouldReturnClusterId_WhenGivenComponent()
    {
        CPPUNIT_ASSERT_EQUAL(uf_QuickUnion.find(ufData, 9), static_cast<T>(1));
        CPPUNIT_ASSERT_EQUAL(uf_QuickUnion.find(ufData, 2), static_cast<T>(4));
        CPPUNIT_ASSERT_EQUAL(uf_QuickUnion.find(ufData, 6), static_cast<T>(6));
    }

    void unionComponents_ShouldConnectComponentsIntoOneCluster()
    {
        CPPUNIT_ASSERT(uf_QuickUnion.connected(ufData, 1, 3));
        CPPUNIT_ASSERT(uf_QuickUnion.connected(ufData, 2, 8));
        CPPUNIT_ASSERT(uf_QuickUnion.connected(ufData, 1, 7));
        CPPUNIT_ASSERT(uf_QuickUnion.connected(ufData, 3, 9));
        CPPUNIT_ASSERT(uf_QuickUnion.connected(ufData, 4, 8));
        CPPUNIT_ASSERT(uf_QuickUnion.connected(ufData, 7, 3));
    }

private:
    uf::UnionFindInfo<T> ufData{10};
    uf::UnionFind_QuickUnion<T> uf_QuickUnion;
};

CPPUNIT_TEST_SUITE_REGISTRATION(TestUnionFind<size_t>);

}
//--------------------------------------------------------------------------------------------------
#endif // TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
