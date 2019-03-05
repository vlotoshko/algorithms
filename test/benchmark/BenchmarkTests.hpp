/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 23-Feb-2019
 */

//--------------------------------------------------------------------------------------------------
#ifndef BENCHMARK_TESTS_HPP
#define BENCHMARK_TESTS_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestUnionFind.hpp"
#include "CustomListeners.hpp"

#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
//--------------------------------------------------------------------------------------------------

namespace tests
{


void registerBenchmarkTests()
{
    CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(tests::TestUnionFind_QuickFind<size_t>, "Benchmark Tests");
    CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(tests::TestUnionFind_QuickUnion<size_t>, "Benchmark Tests");
    CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(tests::TestUnionFind_QuickUnion_Balanced<size_t>, "Benchmark Tests");
}

bool runBenchmarkTests()
{
    CppUnit::TestResult testResults;
    CppUnit::TestResultCollector collectedResult;
    testResults.addListener(&collectedResult);

    tests::ShowStartListener showStart;
    testResults.addListener(&showStart);

    tests::ShowEndListener showEnd;
    testResults.addListener(&showEnd);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("Benchmark Tests");

    CppUnit::TestRunner runner;
    runner.addTest(registry.makeTest());
    runner.run(testResults);

    CppUnit::CompilerOutputter compileroutputter(&collectedResult, std::cerr);
    compileroutputter.write();
    return collectedResult.wasSuccessful();
}


/**
 * @brief launchBenchmarkTests registers and runs unit tests.
 * @return zero if all tests are passed else 1.
 */
int launchBenchmarkTests()
{
    registerBenchmarkTests();
    return runBenchmarkTests() ? 0 : 1;
}



}// namespace tests

//--------------------------------------------------------------------------------------------------
#endif // BENCHMARK_TESTS_HPP
//--------------------------------------------------------------------------------------------------
