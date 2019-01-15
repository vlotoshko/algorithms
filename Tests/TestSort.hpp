//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTSORT_HPP
#define TESTSORT_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ITestable.hpp"
#include "Sort.hpp"

// TODO: Check and remove unused headers
#include <map>
#include <memory>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------

namespace sort
{

enum class AlgId : int
{
    // Change sorts
    SORT_DUMMY = 0,
    SORT_BUBLE,
    SORT_COMB,
    SORT_SHAKE,
    SORT_QUICK,
    SORT_QUICKM, // 5
    SORT_QUICK3,
    SORT_GNOME,

    // Selection sorts
    SORT_SELECTION,
    SORT_HEAP,

    // Insertion sorts
    SORT_INSERTION, //10
    SORT_SHELL,

    // Merge sorts
    SORT_MERGE,
    SORT_MERGE_UP,

    // Hybrid sorts
    SORT_QUICK_INS,
    SORT_MERGE_INS, // 15
    SORT_INSERTION_BIN,
};


// ------------------------------------------------------------------------------------------
// Runs sort algorithm specified by the algorithm's id
//
template <typename T>
class TestSort : public ITestable
{
public:
//    using Alg = std::shared_ptr<ISortable<T>>;
    TestSort(AlgId algId, size_t count) : algId_(algId), elementsCount_(count) {}

    void runTest(tools::Timer & timer) override
    {
//        auto iter = Algorithms.find(algId_);
//        if (iter != Algorithms.end())
//        {
//            // Generate elements
//            std::vector<T> elements(elementsCount_);
////            std::cout << "generating data... " << std::flush;
//            tools::randomData(elements, elementsCount_, 1, 1000);
////            std::cout << "Ok" << std::endl;

//            // Sort
////            tools::show(elements);
//            timer.start();
//            iter->second->sort(elements);
////            std::cout << iter->second->name() << std::endl;
////            tools::show(elements);
//        }
    }
//    static std::map<AlgId, Alg> Algorithms;
private:
    AlgId algId_;
    size_t elementsCount_;
};


// ------------------------------------------------------------------------------------------
// Registry of the sort algorithms
//
//template <typename T>
//std::map<AlgId, typename TestSort<T>::Alg> TestSort<T>::Algorithms =
//{
//      {AlgId::SORT_DUMMY,     std::make_shared<DummySort<T>>()}
//    , {AlgId::SORT_BUBLE,     std::make_shared<BubleSort<T>>()}
//    , {AlgId::SORT_COMB,      std::make_shared<CombSort<T>>()}
//    , {AlgId::SORT_SHAKE,     std::make_shared<ShakeSort<T>>()}
//    , {AlgId::SORT_QUICK,     std::make_shared<QuickSort<T>>()}
//    , {AlgId::SORT_QUICKM,    std::make_shared<QuickSortM<T>>()}
//    , {AlgId::SORT_QUICK3,    std::make_shared<Quick3Sort<T>>()}
//    , {AlgId::SORT_GNOME,     std::make_shared<GnomeSort<T>>()}
//    , {AlgId::SORT_SELECTION, std::make_shared<SelectionSort<T>>()}
//    , {AlgId::SORT_HEAP,      std::make_shared<HeapSort<T>>()}
//    , {AlgId::SORT_INSERTION, std::make_shared<InsertionSort<T>>()}
//    , {AlgId::SORT_SHELL,     std::make_shared<ShellSort<T>>()}
//    , {AlgId::SORT_MERGE,     std::make_shared<MergeSort<T>>()}
//    , {AlgId::SORT_MERGE_UP,  std::make_shared<MergeUpSort<T>>()}
//    , {AlgId::SORT_QUICK_INS, std::make_shared<QuickInsSort<T>>()}
//    , {AlgId::SORT_MERGE_INS, std::make_shared<MergeInsSort<T>>()}
//    , {SortId::SORT_INSERTION_BIN, std::make_shared<InsertionBinarySort<T>>()}
//};

} // namespace sort



namespace tests
{

template <typename T>
class TestIsSorted : public CppUnit::TestFixture
{
public:
    static CppUnit::Test * suite()
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
    void isSorted_ShouldFail_WhenGivenUnSortedContainer()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{1,7,3,4,5}));
    }

    void isSorted_ShouldReturnTrue_WhenGivenSortedContainer()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{1,2,3,4,5}));
    }

    void isSorted_ShouldReturnTrue_WhenGivenContainerHasEqualElements()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{1,2,2,2,3,4,5}));
    }

    void isSorted_ShouldReturnTrue_WhenGivenContainerHasSameElement()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{2,2,2}));
    }

    void isSorted_ShouldReturnTrue_WhenGivenContainerIsEmpty()
    {
        CPPUNIT_ASSERT(tools::isSorted<std::vector>(std::vector<T>{}));
    }
};


template <template <typename> class SortAlg, typename T>
class TestSortAlgorithms : public CppUnit::TestFixture
{
public:
    void setUp()
    {
        sorted   = {1,2,3,4,5,6,7};
        unsorted = {5,7,3,4,7,9,2};
    }

    static CppUnit::Test * suite()
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
template<typename T> using TestDummySort           = TestSortAlgorithms<sort::DummySort, T>;
template<typename T> using TestBubleSort           = TestSortAlgorithms<sort::BubleSort, T>;
template<typename T> using TestCombSort            = TestSortAlgorithms<sort::CombSort, T>;
template<typename T> using TestShakeSort           = TestSortAlgorithms<sort::ShakeSort, T>;
template<typename T> using TestQuickSort           = TestSortAlgorithms<sort::QuickSort, T>;
template<typename T> using TestQuickSortM          = TestSortAlgorithms<sort::QuickSortM, T>;
template<typename T> using TestQuick3Sort          = TestSortAlgorithms<sort::Quick3Sort, T>;
template<typename T> using TestGnomeSort           = TestSortAlgorithms<sort::GnomeSort, T>;
template<typename T> using TestSelectionSort       = TestSortAlgorithms<sort::SelectionSort, T>;
template<typename T> using TestHeapSort            = TestSortAlgorithms<sort::HeapSort, T>;
template<typename T> using TestInsertionySort      = TestSortAlgorithms<sort::InsertionSort, T>;
template<typename T> using TestMergeSort           = TestSortAlgorithms<sort::MergeSort, T>;
template<typename T> using TestMergeUpSort         = TestSortAlgorithms<sort::MergeUpSort, T>;
template<typename T> using TestQuickInsSort        = TestSortAlgorithms<sort::QuickInsSort, T>;
template<typename T> using TestMergeInsSort        = TestSortAlgorithms<sort::MergeInsSort, T>;
template<typename T> using TestInsertionBinarySort = TestSortAlgorithms<sort::InsertionBinarySort, T>;


} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // TESTSORT_HPP
//--------------------------------------------------------------------------------------------------
