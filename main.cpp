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
    static const char * hello;
    template<typename T>
    static void usage()
    {
        std::cout << hello << std::endl;
        for (auto & item: sort::TestSort<T>::Algorithms)
        {
            std::cout << std::setw(3) << static_cast<int>(item.first) <<  ":\t"
                      << item.second->name() << std::endl;
        }
    }
};

const char * InputParameters::hello =
        "Usage: algorithm X Y Z\n"
        "Where:\n"
        "  X - number of the algorithm\n"
        "  Y - repeat count, algorithm will be invoked Y times, doubling its element count each time\n"
        "  Z - initial elements count\n"
        "Sort algorithms:";


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
    auto parameters = getParameters(argc, argv);
    auto const & sortAlgs = sort::TestSort<int>::Algorithms;
    if (argc < 4 || sortAlgs.find(parameters.algId) == sortAlgs.end())
    {
        InputParameters::usage<int>();
    }
    else
    {
        doubleAmountTest(parameters);
    }
    return 0;
}

//--------------------------------------------------------------------------------------------------
