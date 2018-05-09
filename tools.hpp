//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TOOLS_H
#define TOOLS_H
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <chrono>
#include <vector>
#include <iostream>
#include <random>
//--------------------------------------------------------------------------------------------------

namespace tools
{
// ------------------------------------------------------------------------------------------
// Timer returns time is seconds as xx.xxx between construction/start and timeSpent invokations
//
class Timer {
public:
    Timer();
    void start();
    double timeSpent();
private:
    std::chrono::time_point<std::chrono::system_clock> start_;
};


// ------------------------------------------------------------------------------------------
// Returns random T value within from min to max
//
template <typename T>
T random(const T & min, const T & max)
{
    // TODO: make static objects that should be initialized once
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<T> uni(min,max);
    auto random_T = uni(rng);
    return random_T;
}


// ------------------------------------------------------------------------------------------
// Fills vector with the count of size elements with the random value from min to max
//
template <typename T>
void randomData(std::vector<T> & elements, size_t size, T min, T max)
{
    elements.clear();
    elements.reserve(size);
    for (size_t i = 0; i < size; ++i)
    {
        elements.push_back(random(min, max));
    }
}


// ------------------------------------------------------------------------------------------
// Outputs all elements of a vector
//
template <typename T>
void show(const std::vector<T> & elements)
{
    for (auto const & e : elements)
    {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}


// ------------------------------------------------------------------------------------------
// Calculates ratio between current value and previous, saved before.
//
class CalcRatio
{
public:
    CalcRatio() : previous_(1) {}
    double getRatio(double value);
private:
    double previous_;
};

} // namespace tools

//--------------------------------------------------------------------------------------------------
#endif // TOOLS_H
//--------------------------------------------------------------------------------------------------
