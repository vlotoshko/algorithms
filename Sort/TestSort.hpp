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
#include "Sort/Sort.hpp"

#include <map>
#include <memory>
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
    using Alg = std::shared_ptr<ISortable<T>>;
    TestSort(AlgId algId, size_t count) : algId_(algId), elementsCount_(count) {}

    void runTest(tools::Timer & timer) override
    {
        auto iter = Algorithms.find(algId_);
        if(iter != Algorithms.end())
        {
            // Generate elements
            std::vector<T> elements(elementsCount_);
//            std::cout << "generating data... " << std::flush;
            tools::randomData(elements, elementsCount_, 1, 1000);
//            std::cout << "Ok" << std::endl;

            // Sort
//            tools::show(elements);
            timer.start();
            iter->second->sort(elements);
            std::cout << iter->second->name() << std::endl;
//            tools::show(elements);
        }
    }
    static std::map<AlgId, Alg> Algorithms;
private:
    AlgId algId_;
    size_t elementsCount_;
};


// ------------------------------------------------------------------------------------------
// Registry of the sort algorithms
//
template <typename T>
std::map<AlgId, typename TestSort<T>::Alg> TestSort<T>::Algorithms =
{
      {AlgId::SORT_DUMMY,     std::make_shared<DummySort<T>>()}
    , {AlgId::SORT_BUBLE,     std::make_shared<BubleSort<T>>()}
    , {AlgId::SORT_COMB,      std::make_shared<CombSort<T>>()}
    , {AlgId::SORT_SHAKE,     std::make_shared<ShakeSort<T>>()}
    , {AlgId::SORT_QUICK,     std::make_shared<QuickSort<T>>()}
    , {AlgId::SORT_QUICKM,    std::make_shared<QuickSortM<T>>()}
    , {AlgId::SORT_QUICK3,    std::make_shared<Quick3Sort<T>>()}
    , {AlgId::SORT_GNOME,     std::make_shared<GnomeSort<T>>()}
    , {AlgId::SORT_SELECTION, std::make_shared<SelectionSort<T>>()}
    , {AlgId::SORT_HEAP,      std::make_shared<HeapSort<T>>()}
    , {AlgId::SORT_INSERTION, std::make_shared<InsertionSort<T>>()}
    , {AlgId::SORT_SHELL,     std::make_shared<ShellSort<T>>()}
    , {AlgId::SORT_MERGE,     std::make_shared<MergeSort<T>>()}
    , {AlgId::SORT_MERGE_UP,  std::make_shared<MergeUpSort<T>>()}
    , {AlgId::SORT_QUICK_INS, std::make_shared<QuickInsSort<T>>()}
    , {AlgId::SORT_MERGE_INS, std::make_shared<MergeInsSort<T>>()}
//    , {SortId::SORT_INSERTION_BIN, std::make_shared<InsertionBinarySort<T>>()}
};

} // namespace sort

//--------------------------------------------------------------------------------------------------
#endif // TESTSORT_HPP
//--------------------------------------------------------------------------------------------------
