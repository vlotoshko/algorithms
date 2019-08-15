/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

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

/**
 * @brief The Timer class calculates time is seconds as xx.xxx between construction/start
 * and timeSpent invokations.
 */
class Timer {
public:
    /**
     * @brief The Timer constructor sets new start time point.
     */
    Timer();

    /**
     * @brief start resets start time point
     */
    void start();

    /**
     * @brief timeSpent calculates time between 'now' time point and saved time point.
     * @return difference between 'now' time point and saved time point.
     */
    double timeSpent() const;
private:
    std::chrono::time_point<std::chrono::system_clock> start_;
};

/**
 * @brief random returns random values from min to max of the type T.
 * @tparam T type
 * @param[in] min min value
 * @param[in] max max value
 * @return randome value of T
 */
template <typename T>
T random(const T & min, const T & max)
{
    static auto const seed = std::random_device()();
    static std::mt19937 rng(seed);
    std::uniform_int_distribution<T> uni(min,max);
    auto random_T = uni(rng);
    return random_T;
}

/**
 * @brief randomData fills vector by random values from min to max of the type T.
 * @tparam T type
 * @param[out] elements
 * @param[in] size size of the vector
 * @param[in] min min value
 * @param[in] max max value
 */
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

/**
 * @brief show outputs elements of the vector.
 * @tparam T type of the element
 * @param[in] elements
 */
template <typename T>
void show(const std::vector<T> & elements)
{
    for (auto const & e : elements)
    {
        std::cout << e << ' ';
    }
    std::cout << std::endl;
}

/**
 * @brief isSorted check wheter container is sorted or not.
 * @tparam Container type of the container
 * @tparam T type of the element
 * @param[in] container
 * @return true if container sorted.
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

/**
 * @brief The CalcRatio class calculates ratio between current value and previous, saved before.
 */
class CalcRatio
{
public:
    /**
     * @brief The CalcRatio saver initial value as 1.
     */
    CalcRatio() : previous_(1) {}
    /**
     * @brief getRatio calrulates ratio and saves given value.
     * @param[in] value value
     * @return ratio between current value and value saved before.
     */
    double getRatio(double value);
private:
    double previous_;
};


} // namespace tools


//--------------------------------------------------------------------------------------------------
#endif // TOOLS_H
//--------------------------------------------------------------------------------------------------
