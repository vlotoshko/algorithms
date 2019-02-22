/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef TESTSORT_HPP
#define TESTSORT_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort_Impl.hpp"

// TODO: Check and remove unused headers
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------

namespace tests
{

/**
 * @class TestIsSorted
 * @brief The TestIsSorted template class tests whether container is sorted.
 * @tparam T type of the container elements
 */
template <typename T>
class TestIsSorted : public CppUnit::TestFixture
{
public:
    /**
     * @brief suite implements implicit intreface for the TestSuiteFactory.
     * @return test suite for the current tests.
     */
    static CppUnit::TestSuite * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("TestIsSorted");

        suiteOfTests->addTest(new CppUnit::ExceptionTestCaseDecorator<CppUnit::Exception>(
                                   new CppUnit::TestCaller<TestIsSorted<T>>(
                                       "isSorted_ShouldFail_WhenGivenUnSortedContainer",
                                       &TestIsSorted::isSorted_ShouldFail_WhenGivenUnSortedContainer)));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestIsSorted<T>>(
                                  "isSorted_ShouldReturnTrue_WhenGivenSortedContainer",
                                  &TestIsSorted::isSorted_ShouldReturnTrue_WhenGivenSortedContainer));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestIsSorted<T>>(
                                  "isSorted_ShouldReturnTrue_WhenGivenContainerHasEqualElements",
                                  &TestIsSorted::isSorted_ShouldReturnTrue_WhenGivenContainerHasEqualElements));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestIsSorted<T>>(
                                  "isSorted_ShouldReturnTrue_WhenGivenContainerHasSameElement",
                                  &TestIsSorted::isSorted_ShouldReturnTrue_WhenGivenContainerHasSameElement));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestIsSorted<T>>(
                                  "isSorted_ShouldReturnTrue_WhenGivenContainerIsEmpty",
                                  &TestIsSorted::isSorted_ShouldReturnTrue_WhenGivenContainerIsEmpty));
        return suiteOfTests;
    }
protected:
    /**
     * @brief isSorted_ShouldFail_WhenGivenUnSortedContainer tests whether elements
     * are not sorted.
     */
    void isSorted_ShouldFail_WhenGivenUnSortedContainer()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{1,7,3,4,5}));
    }

    /**
     * @brief isSorted_ShouldReturnTrue_WhenGivenSortedContainer test whether elements
     * are sorted.
     */
    void isSorted_ShouldReturnTrue_WhenGivenSortedContainer()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{1,2,3,4,5}));
    }

    /**
     * @brief isSorted_ShouldReturnTrue_WhenGivenContainerHasEqualElements test whether
     * elements are sorted.
     */
    void isSorted_ShouldReturnTrue_WhenGivenContainerHasEqualElements()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{1,2,2,2,3,4,5}));
    }

    /**
     * @brief isSorted_ShouldReturnTrue_WhenGivenContainerHasSameElement test whether
     * elements are sorted.
     */
    void isSorted_ShouldReturnTrue_WhenGivenContainerHasSameElement()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{2,2,2}));
    }

    /**
     * @brief isSorted_ShouldReturnTrue_WhenGivenContainerIsEmpty test whether elements
     * are sorted.
     */
    void isSorted_ShouldReturnTrue_WhenGivenContainerIsEmpty()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{}));
    }
};

/**
 * @class TestSortAlgorithms
 * @brief The TestSortAlgorithms template class tests sort algorithms.
 * @tparam SortAlg type of the sort algorithm
 * @tparam T type of the container elements
 */
template <template <typename> class SortAlg, typename T>
class TestSortAlgorithms : public CppUnit::TestFixture
{
public:
    /**
     * @brief setUp sets up sorted and unsorted arrays for the test cases.
     */
    void setUp() override
    {
        sorted   = {1,2,3,4,5,6,7};
        unsorted = {5,7,3,4,7,9,2};
    }

    /**
     * @brief suite implements implicit intreface for the TestSuiteFactory.
     * @return test suite for the current tests.
     */
    static CppUnit::TestSuite * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite(SortAlg<T>::name);
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSortAlgorithms<SortAlg, T>>(
                                  "sort_ShouldReturnSorted_WhenGivenSortedContainer",
                                  &TestSortAlgorithms::sort_ShouldReturnSorted_WhenGivenSortedContainer));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestSortAlgorithms<SortAlg, T>>(
                                  "sort_ShouldReturnSorted_WhenGivenUnsortedContainer",
                                  &TestSortAlgorithms::sort_ShouldReturnSorted_WhenGivenUnsortedContainer));
        return suiteOfTests;
    }

protected:
    /**
     * @brief sort_ShouldReturnSorted_WhenGivenSortedContainer tests whether sorted elements
     * remains sorted.
     */
    void sort_ShouldReturnSorted_WhenGivenSortedContainer()
    {
        SortAlg<T>().sort(sorted);
        CPPUNIT_ASSERT_EQUAL(sorted[0], static_cast<T>(1));
        CPPUNIT_ASSERT_EQUAL(sorted[1], static_cast<T>(2));
        CPPUNIT_ASSERT_EQUAL(sorted[2], static_cast<T>(3));
        CPPUNIT_ASSERT_EQUAL(sorted[3], static_cast<T>(4));
        CPPUNIT_ASSERT_EQUAL(sorted[4], static_cast<T>(5));
        CPPUNIT_ASSERT_EQUAL(sorted[5], static_cast<T>(6));
        CPPUNIT_ASSERT_EQUAL(sorted[6], static_cast<T>(7));
    }

    /**
     * @brief sort_ShouldReturnSorted_WhenGivenUnsortedContainer test whether elements
     * become sorted.
     */
    void sort_ShouldReturnSorted_WhenGivenUnsortedContainer()
    {
        SortAlg<T>().sort(unsorted);
        CPPUNIT_ASSERT_EQUAL(unsorted[0], static_cast<T>(2));
        CPPUNIT_ASSERT_EQUAL(unsorted[1], static_cast<T>(3));
        CPPUNIT_ASSERT_EQUAL(unsorted[2], static_cast<T>(4));
        CPPUNIT_ASSERT_EQUAL(unsorted[3], static_cast<T>(5));
        CPPUNIT_ASSERT_EQUAL(unsorted[4], static_cast<T>(7));
        CPPUNIT_ASSERT_EQUAL(unsorted[5], static_cast<T>(7));
        CPPUNIT_ASSERT_EQUAL(unsorted[6], static_cast<T>(9));
    }

private:
    std::vector<T> sorted;
    std::vector<T> unsorted;
};


// Had to use aliases for the test suite registration, because in this particulat case
// preprocessor does not accept templates with more that 1 parameter

/// @brief The template class TestDummySort tests dummy sort algorithm
template<typename T> using TestDummySort           = TestSortAlgorithms<sort::DummySort, T>;
/// @brief The template class TestBubleSort tests buble sort algorithm
template<typename T> using TestBubleSort           = TestSortAlgorithms<sort::BubleSort, T>;
/// @brief The template class TestCombSort tests comb sort algorithm
template<typename T> using TestCombSort            = TestSortAlgorithms<sort::CombSort, T>;
/// @brief The template class TestShakeSort tests shake sort algorithm
template<typename T> using TestShakeSort           = TestSortAlgorithms<sort::ShakeSort, T>;
/// @brief The template class TestQuickSort tests quick sort algorithm
template<typename T> using TestQuickSort           = TestSortAlgorithms<sort::QuickSort, T>;
/// @brief The template class TestQuickSortM tests quick sort median algorithm
template<typename T> using TestQuickSortM          = TestSortAlgorithms<sort::QuickSortM, T>;
/// @brief The template class TestQuick3Sort tests quick sort 3part algorithm
template<typename T> using TestQuick3Sort          = TestSortAlgorithms<sort::Quick3Sort, T>;
/// @brief The template class TestGnomeSort tests gnome sort algorithm
template<typename T> using TestGnomeSort           = TestSortAlgorithms<sort::GnomeSort, T>;
/// @brief The template class TestSelectionSort tests selection sort algorithm
template<typename T> using TestSelectionSort       = TestSortAlgorithms<sort::SelectionSort, T>;
/// @brief The template class TestHeapSort tests heap sort algorithm
template<typename T> using TestHeapSort            = TestSortAlgorithms<sort::HeapSort, T>;
/// @brief The template class TestInsertionySort tests insertion sort algorithm
template<typename T> using TestInsertionySort      = TestSortAlgorithms<sort::InsertionSort, T>;
/// @brief The template class TestMergeSort tests merge sort algorithm
template<typename T> using TestMergeSort           = TestSortAlgorithms<sort::MergeSort, T>;
/// @brief The template class TestMergeUpSort tests merge-up sort algorithm
template<typename T> using TestMergeUpSort         = TestSortAlgorithms<sort::MergeUpSort, T>;
/// @brief The template class TestQuickInsSort tests quick-ins sort algorithm
template<typename T> using TestQuickInsSort        = TestSortAlgorithms<sort::QuickInsSort, T>;
/// @brief The template class TestMergeInsSort tests merge-ins sort algorithm
template<typename T> using TestMergeInsSort        = TestSortAlgorithms<sort::MergeInsSort, T>;
/// @brief The template class TestInsertionBinarySort tests insertion-binary sort algorithm
template<typename T> using TestInsertionBinarySort = TestSortAlgorithms<sort::InsertionBinarySort, T>;

} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // TESTSORT_HPP
//--------------------------------------------------------------------------------------------------
