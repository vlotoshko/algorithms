//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestFactory.hpp"

#include <iostream>
#include <iomanip>

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

#include "CustomListeners.hpp"
//--------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Repeatedly invokes test doubling the amount of elements for each iteration
//
void runDoubleAmountTest(std::shared_ptr<tests::ITestFactory> builder, tests::TestSettings settings)
{
    tools::CalcRatio calcRatio;

    for (size_t i = 1; i <= settings.repeatTimes; ++i)
    {
        auto test = builder->createTest(settings);

        tools::Timer timer;
        test->runTest(timer);
        double time = timer.timeSpent();

        std::cout << std::left
                  << "count: " << std::setw(10) << settings.elementsCount << "time eplaced: " << std::setw(10)
                  << time << "ratio: " << calcRatio.getRatio(time) << std::endl;

        // Double elements count before next test
        settings.elementsCount += settings.elementsCount;
    }
}

void runTest(std::shared_ptr<tests::ITestFactory> builder, tests::TestSettings settings)
{
    auto test = builder->createTest(settings);

    tools::Timer timer;
    test->runTest(timer);

    double time = timer.timeSpent();
    std::cout << std::left
//              << "count: " << std::setw(10) << settings.elementsCount
              << "time eplaced: " << std::setw(10) << time << std::endl;
}


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

int main(int argc, char *argv[])
{
    auto settings = registry::getSettings(argc, argv);
    auto builder = tests::getTestBuilder<int>(settings.algId);

    if (registry::algorithmExists<int>(settings.algId) && builder)
    {
        if (settings.repeatTimes > 0)
        {
            runDoubleAmountTest(builder, settings);
        }
        else
        {
            runTest(builder, settings);
        }
    }
    else
    {
        tests::TestSettings::usage();
    }

    registerUnitTests();
    return runUnitTests() ? 0 : 1;
}

//--------------------------------------------------------------------------------------------------
