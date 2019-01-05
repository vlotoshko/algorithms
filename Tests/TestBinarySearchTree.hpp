//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   30-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTBINARYSEARCHTREE_HPP
#define TESTBINARYSEARCHTREE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ITestable.hpp"
#include "BinarySearchTree.hpp"

#include <fstream>
#include <sstream>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace bst // binary search tree
{

// ------------------------------------------------------------------------------------------
// Fills binary search tree with words from the text file
//
class TestBST2 : public ITestable
{
public:
    TestBST2(const std::string & fileName, size_t /*repeats*/) : fileName_(fileName) {}

    void runTest(tools::Timer & timer) override
    {
        timer.start();

        std::ifstream file;
        file.open (fileName_);
        BinarySearchTree<std::string, int> bst;

        std::string word;
        while (file >> word)
        {
            bst.put(word, 0);
        }

        if (bst.size() > 0)
        {
            std::cout << "size: " << bst.size() << std::endl;
            std::cout << "count: " << bst.valueSum() << std::endl;
            std::cout << "min: " << bst.min() << std::endl;
            std::cout << "max: " << bst.max() << std::endl;
//                std::string key;
//                std::cin >> key;
//                std::cout << "floor: " << bst.floor(key) << std::endl;
//                std::cout << "ceiling: " << bst.ceiling(key) << std::endl;
//                std::cout << "select: " << bst.select(1) << std::endl;
//                std::cout << "rank \"love\": " << bst.rank("memory") << std::endl;
//                bst.deleteNode("love");
//                std::cout << "rank \"love\": " << bst.rank("memory") << std::endl;
//                bst.put("love", 0);
//                bst.print();
//                std::cout << std::endl;

//                auto v = bst.keys("f", "m");
//                for (auto e : v)
//                {
//                    std::cout << e << " ";
//                }
//                std::cout << std::endl;
        }
    }

private:
    std::string fileName_;
};


} // namespace binary search tree

namespace tests
{

class TestBST : public CppUnit::TestFixture
{
public:
    static CppUnit::Test * suite()
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
    void get_ShouldReturnValue_WhenGivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), bst.get("word"));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), bst.get("select"));
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), bst.get("zero"));
    }

    void deleteNode_ShouldDeleteNode_WhenGivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), bst.get("car"));
        bst.deleteNode("car");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(0), bst.get("car"));
    }

    void min_ShouldReturnKeyWithMinimalValue()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("android"), bst.min());
    }

    void max_ShouldReturnKeyWithMaximalValue()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("word"), bst.max());
    }

    void size_ShouldReturnCountOfNodes()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), bst.size());
        bst.deleteNode("car");
        bst.deleteNode("select");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(4), bst.size());
    }

    void valueSum_ShouldReturnSumOfAllvalues()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(8), bst.valueSum());
        bst.deleteNode("car");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), bst.valueSum());
        bst.deleteNode("select");
        CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(5), bst.valueSum());
    }

    void floor_ShouldReturnFloor_WhengivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("connect"), bst.floor("cow"));
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("android"), bst.floor("ara"));
    }

    void ceiling_ShouldReturnCeiling_WhengivenKey()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("select"), bst.ceiling("flower"));
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("word"), bst.ceiling("star"));
    }

    void select_ShouldReturnKey_WhenGivenRank()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("connect"), bst.select(3));
        CPPUNIT_ASSERT_EQUAL(static_cast<std::string>("android"), bst.select(0));
    }

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
