/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 19-Oct-2020
 */

//--------------------------------------------------------------------------------------------------
#include "catch2/catch.hpp"
#include "Sort_Impl.hpp"
//--------------------------------------------------------------------------------------------------

namespace tests
{

SCENARIO( "isSorted tool testing", "[tools]" ) {

    GIVEN( "Unsorted container with some items" ) {
        std::vector<int> v = {1,7,3,4,5};
        WHEN( "Container is unsorted" ) {
            THEN( "isSorted returns false" ) { REQUIRE_FALSE( tools::isSorted(v) ); }
        }
    }
    GIVEN( "Sorted container with some items" ) {
        std::vector<int> v = {1,2,3,4,5};
        WHEN( "Container is sorted" ) {
            THEN( "isSorted returns true" ) { REQUIRE( tools::isSorted(v) ); }
        }
    }
    GIVEN( "Usnorted container with not unique items" ) {
        std::vector<int> v = {1,2,2,3,3,4,5,3};
        WHEN( "Container with duplicates is unsorted" ) {
            THEN( "isSorted returns false" ) { REQUIRE_FALSE( tools::isSorted(v) ); }
        }
    }
    GIVEN( "Sorted container with not unique items" ) {
        std::vector<int> v = {1,2,2,3,3,4,5};
        WHEN( "Container with duplicates is sorted" ) {
            THEN( "isSorted returns true" ) { REQUIRE( tools::isSorted(v) ); }
        }
    }
    GIVEN( "Container with all equal items" ) {
        std::vector<int> v = {3,3,3,3};
        WHEN( "Container with duplicates is sorted" ) {
            THEN( "isSorted returns true" ) { REQUIRE( tools::isSorted(v) ); }
        }
    }
    GIVEN( "Empty container" ) {
        std::vector<int> v = {3,3,3,3};
        WHEN( "Container is empty" ) {
            THEN( "isSorted returns true" ) { REQUIRE( tools::isSorted(v) ); }
        }
    }
}

SCENARIO( "Sort unsorted vector", "[sort]" ) {

    GIVEN( "Unsorted vector with some items" ) {
        std::vector<int> v = {5,7,3,4,7,9,2};

        WHEN( "Dummy sort algorithm applied" ) {
            sort::DummySort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Buble sort algorithm applied" ) {
            sort::BubleSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Comb sort algorithm applied" ) {
            sort::CombSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Shake sort algorithm applied" ) {
            sort::ShakeSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Quick sort algorithm applied" ) {
            sort::QuickSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Quick-sort-median algorithm applied" ) {
            sort::QuickSortM<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Quick-sort-3parts sort algorithm applied" ) {
            sort::Quick3Sort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Gnome sort algorithm applied" ) {
            sort::GnomeSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Selection sort algorithm applied" ) {
            sort::SelectionSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Heap sort algorithm applied" ) {
            sort::HeapSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Insertion sort algorithm applied" ) {
            sort::InsertionSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "Merge sort algorithm applied" ) {
            sort::MergeSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "MergeUp sort algorithm applied" ) {
            sort::MergeUpSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "QuickIns sort algorithm applied" ) {
            sort::QuickInsSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "MergeIns sort algorithm applied" ) {
            sort::MergeInsSort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
        WHEN( "InsertionBinary sort algorithm applied" ) {
            sort::InsertionBinarySort<int>().sort(v);
            THEN( "Vector becomes sorted" ) { REQUIRE( tools::isSorted(v) ); }
        }
    }
}

} // namespace tests
