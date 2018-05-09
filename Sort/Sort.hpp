//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef SORT_HPP
#define SORT_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort/ISortable.hpp"
//--------------------------------------------------------------------------------------------------

namespace sort
{

// ------------------------------------------------------------------------------------------
// ---------------- Changing sort algorithms ------------------------------------------------
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
// Simpliest sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class DummySort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        size_t length = elements.size();
        bool isSorted = false;
        while (!isSorted)
        {
            isSorted = true;
            for (int i = 0; i < length - 1; i++)
            {
                if (elements[i] != elements[i + 1] && !this->less(elements[i], elements[i + 1]))
                {
                    std::swap(elements[i], elements[i + 1]);
                    isSorted = false;
                }
            }
        }
    }
};


// ------------------------------------------------------------------------------------------
// Classic buble sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class BubleSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        size_t length = elements.size();
        for (size_t i = 0; i < length; i++)
        {
            for (size_t j = 0; j < length - i - 1; ++j)
            {
                if (elements[j] != elements[j + 1] && !this->less(elements[j], elements[j + 1]))
                {
                    std::swap(elements[j], elements[j + 1]);
                }
            }
        }
    }
};


// ------------------------------------------------------------------------------------------
// Classic buble sort algorithm
// Complexity: average O(n*log(n)), worst O(n*n)
//
template <typename T>
class CombSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        size_t length = elements.size();
        size_t h = length;
        bool swapped = true;
        while (h > 1 || swapped)
        {
            if (h > 1)
                h /= 1.24733;

            swapped = false;
            for (size_t i = 0; i + h < length; i++)
            {
                if (this->less(elements[i + h], elements[i]))
                {
                    std::swap(elements[i], elements[i + h]);
                    swapped = true;
                }
            }
        }
    }
};



// ------------------------------------------------------------------------------------------
// Classic buble sort algorithm
// Complexity: average O(n*log(n)), worst O(n*n)
//
template <typename T>
class ShakeSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        size_t length = elements.size();
        for (int left = 0, right = length - 1; left < right;) {

            for (int j = left; j < right; ++j)
            {
                if (elements[j] != elements[j + 1] && this->less(elements[j + 1], elements[j]))
                {
                    std::swap(elements[j], elements[j + 1]);
                }
            }
            right--;

            for (int j = right; j > left; --j)
            {
                if (elements[j] != elements[j - 1] && this->less(elements[j], elements[j - 1]))
                {
                    std::swap(elements[j - 1], elements[j]);
                }
            }
            left++;
        }
    }
};


// ------------------------------------------------------------------------------------------
// ---------------- Selection sort algorithms -----------------------------------------------
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
// ---------------- Insertion sort algorithms -----------------------------------------------
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
// ---------------- Merging sort algorithms -------------------------------------------------
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
// ---------------- Hybrid sort algorithms --------------------------------------------------
// ------------------------------------------------------------------------------------------



} // namespace sort

//--------------------------------------------------------------------------------------------------
#endif // SORT_HPP
//--------------------------------------------------------------------------------------------------
