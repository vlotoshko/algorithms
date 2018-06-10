//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "TestFactory.hpp"

#include <iostream>
#include <iomanip>
//--------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Repeatedly invokes test doubling the amount of elements for each iteration
//
void runDoubleAmountTest(std::shared_ptr<tests::ITestFactory> builder, tests::TestSettings settings)
{
    tools::CalcRatio calcRatio;

    for (size_t i = 1; i <= settings.repeatTimes; ++i)
    {
        tools::Timer timer;
        auto test = builder->createTest(settings);
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
    tools::Timer timer;

    auto test = builder->createTest(settings);
    test->runTest(timer);

    double time = timer.timeSpent();
    std::cout << std::left
//              << "count: " << std::setw(10) << settings.elementsCount
              << "time eplaced: " << std::setw(10) << time << std::endl;
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

    return 0;
}

//--------------------------------------------------------------------------------------------------
