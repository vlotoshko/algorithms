/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#include "TestSort.hpp"
#include "TestUnionFind.hpp"
#include "TestBinarySearchTree.hpp"
#include "TestGraph.hpp"
#include "CustomListeners.hpp"

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

//--------------------------------------------------------------------------------------------------

void registerUnitTests()
{
    using namespace tests;
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestIsSorted<size_t>);

    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestDummySort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestBubleSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestCombSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestShakeSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestQuickSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestQuickSortM<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestQuick3Sort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestGnomeSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestSelectionSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestHeapSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestInsertionySort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestMergeSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestMergeUpSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestQuickInsSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestMergeInsSort<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestInsertionBinarySort<size_t>);

    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestUnionFind_QuickFind<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TesUnionFind_QuickUnion<size_t>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestUnionFind_QuickUnion_Balanced<size_t>);

    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestBST);

    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestGraph<graph::Graph>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestSymbolGraph);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestMinimalSpanningTree<graph::PrimMST_Lazy>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestMinimalSpanningTree<graph::PrimMST_Energy>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestMinimalSpanningTree<graph::KruskalMST>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestShortPahes<graph::DijkstraSP>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestShortPahes<graph::AcyclicShortPaths>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestShortPahes<graph::AcyclicLongPaths>);
    CPPUNIT_TEST_SUITE_REGISTRATION(tests::TestCriticalPathMethod);
}

bool runUnitTests()
{
    CppUnit::TestResult testResults;
    CppUnit::TestResultCollector collectedResult;
    testResults.addListener(&collectedResult);

    tests::ShowStartListener showStart;
    testResults.addListener(&showStart);

    tests::ShowEndListener showEnd;
    testResults.addListener(&showEnd);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();

    CppUnit::TestRunner runner;
    runner.addTest(registry.makeTest());
    runner.run(testResults);

    CppUnit::CompilerOutputter compileroutputter(&collectedResult, std::cerr);
    compileroutputter.write();
    return collectedResult.wasSuccessful();
}

int main(/*int argc, char *argv[]*/)
{
    registerUnitTests();
    return runUnitTests() ? 0 : 1;
}

//--------------------------------------------------------------------------------------------------
