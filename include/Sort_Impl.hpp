/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 04-Feb-2019
 */

// -------------------------------------------------------------------------------------------------
#ifndef SORT_IMPL_HPP
#define SORT_IMPL_HPP
// -------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort.hpp"
//--------------------------------------------------------------------------------------------------

namespace sort
{


// -------------------------------------------------------------------------------
// ----- DummySort -----
//

template <typename T>
void DummySort<T>::sort(std::vector<T> & elements)
{
    size_t length = elements.size();
    bool isSorted = false;
    while (!isSorted)
    {
        isSorted = true;
        for (size_t i = 0; i < length - 1; i++)
        {
            if (elements[i] != elements[i + 1] && !less(elements[i], elements[i + 1]))
            {
                std::swap(elements[i], elements[i + 1]);
                isSorted = false;
            }
        }
    }
}

template <typename T>
char const * DummySort<T>::name = "Dummy sort";


// -------------------------------------------------------------------------------
// ----- BubleSort -----
//

template <typename T>
void BubleSort<T>::sort(std::vector<T> & elements)
{
    size_t length = elements.size();
    for (size_t i = 0; i < length; i++)
    {
        for (size_t j = 0; j < length - i - 1; ++j)
        {
            if (elements[j] != elements[j + 1] && !less(elements[j], elements[j + 1]))
            {
                std::swap(elements[j], elements[j + 1]);
            }
        }
    }
}

template <typename T>
char const * BubleSort<T>::name = "Buble sort";


// -------------------------------------------------------------------------------
// ----- CombSort -----
//

template <typename T>
void CombSort<T>::sort(std::vector<T> & elements)
{
    size_t length = elements.size();
    size_t h = length;
    bool swapped = true;
    while (h > 1 || swapped)
    {
        if (h > 1)
            h = static_cast<size_t>(h / 1.24733);

        swapped = false;
        for (size_t i = 0; i + h < length; i++)
        {
            if (less(elements[i + h], elements[i]))
            {
                std::swap(elements[i], elements[i + h]);
                swapped = true;
            }
        }
    }
}

template <typename T>
char const * CombSort<T>::name = "Comb sort";


// -------------------------------------------------------------------------------
// ----- ShakeSort -----
//

template <typename T>
void ShakeSort<T>::sort(std::vector<T> & elements)
{
    int length = static_cast<int>(elements.size());
    for (int left = 0, right = length - 1; left < right;) {

        for (int j = left; j < right; ++j)
        {
            if (elements[j] != elements[j + 1] && less(elements[j + 1], elements[j]))
            {
                std::swap(elements[j], elements[j + 1]);
            }
        }
        right--;

        for (int j = right; j > left; --j)
        {
            if (elements[j] != elements[j - 1] && less(elements[j], elements[j - 1]))
            {
                std::swap(elements[j - 1], elements[j]);
            }
        }
        left++;
    }
}

template <typename T>
char const * ShakeSort<T>::name = "Shake sort";


// -------------------------------------------------------------------------------
// ----- QuickSort -----
//

template <typename T>
void QuickSort<T>::sort(std::vector<T> & elements, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }
    int j = partition(elements, lo, hi);
    sort(elements, lo, j - 1);
    sort(elements, j + 1, hi);
}

template <typename T>
int QuickSort<T>::partition(std::vector<T> & elements, int lo, int hi)
{
    int i = lo;
    int j = hi + 1;
    T v = elements[lo];
    while (true)
    {
        while (less(elements[++i], v))
        {
            if (i == hi)
                break;
        }
        while (less(v, elements[--j]))
        {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        std::swap(elements[i], elements[j]);
    }
    std::swap(elements[lo], elements[j]);
    return j;
}

template <typename T>
char const * QuickSort<T>::name = "Quick sort";


// -------------------------------------------------------------------------------
// ----- QuickSortM -----
//

template <typename T>
void QuickSortM<T>::sort(std::vector<T> & elements, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }
    int j = partition(elements, lo, hi);
    sort(elements, lo, j - 1);
    sort(elements, j + 1, hi);
}

template <typename T>
int QuickSortM<T>::partition(std::vector<T> & elements, int lo, int hi)
{
    int i = lo;
    int j = hi + 1;
    int ind = lo;

    if (hi - lo >= 3)
    {
        bool a_less_b = less(elements[lo], elements[lo + 1]);
        bool b_less_c = less(elements[lo + 1], elements[lo + 2]);
        bool c_less_a = less(elements[lo + 2], elements[lo]);

        if (c_less_a && a_less_b)
            ind = lo;
        else
            if (a_less_b && b_less_c)
                ind = lo+1;
            else
                if (b_less_c && c_less_a)
                    ind = lo+2;
    }

    if (ind != lo)
        std::swap(elements[lo], elements[ind]);

    T v = elements[lo];

    while (true)
    {
        while (less(elements[++i], v))
        {
            if (i == hi)
                break;
        }
        while (less(v, elements[--j]))
        {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        std::swap(elements[i], elements[j]);
    }
    std::swap(elements[lo], elements[j]);
    return j;
}

template <typename T>
char const * QuickSortM<T>::name = "Quick sort median";


// -------------------------------------------------------------------------------
// ----- Quick3Sort -----
//

template <typename T>
void Quick3Sort<T>::sort(std::vector<T> & elements, int lo, int hi)
{
    if (hi <= lo)
    {
        return;
    }

    int lt = lo;
    int i = lo + 1;
    int gt = hi;
    T v = elements[lo];

    while (i <= gt)
    {
        if (elements[i] == v)
        {
            i++;
        }
        else if (less(elements[i], v))
        {
            std::swap(elements[lt++], elements[i++]);
        }
        else
        {
            std::swap(elements[i], elements[gt--]);
        }
    }
    sort(elements, lo, lt - 1);
    sort(elements, gt + 1, hi);
}

template <typename T>
char const * Quick3Sort<T>::name = "Quick3 sort";



// -------------------------------------------------------------------------------
// ----- GnomeSort -----
//

template <typename T>
void GnomeSort<T>::sort(std::vector<T> & elements)
{
    size_t length = elements.size();
    for (size_t i = 1; i < length; i++)
    {
        for (size_t j = i; j > 0 && less(elements[j], elements[j - 1]); j--)
        {
            std::swap(elements[j], elements[j - 1]);
        }
    }
}

template <typename T>
char const * GnomeSort<T>::name = "Gnome sort";


// -------------------------------------------------------------------------------
// ----- SelectionSort -----
//

template <typename T>
void SelectionSort<T>::sort(std::vector<T> & elements)
{
    size_t length = elements.size();
    for (size_t i = 0; i < length; i++)
    {
        size_t min = i;
        for (size_t j = i; j < length - 1; ++j)
        {
            if (elements[min] != elements[j + 1] && less(elements[j + 1], elements[min]))
            {
                min = j + 1;
            }
        }
        std::swap(elements[min], elements[i]);
    }
}

template <typename T>
char const * SelectionSort<T>::name = "Selection sort";


// -------------------------------------------------------------------------------
// ----- HeapSort -----
//

template <typename T>
void HeapSort<T>::sort(std::vector<T> & elements)
{
    int length = static_cast<int>(elements.size());
    {
        //  1. make sorted tree
        for (int i = length / 2; i >= 0; i--)
        {
            sink(elements, i, length);
        }

        // 2. sort
        while (length > 1)
        {
            std::swap(elements[0], elements[--length]);
            sink(elements, 0, length);

        }
    }
}


template <typename T>
void HeapSort<T>::sink(std::vector<T> & elements, int pos, int length)
{
    ++pos;
    while (2 * pos <= length)
    {
        int j = 2 * pos;
        if (j < length && less(elements[j - 1], elements[j]))
            j++;

        if (less(elements[j - 1], elements[pos - 1]))
            break;
        std::swap(elements[j - 1], elements[pos - 1]);
        pos = j;
    }
}
template <typename T>
char const * HeapSort<T>::name = "Heap sort";


// -------------------------------------------------------------------------------
// ----- InsertionSort -----
//

template <typename T>
void InsertionSort<T>::sort(std::vector<T> & elements)
{
    int length = static_cast<int>(elements.size());
    for (int i = 1; i < length; i++)
    {
        T key = elements[i];
        int j = i - 1;

        while (j >= 0 && elements[j] > key)
        {
            elements[j + 1] = elements[j];
            --j;
        }
        elements[j + 1] = key;
    }
}

template <typename T>
void InsertionSort<T>::sort(T *array, int length)
{
    for (int i = 1; i < length; i++)
    {
        T key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            --j;
        }
        array[j + 1] = key;
    }
}

template <typename T>
char const * InsertionSort<T>::name = "Insertion sort";


// -------------------------------------------------------------------------------
// ----- ShellSort -----
//

template <typename T>
void ShellSort<T>::sort(std::vector<T> & elements)
{
    int length = static_cast<int>(elements.size());
    int h = 1;
    while (h < length / 3)
        h = 3 * h + 1;

    while (h >= 1)
    {
        for (int i = h; i < length; i++)
        {
            for (int j = i; j >= h && less(elements[j], elements[j - h]); j -= h)
            {
                std::swap(elements[j], elements[j - h]);
            }
        }
        h /= 3;
    }
}

template <typename T>
char const * ShellSort<T>::name = "Shell sort";


// -------------------------------------------------------------------------------
// ----- MergeSort -----
//

template <typename T>
void MergeSort<T>::sort(std::vector<T> & elements, int lo, int hi, std::vector<T> & aux)
{
    if (hi <= lo)
    {
        return;
    }

    int mid = lo + (hi - lo) / 2;

    sort(elements, lo, mid, aux);
    sort(elements, mid + 1, hi, aux);
    merge(elements, lo, mid, hi, aux);
}

template <typename T>
void MergeSort<T>::merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux)
{
    int i = lo;
    int j = mid + 1;

    // copying array to aux
    for (int k = lo; k <= hi; k++)
    {
       aux[k] = elements[k];
    }

    // copying array from aux
    for (int k = lo; k <= hi; k++)
    {
        if (i > mid)
            elements[k] = aux[j++]; // copy from right part
        else
            if (j > hi)
                elements[k] = aux[i++]; // copy from left part
            else
                if (less(aux[j], aux[i]))
                    elements[k] = aux[j++]; // copy from right part
                else
                    elements[k] = aux[i++]; // copy from left part
    }
}

template <typename T>
char const * MergeSort<T>::name = "Merge sort";


// -------------------------------------------------------------------------------
// ----- MergeUpSort -----
//

template <typename T>
void MergeUpSort<T>::sort(std::vector<T> & elements, int length, std::vector<T> & aux)
{
    for (int sz = 1; sz < length; sz += sz)
    {
        for (int lo = 0; lo < length - sz; lo += sz+sz)
        {
            merge(elements, lo, lo+sz-1, (lo + sz + sz - 1) < (length - 1) ? lo + sz + sz - 1 : length - 1, aux);
        }
    }
}

template <typename T>
void MergeUpSort<T>::merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux)
{
    int i = lo;
    int j = mid + 1;

    // copying array to aux
    for (int k = lo; k <= hi; k++)
    {
       aux[k] = elements[k];
    }

    // copying array from aux
    for (int k = lo; k <= hi; k++)
    {
        if (i > mid)
            elements[k] = aux[j++]; // copy from right part
        else
            if (j > hi)
                elements[k] = aux[i++]; // copy from left part
            else
                if (less(aux[j], aux[i]))
                    elements[k] = aux[j++]; // copy from right part
                else
                    elements[k] = aux[i++]; // copy from left part
    }
}
template <typename T>
char const * MergeUpSort<T>::name = "MergeUp sort";


// -------------------------------------------------------------------------------
// ----- QuickInsSort -----
//

template <typename T>
void QuickInsSort<T>::sort(std::vector<T> & elements, int lo, int hi)
{
    if (hi - lo <= 15)
    {
        InsertionSort<T>{}.sort(&elements[lo], hi - lo + 1);
        return;
    }

    int j = partition(elements, lo, hi);
    sort(elements, lo, j - 1);
    sort(elements, j + 1, hi);
}

template <typename T>
int QuickInsSort<T>::partition(std::vector<T> & elements, int lo, int hi)
{
    int i = lo;
    int j = hi + 1;
    T v = elements[lo];
    while (true)
    {
        while (less(elements[++i], v))
        {
            if (i == hi)
                break;
        }
        while (less(v, elements[--j]))
        {
            if (j == lo)
                break;
        }
        if (i >= j)
            break;
        std::swap(elements[i], elements[j]);
    }
    std::swap(elements[lo], elements[j]);
    return j;
}

template <typename T>
char const * QuickInsSort<T>::name = "QuickIns sort";


// -------------------------------------------------------------------------------
// ----- MergeInsSort -----
//

template <typename T>
void MergeInsSort<T>::sort(std::vector<T> & elements, int lo, int hi, std::vector<T> & aux)
{
    if (hi - lo <= 15)
    {
        InsertionSort<T>{}.sort(&elements[lo], hi - lo + 1);
        return;
    }

    int mid = lo + (hi - lo) / 2;

    sort(elements, lo, mid, aux);
    sort(elements, mid + 1, hi, aux);
    merge(elements, lo, mid, hi, aux);
}


template <typename T>
void MergeInsSort<T>::merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux)
{
    int i = lo;
    int j = mid + 1;

    // copying array to aux
    for (int k = lo; k <= hi; k++)
    {
       aux[k] = elements[k];
    }

    // copying array from aux
    for (int k = lo; k <= hi; k++)
    {
        if (i > mid)
            elements[k] = aux[j++]; // copy from right part
        else
            if (j > hi)
                elements[k] = aux[i++]; // copy from left part
            else
                if (less(aux[j], aux[i]))
                    elements[k] = aux[j++]; // copy from right part
                else
                    elements[k] = aux[i++]; // copy from left part
    }
}

template <typename T>
char const * MergeInsSort<T>::name = "MergeIns sort";


// -------------------------------------------------------------------------------
// ----- InsertionBinarySort -----
//

template <typename T>
void InsertionBinarySort<T>::sort(std::vector<T> & elements)
{
     // TODO: implement InsertionBinary sort
    int length = static_cast<int>(elements.size());
    for (int i = 1; i < length; i++)
    {
        T key = elements[i];
        int j = i - 1;

        while (j >= 0 && elements[j] > key)
        {
            elements[j + 1] = elements[j];
            --j;
        }
        elements[j + 1] = key;
    }
}

template <typename T>
char const * InsertionBinarySort<T>::name = "InsertionBinary sort";


} // namespace sort

//--------------------------------------------------------------------------------------------------
#endif // SORT_IMPL_HPP
//--------------------------------------------------------------------------------------------------
