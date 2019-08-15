/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#include "Tools.hpp"

#include <iomanip>
//--------------------------------------------------------------------------------------------------

namespace tools
{

Timer::Timer() : start_(std::chrono::system_clock::now()) {}

void Timer::start()
{
    start_ = std::chrono::system_clock::now();
}

double Timer::timeSpent() const
{
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    double duration = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(end-start_).count());
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


