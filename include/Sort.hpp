/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

// -------------------------------------------------------------------------------------------------
#ifndef SORT_HPP
#define SORT_HPP
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
#include "Tools.hpp"
// -------------------------------------------------------------------------------------------------

namespace sort
{

/**
 * @brief The less template function is a comparator.
 * @tparam type of elements to compare
 * @param[in] a first element
 * @param[in] b second element
 * @return true if a less than b.
 */
template<typename T>
inline bool less(const T & a, const T & b)
{
    return std::less<T>()(a, b);
}


// ----------------------------------------------------------------------------------------
// ---------------- Changing sort algorithms ----------------------------------------------
// ----------------------------------------------------------------------------------------

/**
 * @class DummySort
 * @brief The DummySort template class is the simpliest sort algorithm. Complexity: O(n*n).
 */
template <typename T>
class DummySort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};


/**
 * @class BubleSort
 * @brief The BubleSort template class is the classic sort algorithm. Complexity: O(n*n).
 */
template <typename T>
class BubleSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};


/**
 * @class CombSort
 * @brief The CombSort template class. Complexity: average O(n*log(n)), worst O(n*n).
 */
template <typename T>
class CombSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};


/**
 * @class ShakeSort
 * @brief The ShakeSort template class. Complexity: O(n*n).
 */
template <typename T>
class ShakeSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};


/**
 * @class QuickSort
 * @brief The QuickSort template class. Complexity: average O(n*log(n)), worst O(n*n).
 */
template <typename T>
class QuickSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        sort(elements, 0, static_cast<int>(elements.size()) - 1);
    }

    /// class name
    static char const * name;
private:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     * @param[in] lo left boundary
     * @param[in] hi right boundary
     *
     * @note bounders lo and hi should be signed type
     */
    static void sort(std::vector<T> & elements, int lo, int hi);

    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     * @param[in] lo left boundary
     * @param[in] hi right boundary
     *
     * @note bounders lo and hi should be signed type
     */
    static int partition(std::vector<T> & elements, int lo, int hi);
};


/**
 * @class QuickSortM
 * @brief The QuickSortM template class implements quick-sort-median algorithm.
 * Complexity: average O(n*log(n)), worst O(n*n).
 */
template <typename T>
class QuickSortM
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        sort(elements, 0, static_cast<int>(elements.size()) - 1);
    }

    /// class name
    static char const * name;
private:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     * @param[in] lo left boundary
     * @param[in] hi right boundary
     *
     * @note bounders lo and hi should be signed type
     */
    static void sort(std::vector<T> & elements, int lo, int hi);

    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     * @param[in] lo left boundary
     * @param[in] hi right boundary
     *
     * @note bounders lo and hi should be signed type
     */
    static int partition(std::vector<T> & elements, int lo, int hi);
};


/**
 * @class Quick3Sort
 * @brief The Quick3Sort template class implements quick-sort-3parts algorithm.
 * Complexity: average O(n*log(n)), worst O(n*n).
 */
template <typename T>
class Quick3Sort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        sort(elements, 0, static_cast<int>(elements.size()) - 1);
    }

    /// class name
    static char const * name;
private:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     * @param[in] lo left boundary
     * @param[in] hi right boundary
     *
     * @note bounders lo and hi should be signed type
     */
    static void sort(std::vector<T> & elements, int lo, int hi);
};


/**
 * @class GnomeSort
 * @brief The GnomeSort template class. Complexity: O(n*n).
 */
template <typename T>
class GnomeSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};


// ------------------------------------------------------------------------------------------
// ---------------- Selection sort algorithms -----------------------------------------------
// ------------------------------------------------------------------------------------------


/**
 * @class SelectionSort
 * @brief The SelectionSort template class. Complexity: O(n*n).
 */
template <typename T>
class SelectionSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};


/**
 * @class HeapSort
 * @brief The HeapSort template class. Complexity: O(n*log(n)).
 */
template <typename T>
class HeapSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
private:
    static void sink(std::vector<T> & elements, int pos, int length);
};


// ------------------------------------------------------------------------------------------
// ---------------- Insertion sort algorithms -----------------------------------------------
// ------------------------------------------------------------------------------------------

/**
 * @class InsertionSort
 * @brief The InsertionSort template class. Complexity: O(n*n).
 */
template <typename T>
class InsertionSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);
    /**
     * @brief Sorts elements in the container.
     * @param[in] array container with the elements
     * @param[in] length length of the array
     */
    static void sort(T * array, int length);
    /// class name
    static char const * name;
};


/**
 * @class ShellSort
 * @brief The ShellSort template class. Complexity: O(n*log(n)*log(n)).
 */
template <typename T>
class ShellSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};



// ------------------------------------------------------------------------------------------
// ---------------- Merging sort algorithms -------------------------------------------------
// ------------------------------------------------------------------------------------------

/**
 * @class MergeSort
 * @brief The MergeSort template class. Complexity: O(n*log(n)).
 */
template <typename T>
class MergeSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        std::vector<T> aux(elements.size());
        sort(elements, 0, static_cast<int>(elements.size()) - 1, aux);
    }

    /// class name
    static char const * name;
private:
    /**
     * @brief Sorts elements in the container and copies its into aux.
     * @param[in] elements container with the elements
     * @param[in] lo left boundary
     * @param[in] hi right boundary
     * @param[out] aux container
     *
     * @note bounders lo and hi should be signed type
     */
    static void sort(std::vector<T> & elements, int lo, int hi, std::vector<T> & aux);

    static void merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux);
};


/**
 * @class MergeUpSort
 * @brief The MergeUpSort template class. Complexity: O(n*log(n)).
 */
template <typename T>
class MergeUpSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        std::vector<T> aux(elements.size());
        sort(elements, static_cast<int>(elements.size()), aux);
    }

    /// class name
    static char const * name;
private:
    // NOTE: bounders lo and hi should be signed type
    static void sort(std::vector<T> & elements, int length, std::vector<T> & aux);

    // merge function is the same as in the merge sort algorithm
    static void merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux);
};



// ------------------------------------------------------------------------------------------
// ---------------- Hybrid sort algorithms --------------------------------------------------
// ------------------------------------------------------------------------------------------


/**
 * @class QuickInsSort
 * @brief The QuickInsSort template class. Complexity: average O(n*log(n)), worst O(n*n).
 */
template <typename T>
class QuickInsSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        sort(elements, 0, static_cast<int>(elements.size()) - 1);
    }

    /// class name
    static char const * name;
private:
    // NOTE: bounders lo and hi should be signed type
    static void sort(std::vector<T> & elements, int lo, int hi);

    static int partition(std::vector<T> & elements, int lo, int hi);
};


/**
 * @class MergeInsSort
 * @brief The MergeInsSort template class. Complexity: O(n*log(n)).
 */
template <typename T>
class MergeInsSort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements)
    {
        std::vector<T> aux(elements.size());
        sort(elements, 0, static_cast<int>(elements.size()) - 1, aux);
    }

    /// class name
    static char const * name;
private:
    // NOTE: bounders lo and hi should be signed type
    static void sort(std::vector<T> & elements, int lo, int hi, std::vector<T> & aux);

    static void merge(std::vector<T> & elements, int lo, int mid, int hi, std::vector<T> & aux);
};


/**
 * @class InsertionBinarySort
 * @brief The InsertionBinarySort template class. Complexity: O(n*n).
 */
template <typename T>
class InsertionBinarySort
{
public:
    /**
     * @brief Sorts elements in the container.
     * @param[in] elements container with the elements
     */
    static void sort(std::vector<T> & elements);

    /// class name
    static char const * name;
};

} // namespace sort

//--------------------------------------------------------------------------------------------------
#endif // SORT_HPP
//--------------------------------------------------------------------------------------------------
