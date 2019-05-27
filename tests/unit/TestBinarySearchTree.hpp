/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 30-May-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef TESTBINARYSEARCHTREE_HPP
#define TESTBINARYSEARCHTREE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "BinarySearchTree.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace tests
{

/**
 * @class TestBST
 * @brief The TestBST class tests binary search tree.
 */
class TestBST : public CppUnit::TestFixture
{
public:
    /**
     * @brief suite implements implicit intreface for the TestSuiteFactory.
     * @return test suite for the current tests.
     */
    static CppUnit::TestSuite * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestBST");
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "get_ShouldReturnValue_WhenGivenKey",
                                  &TestBST::get_ShouldReturnValue_WhenGivenKey));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "deleteNode_ShouldDeleteNode_WhenGivenKey",
                                  &TestBST::deleteNode_ShouldDeleteNode_WhenGivenKey));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "min_ShouldReturnKeyWithMinimalValue",
                                  &TestBST::min_ShouldReturnKeyWithMinimalValue));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "max_ShouldReturnKeyWithMaximalValue",
                                  &TestBST::max_ShouldReturnKeyWithMaximalValue));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "size_ShouldReturnCountOfNodes",
                                  &TestBST::size_ShouldReturnCountOfNodes));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "valueSum_ShouldReturnSumOfAllvalues",
                                  &TestBST::valueSum_ShouldReturnSumOfAllvalues));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "floor_ShouldReturnFloor_WhengivenKey",
                                  &TestBST::floor_ShouldReturnFloor_WhengivenKey));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "ceiling_ShouldReturnCeiling_WhengivenKey",
                                  &TestBST::ceiling_ShouldReturnCeiling_WhengivenKey));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "select_ShouldReturnKey_WhenGivenRank",
                                  &TestBST::select_ShouldReturnKey_WhenGivenRank));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestBST>(
                                  "rank_ShouldReturnRank_WhenGivenKey",
                                  &TestBST::rank_ShouldReturnRank_WhenGivenKey));
        return suiteOfTests;
    }

    /**
     * @brief setUp sets up initial BST
     */
    void setUp()
    {
        bst.put("word", 0);
        bst.put("select", 0);
        bst.put("connect", 0);
        bst.put("car", 0);
        bst.put("car", 0);
        bst.put("cat", 0);
        bst.put("android", 0);
        bst.put("word", 0);
    }

protected:
    /**
     * @brief get_ShouldReturnValue_WhenGivenKey tests returning correct value.
     */
    void get_ShouldReturnValue_WhenGivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), bst.get("word"));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), bst.get("select"));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), bst.get("zero"));
    }

    /**
     * @brief deleteNode_ShouldDeleteNode_WhenGivenKey tests deleting correct value.
     */
    void deleteNode_ShouldDeleteNode_WhenGivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), bst.get("car"));
        bst.deleteNode("car");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), bst.get("car"));
    }

    /**
     * @brief min_ShouldReturnKeyWithMinimalValue tests returning minimal value.
     */
    void min_ShouldReturnKeyWithMinimalValue()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("android"), bst.min());
    }

    /**
     * @brief max_ShouldReturnKeyWithMaximalValue tests returning maximal element.
     */
    void max_ShouldReturnKeyWithMaximalValue()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("word"), bst.max());
    }

    /**
     * @brief size_ShouldReturnCountOfNodes tests returning correct size of tree.
     */
    void size_ShouldReturnCountOfNodes()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), bst.size());
        bst.deleteNode("car");
        bst.deleteNode("select");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), bst.size());
    }

    /**
     * @brief valueSum_ShouldReturnSumOfAllvalues tests returning sum of all elements.
     */
    void valueSum_ShouldReturnSumOfAllvalues()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), bst.valueSum());
        bst.deleteNode("car");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), bst.valueSum());
        bst.deleteNode("select");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), bst.valueSum());
    }

    /**
     * @brief floor_ShouldReturnFloor_WhengivenKey tests returning correct floor element.
     */
    void floor_ShouldReturnFloor_WhengivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("connect"), bst.floor("cow"));
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("android"), bst.floor("ara"));
    }

    /**
     * @brief ceiling_ShouldReturnCeiling_WhengivenKey tests returning correct ceinig element.
     */
    void ceiling_ShouldReturnCeiling_WhengivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("select"), bst.ceiling("flower"));
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("word"), bst.ceiling("star"));
    }

    /**
     * @brief select_ShouldReturnKey_WhenGivenRank tests returning element of the correct rank.
     */
    void select_ShouldReturnKey_WhenGivenRank()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("connect"), bst.select(3));
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("android"), bst.select(0));
    }

    /**
     * @brief rank_ShouldReturnRank_WhenGivenKey tests returning correct rank of the element.
     */
    void rank_ShouldReturnRank_WhenGivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), bst.rank("cat"));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), bst.rank("word"));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), bst.rank("android"));
    }
private:
    bst::BinarySearchTree<std::string, size_t> bst;
};


} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // TESTBINARYSEARCHTREE_HPP
//--------------------------------------------------------------------------------------------------
