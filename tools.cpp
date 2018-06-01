//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "tools.hpp"

#include <iomanip>
//--------------------------------------------------------------------------------------------------

namespace tools
{

Timer::Timer() : start_(std::chrono::system_clock::now()) {}

void Timer::start()
{
    start_ = std::chrono::system_clock::now();
}

double Timer::timeSpent()
{
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start_).count();
    return duration / 1000;
}

double CalcRatio::getRatio(double value)
{
    double result = value/previous_;
    if (value != 0.0)
    {
        previous_ = value;
    }
    else
    {
        previous_ = 1;
    }

    return result;
}

void InputParameters::usage()
{
    std::cout << hello << std::endl;
//    for (auto & item: sort::TestSort<T>::Algorithms)
//    {
//        std::cout << std::setw(3) << static_cast<int>(item.first) <<  ":\t"
//                  << item.second->name() << std::endl;
//    }
}

const char * InputParameters::hello =
        "Usage: algorithm X Y Z\n"
        "Where:\n"
        "  X - number of the algorithm\n"
        "  Y - repeat count, algorithm will be invoked Y times, doubling its element count each time\n"
        "  Z - initial elements count\n"
        "Sort algorithms:";

InputParameters getParameters(int argc, char *argv[])
{
    InputParameters parameters{};

    if (argc > 1)
    {
        parameters.algId = static_cast<unsigned>(atoi(argv[1]));
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

} // namespace tools
//--------------------------------------------------------------------------------------------------


