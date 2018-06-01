//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort/TestSort.hpp"
#include "Search/TestUnionFind.hpp"
#include "TestFactory.hpp"

#include <iostream>
//--------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Repeatedly invokes test doubling the amount of elements for each iteration
//
void doubleAmountTest(const tests::InputParameters parameters)
{
    tools::CalcRatio calcRatio;
    auto count = parameters.elementsCount;
    for (size_t i = 1; i <= parameters.repeatCount; ++i)
    {
        tools::Timer timer;
        auto builder = tests::Registry<int>::getBuilder(parameters.algId);

        if (!builder)
        {
            return;
        }
        auto test = builder->createTest(parameters, count);
        test->runTest(timer);

        double time = timer.timeSpent();
        std::cout << std::left
                  << "count: " << std::setw(10) << count << "time eplaced: " << std::setw(10)
                  << time << "ratio: " << calcRatio.getRatio(time) << std::endl;

        // Double elements count before next test
        count += count;
    }
}


int main(int argc, char *argv[])
{
    auto parameters = tests::getParameters(argc, argv);
    if (tests::Registry<int>::algorithmExists(parameters.algId))
    {
        doubleAmountTest(parameters);
    }
    else
    {
        tests::InputParameters::usage<int>();
    }

    return 0;
}

//--------------------------------------------------------------------------------------------------
