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
    explicit SortBmAble (size_t c = 100) : elementsCount_(c), elementsCountInitial_(c) {
        init();
    }
    void init() override { tools::randomData<T>(elements_, elementsCount_, 0, 10000); }
    void reset() override { elementsCount_ = elementsCountInitial_; }
    void doubleData() override {
        elementsCount_ += elementsCount_;
        init();
    }
    void doSomeHeavy() override { SortAlg<T>::sort(elements_); }
private:
    std::vector<T> elements_;
    size_t elementsCount_;
    size_t elementsCountInitial_;
};

class BmSort : public CppUnit::TestFixture
{
public:
    BmSort() : settings_() {}
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

    void setUp() override
    {
        settings_.reset(new BenchmarkSettings(0.01, 5, 10, std::make_unique<InterruptByTime>(900)));
    }

protected:
    ///
    void dummySort()
    {
        auto test = std::make_unique<SortBmAble<sort::DummySort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void bubleSort()
    {
        auto test = std::make_unique<SortBmAble<sort::BubleSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void combSort()
    {
        auto test = std::make_unique<SortBmAble<sort::CombSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void shakeSort()
    {
        auto test = std::make_unique<SortBmAble<sort::BubleSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void quickSort()
    {
        std::unique_ptr<IBenchmarkable> ex (new SortBmAble<sort::QuickSort, size_t>);
        auto test = std::make_unique<SortBmAble<sort::QuickSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void quickSortM()
    {
        auto test = std::make_unique<SortBmAble<sort::QuickSortM, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void quick3Sort()
    {
        auto test = std::make_unique<SortBmAble<sort::Quick3Sort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void gnomeSort()
    {
        auto test = std::make_unique<SortBmAble<sort::GnomeSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void selectionSort()
    {
        auto test = std::make_unique<SortBmAble<sort::SelectionSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void heapSort()
    {
        auto test = std::make_unique<SortBmAble<sort::HeapSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void insertionSort()
    {
        auto test = std::make_unique<SortBmAble<sort::InsertionSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void mergeSort()
    {
        auto test = std::make_unique<SortBmAble<sort::MergeSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void mergeUpSort()
    {
        auto test = std::make_unique<SortBmAble<sort::BubleSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void quickInsSort()
    {
        auto test = std::make_unique<SortBmAble<sort::QuickInsSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void mergeInsSort()
    {
        auto test = std::make_unique<SortBmAble<sort::MergeInsSort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

    ///
    void insertionBinarySort()
    {
        auto test = std::make_unique<SortBmAble<sort::InsertionBinarySort, size_t>>();
        Benchmark(std::move(test), std::move(settings_)).run();
    }

private:
    std::unique_ptr<BenchmarkSettings> settings_;
};


} // namespace benchmark

//--------------------------------------------------------------------------------------------------
#endif // BMSORT_HPP
//--------------------------------------------------------------------------------------------------
