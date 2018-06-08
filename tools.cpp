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


} // namespace tools
//--------------------------------------------------------------------------------------------------


