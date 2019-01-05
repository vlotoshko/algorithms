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
            // FIXME: uncomment line below
//            std::cout << unionFind->name() << std::endl;
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

template <template <typename> class UF_Type, typename T>
class TestUnionFind : public CppUnit::TestFixture
{
public:
    static CppUnit::Test * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite(UF_Type<T>::name);
        suiteOfTests->addTest(new CppUnit::TestCaller<TestUnionFind<UF_Type, T>>(
                                  "find_ShouldReturnClusterId_WhenGivenComponent",
                                  &TestUnionFind::find_ShouldReturnClusterId_WhenGivenComponent));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestUnionFind<UF_Type, T>>(
                                  "unionComponents_ShouldConnectComponentsIntoOneCluster",
                                  &TestUnionFind::unionComponents_ShouldConnectComponentsIntoOneCluster));
        return suiteOfTests;
    }

    void setUp()
    {
        uf_Type.unionComponents(ufData, 1, 3);
        uf_Type.unionComponents(ufData, 2, 8);
        uf_Type.unionComponents(ufData, 1, 7);
        uf_Type.unionComponents(ufData, 3, 9);
        uf_Type.unionComponents(ufData, 4, 8);
    }

protected:
    void find_ShouldReturnClusterId_WhenGivenComponent()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<T>(1), uf_Type.find(ufData, 9));
        CPPUNIT_ASSERT_EQUAL(static_cast<T>(4), uf_Type.find(ufData, 2));
        CPPUNIT_ASSERT_EQUAL(static_cast<T>(6), uf_Type.find(ufData, 6));
    }

    void unionComponents_ShouldConnectComponentsIntoOneCluster()
    {
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 1, 3));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 2, 8));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 1, 7));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 3, 9));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 4, 8));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 7, 3));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 4, 2));
    }

private:
    uf::UnionFindInfo<T> ufData{10};
    UF_Type<T> uf_Type;
};

template<>
void TestUnionFind<uf::UnionFind_QuickUnion_Balanced, size_t>::find_ShouldReturnClusterId_WhenGivenComponent()
{
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), uf_Type.find(ufData, 9));
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), uf_Type.find(ufData, 2));
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), uf_Type.find(ufData, 6));
}


// Had to use aliases for the test suite registration, because in this particulat case
// preprocessor does not accept templates with more that 1 parameter
template<typename T> using TestUnionFind_QuickFind           = TestUnionFind<uf::UnionFind_QuickFind, T>;
template<typename T> using TesUnionFind_QuickUnion           = TestUnionFind<uf::UnionFind_QuickUnion, T>;
template<typename T> using TestUnionFind_QuickUnion_Balanced = TestUnionFind<uf::UnionFind_QuickUnion_Balanced, T>;


}// namespace tests

//--------------------------------------------------------------------------------------------------
#endif // TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
