/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 23-Feb-2019
 */

//--------------------------------------------------------------------------------------------------
#ifndef BENCHMARKS_HPP
#define BENCHMARKS_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "BmSort.hpp"

#include "../unit/CustomListeners.hpp"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
//--------------------------------------------------------------------------------------------------

namespace tests
{

void registerBenchmarks()
{
    CPPUNIT_TEST_SUITE_NAMED_REGISTRATION(benchmark::BmSort, "Benchmarks");
}

bool runBenchmarks()
{
    CppUnit::TestResult testResults;
    CppUnit::TestResultCollector collectedResult;
    testResults.addListener(&collectedResult);

    tests::ShowStartListener showStart;
    testResults.addListener(&showStart);

    tests::ShowEndListener showEnd;
    testResults.addListener(&showEnd);

    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("Benchmarks");

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
int launchBenchmarks()
{
    registerBenchmarks();
    return runBenchmarks() ? 0 : 1;
}



}// namespace tests

//--------------------------------------------------------------------------------------------------
#endif // BENCHMARKS_HPP
//--------------------------------------------------------------------------------------------------
