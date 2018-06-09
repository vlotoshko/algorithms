//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   08-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTREGISTRY_HPP
#define TESTREGISTRY_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Sort/TestSort.hpp"
#include "Search/TestUnionFind.hpp"

//--------------------------------------------------------------------------------------------------

namespace registry
{

enum class AlgCategory : int
{
    SORT = 0,
    UNION_FIND,
    BINARY_SEARCH_TREE,
    GRAPH,
    UNKNOWN,
};

AlgCategory getAlgCategory(unsigned id)
{
    if (id < 100)     // range [0, 100)
    {
        return AlgCategory::SORT;
    }
    else if(id < 200) // range [100, 200)
    {
        return AlgCategory::UNION_FIND;
    }
    else if(id < 300) // range [200, 300)
    {
        return AlgCategory::BINARY_SEARCH_TREE;
    }
    else if(id < 400) // range [300, 400)
    {
        return AlgCategory::GRAPH;
    }

    return AlgCategory::UNKNOWN;
}


template <typename T>
bool algorithmExists(unsigned id)
{
    auto category = getAlgCategory(id);
    switch (category)
    {
    case AlgCategory::SORT:
        return sort::TestSort<T>::Algorithms.find(static_cast<sort::AlgId>(id))
                != sort::TestSort<T>::Algorithms.end();
    case AlgCategory::UNION_FIND:
        return uf::TestUnionFind<T>::Algorithms.find(static_cast<uf::AlgId>(id))
                != uf::TestUnionFind<T>::Algorithms.end();
    case AlgCategory::BINARY_SEARCH_TREE:
        return true;
    case AlgCategory::GRAPH:
    case AlgCategory::UNKNOWN:
        return false;
    }
}

// ------------------------------------------------------------------------------------------
// Hold input application parameters
//
struct TestSettings
{
    AlgCategory categoryId;
    unsigned    algId;
    unsigned    repeatTimes;
    unsigned    elementsCount;

    std::string fileName;

    static const char * hello;
    static void usage();
};


// ------------------------------------------------------------------------------------------
// Pasres input app parameter to a convinient structure
//
TestSettings getParameters(int argc, char *argv[]);

void TestSettings::usage()
{
    std::cout << hello << std::endl;
//    for (auto & item: sort::TestSort<T>::Algorithms)
//    {
//        std::cout << std::setw(3) << static_cast<int>(item.first) <<  ":\t"
//                  << item.second->name() << std::endl;
//    }
}

const char * TestSettings::hello =
        "Usage: algorithm X Y Z\n"
        "Where:\n"
        "  X - number of the algorithm\n"
        "  Y - repeat count, algorithm will be invoked Y times, doubling its element count each time\n"
        "  Z - initial elements count\n"
        "Sort algorithms:";

TestSettings getParameters(int argc, char *argv[])
{
    TestSettings parameters{};

    if (argc > 1)
    {
        parameters.algId = static_cast<unsigned>(atoi(argv[1]));
        parameters.categoryId = getAlgCategory(parameters.algId);
    }

    switch (parameters.categoryId)
    {
    case AlgCategory::SORT:
    case AlgCategory::UNION_FIND:
        if (argc > 3)
        {
            parameters.repeatTimes = static_cast<unsigned>(atoi(argv[2]));
            parameters.elementsCount = static_cast<unsigned>(atoi(argv[3]));
        }
        break;
    case AlgCategory::BINARY_SEARCH_TREE:
        if (argc > 2)
        {
            parameters.fileName = argv[2];
        }
        break;
    case AlgCategory::GRAPH:
    case AlgCategory::UNKNOWN:
        break;
    }

    return parameters;
}

} // namespace registry
//--------------------------------------------------------------------------------------------------
#endif // TESTREGISTRY_HPP
//--------------------------------------------------------------------------------------------------
