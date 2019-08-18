/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 18-Aug-2019
 */

//--------------------------------------------------------------------------------------------------
#ifndef BMSORT_HPP
#define BMSORT_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort_Impl.hpp"
#include "Benchmark.hpp"

#include "vector"
#include "memory"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
//--------------------------------------------------------------------------------------------------

namespace benchmark
{


template<template<typename> class SortAlg, typename T>
class SortBmAble : public BenchmarkableBase
{
public:
    explicit SortBmAble (size_t c = 100) : elementsCount_(c) {
        init();
    }
    void init() override { tools::randomData<T>(elements_, elementsCount_, 0, 10000); }
    void doubleData() override {
        elementsCount_ += elementsCount_;
        init();
    }
    void doSomeHeavy() override { SortAlg<T>::sort(elements_); }
private:
    std::vector<T> elements_;
    size_t elementsCount_;
};

class BmSort : public CppUnit::TestFixture
{
public:
    BmSort() = default;

    /**
     * @brief suite implements implicit intreface for the TestSuiteFactory.
     * @return test suite for the current tests.
     */
    static CppUnit::TestSuite * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Benchmark sort");
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("DummySort", &BmSort::dummySort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("BubleSorb", &BmSort::bubleSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("CombSort", &BmSort::combSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("ShakeSort", &BmSort::shakeSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("QuickSort", &BmSort::quickSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("QuickSortM", &BmSort::quickSortM));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("Quick3Sort", &BmSort::quick3Sort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("GnomeSort", &BmSort::gnomeSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("SelectionSort", &BmSort::selectionSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("HeapSort", &BmSort::heapSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("InsertionSort", &BmSort::insertionSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("MergeSort", &BmSort::mergeSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("MergeUpSort", &BmSort::mergeUpSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("QuickInsSort", &BmSort::quickInsSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("MergeInsSort", &BmSort::mergeInsSort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BmSort>("InsertionBinarySort", &BmSort::insertionBinarySort));

        return suiteOfTests;
    }


protected:
    ///
    void dummySort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::DummySort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void bubleSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::BubleSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void combSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::CombSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void shakeSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::ShakeSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void quickSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::QuickSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void quickSortM()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::QuickSortM, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void quick3Sort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::Quick3Sort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void gnomeSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::GnomeSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void selectionSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::SelectionSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void heapSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::HeapSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void insertionSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::InsertionSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void mergeSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::MergeSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void mergeUpSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::MergeUpSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void quickInsSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::QuickInsSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void mergeInsSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::MergeInsSort, size_t>);
        Benchmark(std::move(ex)).run();
    }

    ///
    void insertionBinarySort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::InsertionBinarySort, size_t>);
        Benchmark(std::move(ex)).run();
    }
};


} // namespace benchmark

//--------------------------------------------------------------------------------------------------
#endif // BMSORT_HPP
//--------------------------------------------------------------------------------------------------
