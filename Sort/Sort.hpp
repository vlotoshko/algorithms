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
            for (size_t i = 0; i < length - 1; i++)
            {
                if (elements[i] != elements[i + 1] && !this->less(elements[i], elements[i + 1]))
                {
                    std::swap(elements[i], elements[i + 1]);
                    isSorted = false;
                }
            }
        }
    }
    std::string name() const override { return  "Dummy sort"; }
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
    std::string name() const override { return  "Buble sort"; }
};


// ------------------------------------------------------------------------------------------
// Comb sort algorithm
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
    std::string name() const override { return  "Comb sort"; }
};


// ------------------------------------------------------------------------------------------
// Shake sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class ShakeSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        int length = elements.size();
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
    std::string name() const override { return "Shake sort"; }
};


// ------------------------------------------------------------------------------------------
// Quick sort algorithm
// Complexity: average O(n*log(n)), worst O(n*n)
//
template <typename T>
class QuickSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        sort(elements, 0, elements.size() - 1);
    }
    std::string name() const override { return "Quick sort"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int lo, int hi)
    {
        if (hi <= lo)
        {
            return;
        }
        int j = partition(elements, lo, hi);
        sort(elements, lo, j - 1);
        sort(elements, j + 1, hi);
    }

    int partition(std::vector<T> & elements, int lo, int hi)
    {
        int i = lo;
        int j = hi + 1;
        T v = elements[lo];
        while (true)
        {
            while (this->less(elements[++i], v))
            {
                if (i == hi)
                    break;
            }
            while (this->less(v, elements[--j]))
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
};


// ------------------------------------------------------------------------------------------
// Quick sort Median algorithm
// Complexity: average O(n*log(n)), worst O(n*n)
//
template <typename T>
class QuickSortM : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        sort(elements, 0, elements.size() - 1);
    }
    std::string name() const override { return "Quick sort median"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int lo, int hi)
    {
        if (hi <= lo)
        {
            return;
        }
        int j = partition(elements, lo, hi);
        sort(elements, lo, j - 1);
        sort(elements, j + 1, hi);
    }

    int partition(std::vector<T> & elements, int lo, int hi)
    {
        int i = lo;
        int j = hi + 1;
        int ind = lo;

        if (hi - lo >= 3)
        {
            bool a_less_b = this->less(elements[lo], elements[lo + 1]);
            bool b_less_c = this->less(elements[lo + 1], elements[lo + 2]);
            bool c_less_a = this->less(elements[lo + 2], elements[lo]);

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
            while (this->less(elements[++i], v))
            {
                if (i == hi)
                    break;
            }
            while (this->less(v, elements[--j]))
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
};


// ------------------------------------------------------------------------------------------
// Quick sort 3parts algorithm
// Complexity: average O(n*log(n)), worst O(n*n)
//
template <typename T>
class Quick3Sort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        sort(elements, 0, elements.size() - 1);
    }
    std::string name() const override { return "Quick3 sort"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int lo, int hi)
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
            else if (this->less(elements[i], v))
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
};


// ------------------------------------------------------------------------------------------
// Gnome sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class GnomeSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        size_t length = elements.size();
        for (size_t i = 1; i < length; i++)
        {
            for (size_t j = i; j > 0 && this->less(elements[j], elements[j - 1]); j--)
            {
                std::swap(elements[j], elements[j - 1]);
            }
        }
    }
    std::string name() const override { return  "Gnome sort"; }
};


// ------------------------------------------------------------------------------------------
// ---------------- Selection sort algorithms -----------------------------------------------
// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Selection sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class SelectionSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        size_t length = elements.size();
        for (size_t i = 0; i < length; i++)
        {
            size_t min = i;
            for (size_t j = i; j < length - 1; ++j)
            {
                if (elements[min] != elements[j + 1] && !this->less(elements[min], elements[j + 1]))
                {
                    min = j + 1;
                }
            }
            std::swap(elements[min], elements[i]);
        }
    }
    std::string name() const override { return  "Selection sort"; }
};


// ------------------------------------------------------------------------------------------
// Heap sort algorithm
// Complexity: O(n*log(n))
//
template <typename T>
class HeapSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        int length = elements.size();
        {
            //  1. make sorted tree
            for (int i = length / 2; i >= 0; i--)
            {
                sink(elements, i, length);
            }

            // 2. sort
            while(length > 1)
            {
                std::swap(elements[0], elements[--length]);
                sink(elements, 0, length);

            }
        }
    }
    std::string name() const override { return  "Heap sort"; }
private:
    void sink(std::vector<T> & elements, int pos, int length)
    {
        ++pos;
        while (2 * pos <= length)
        {
            int j = 2 * pos;
            if(j < length && this->less(elements[j - 1], elements[j]))
                j++;

            if(this->less(elements[j - 1], elements[pos - 1]))
                break;
            std::swap(elements[j - 1], elements[pos - 1]);
            pos = j;
        }
    }
};

// ------------------------------------------------------------------------------------------
// ---------------- Insertion sort algorithms -----------------------------------------------
// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Insertion sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class InsertionSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        int length = elements.size();
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
    void sort(int *array, int length)
    {
        for (int i = 1; i < length; i++)
        {
            int key = array[i];
            int j = i - 1;

            while(j >= 0 && array[j] > key)
            {
                array[j + 1] = array[j];
                --j;
            }
            array[j + 1] = key;
        }
    }
    std::string name() const override { return  "Insertion sort"; }
};


// ------------------------------------------------------------------------------------------
// Shell sort algorithm
// Complexity:  O(n*log(n)*log(n))
//
template <typename T>
class ShellSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        int length = elements.size();
        int h = 1;
        while (h < length / 3)
            h = 3 * h + 1;

        while (h >= 1)
        {
            for (int i = h; i < length; i++)
            {
                for (int j = i; j >= h && this->less(elements[j], elements[j - h]); j -= h)
                {
                    std::swap(elements[j], elements[j - h]);
                }
            }
            h /= 3;
        }
    }
    std::string name() const override { return  "Shell sort"; }
};

// ------------------------------------------------------------------------------------------
// ---------------- Merging sort algorithms -------------------------------------------------
// ------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Merge sort algorithm
// Complexity: O(n*log(n))
//
template <typename T>
class MergeSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        std::vector<T> aux(elements.size());
        sort(elements, 0, elements.size() - 1, aux);
    }
    std::string name() const override { return  "Merge sort"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int lo, int hi, std::vector<T> & aux)
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

    void merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux)
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
                    if (this->less(aux[j], aux[i]))
                        elements[k] = aux[j++]; // copy from right part
                    else
                        elements[k] = aux[i++]; // copy from left part
        }
    }
};


// ------------------------------------------------------------------------------------------
// Merge upward sort algorithm
// Complexity: O(n*log(n))
//
template <typename T>
class MergeUpSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        std::vector<T> aux(elements.size());
        sort(elements, elements.size(), aux);
    }
    std::string name() const override { return  "MergeUp sort"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int length, std::vector<T> & aux)
    {
        for (int sz = 1; sz < length; sz += sz)
        {
            for (int lo = 0; lo < length - sz; lo += sz+sz)
            {
                merge(elements, lo, lo+sz-1, (lo + sz + sz - 1) < (length - 1) ? lo + sz + sz - 1 : length - 1, aux);
            }
        }
    }

    // merge function is the same as in the merge sort algorithm
    void merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux)
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
                    if (this->less(aux[j], aux[i]))
                        elements[k] = aux[j++]; // copy from right part
                    else
                        elements[k] = aux[i++]; // copy from left part
        }
    }
};


// ------------------------------------------------------------------------------------------
// ---------------- Hybrid sort algorithms --------------------------------------------------
// ------------------------------------------------------------------------------------------


// ------------------------------------------------------------------------------------------
// Quick + Insertion sort algorithm
// Complexity: average O(n*log(n)), worst O(n*n)
//
template <typename T>
class QuickInsSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        sort(elements, 0, elements.size() - 1);
    }
    std::string name() const override { return "QuickIns sort"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int lo, int hi)
    {
        if (hi - lo <= 15)
        {
            iSort_.sort(&elements[lo], hi - lo + 1);
            return;
        }

        int j = partition(elements, lo, hi);
        sort(elements, lo, j - 1);
        sort(elements, j + 1, hi);
    }

    int partition(std::vector<T> & elements, int lo, int hi)
    {
        int i = lo;
        int j = hi + 1;
        T v = elements[lo];
        while (true)
        {
            while (this->less(elements[++i], v))
            {
                if (i == hi)
                    break;
            }
            while (this->less(v, elements[--j]))
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

    InsertionSort<T> iSort_;
};


// ------------------------------------------------------------------------------------------
// Merge + Insertion sort algorithm
// Complexity: O(n*log(n))
//
template <typename T>
class MergeInsSort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
        std::vector<T> aux(elements.size());
        sort(elements, 0, elements.size() - 1, aux);
    }
    std::string name() const override { return  "MergeIns sort"; }
private:
    // NOTE: bounders lo and hi should be signed type
    void sort(std::vector<T> & elements, int lo, int hi, std::vector<T> & aux)
    {
        if (hi - lo <= 15)
        {
            iSort_.sort(&elements[lo], hi - lo + 1);
            return;
        }

        int mid = lo + (hi - lo) / 2;

        sort(elements, lo, mid, aux);
        sort(elements, mid + 1, hi, aux);
        merge(elements, lo, mid, hi, aux);
    }

    void merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux)
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
                    if (this->less(aux[j], aux[i]))
                        elements[k] = aux[j++]; // copy from right part
                    else
                        elements[k] = aux[i++]; // copy from left part
        }
    }

    InsertionSort<T> iSort_;
};


// ------------------------------------------------------------------------------------------
// InsertionBinary sort algorithm
// Complexity: O(n*n)
//
template <typename T>
class InsertionBinarySort : public ISortable<T>
{
public:
    void sort(std::vector<T> & elements) override
    {
         // TODO: implement InsertionBinary sort
        int length = elements.size();
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
    std::string name() const override { return  "InsertionBinary sort"; }
};

} // namespace sort

//--------------------------------------------------------------------------------------------------
#endif // SORT_HPP
//--------------------------------------------------------------------------------------------------
