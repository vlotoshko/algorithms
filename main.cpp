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
    return runUnitTests() ? 0 : 1;
}

//--------------------------------------------------------------------------------------------------
