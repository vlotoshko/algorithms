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
    static auto const seed = std::random_device()();
    static std::mt19937 rng(seed);
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


/*! \brief Returns true if container is sorted
 * \param const reference to container Container
 */
template <template <typename...> class Container, typename T>
bool isSorted(const Container<T> & container)
{
    if (container.size() > 0)
    {
        auto i = container.front();
        for (auto const & item : container)
        {
            if (std::less<T>()(item, i))
            {
                return false;
            }
            i = item;
        }
    }
    return true;
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