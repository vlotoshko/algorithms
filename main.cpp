//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort/TestSort.hpp"

#include <iostream>
#include <iomanip>
//--------------------------------------------------------------------------------------------------


struct InputParameters
{
    sort::SortId algId;
    unsigned repeatCount;
    unsigned elementsCount;
    static void usage() { std::cout << "Hello, World!" << std::endl; }
};


// ------------------------------------------------------------------------------------------
// Pasres input app parameter to a convinient structure
//
InputParameters getParameters(int argc, char *argv[])
{
    InputParameters parameters{};

    if (argc > 1)
    {
        parameters.algId = static_cast<sort::SortId>(atoi(argv[1]));
    }

    if (argc > 2)
    {
        parameters.repeatCount = static_cast<unsigned>(atoi(argv[2]));
    }

    if (argc > 3)
    {
        parameters.elementsCount = static_cast<unsigned>(atoi(argv[3]));
    }

    return parameters;
}


// ------------------------------------------------------------------------------------------
// Repeatedly invokes test doubling the amount of elements for each iteration
//
void doubleAmountTest(const InputParameters parameters)
{
    tools::CalcRatio calcRatio;
    auto amount = parameters.elementsCount;
    for (size_t i = 1; i <= parameters.repeatCount; ++i)
    {
        tools::Timer timer;
        sort::TestSort<int> (parameters.algId, amount).runTest(timer);
        double time = timer.timeSpent();
        std::cout << std::left
                  << "count: " << std::setw(10) << amount << "time eplaced: " << std::setw(10)
                  << time << "ratio: " << calcRatio.getRatio(time) << std::endl;

        // Double elements count before next test
        amount += amount;
    }
}

int main(int argc, char *argv[])
{
    InputParameters::usage();
    doubleAmountTest(getParameters(argc, argv));
    return 0;
}

//--------------------------------------------------------------------------------------------------
