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
#include "UnionFind.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------

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

    void setUp() override
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
