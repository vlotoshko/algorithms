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

enum class AlgCategoty : int
{
    SORT = 0,
    UNION_FIND,
    BINARY_SEARCH_TREE,
    GRAPH,
    UNKNOWN,
};

AlgCategoty getAlgCategory(unsigned id)
{
    if (id < 100)     // range [0, 100)
    {
        return AlgCategoty::SORT;
    }
    else if(id < 200) // range [100, 200)
    {
        return AlgCategoty::UNION_FIND;
    }
    else if(id < 300) // range [200, 300)
    {
        return AlgCategoty::BINARY_SEARCH_TREE;
    }
    else if(id < 400) // range [300, 400)
    {
        return AlgCategoty::GRAPH;
    }

    return AlgCategoty::UNKNOWN;
}


template <typename T>
bool algorithmExists(unsigned id)
{
    auto category = getAlgCategory(id);
    switch (category)
    {
    case AlgCategoty::SORT:
        return sort::TestSort<T>::Algorithms.find(static_cast<sort::AlgId>(id))
                != sort::TestSort<T>::Algorithms.end();
    case AlgCategoty::UNION_FIND:
        return uf::TestUnionFind<T>::Algorithms.find(static_cast<uf::AlgId>(id))
                != uf::TestUnionFind<T>::Algorithms.end();
    case AlgCategoty::BINARY_SEARCH_TREE:
    case AlgCategoty::GRAPH:
    case AlgCategoty::UNKNOWN:
        return false;
    }
}

// ------------------------------------------------------------------------------------------
// Hold input application parameters
//
struct InputParameters
{
    AlgCategoty categoryId;
    unsigned algId;
    unsigned repeatCount;
    unsigned elementsCount;
    std::string fileName;
    static const char * hello;
    static void usage();
};


// ------------------------------------------------------------------------------------------
// Pasres input app parameter to a convinient structure
//
InputParameters getParameters(int argc, char *argv[]);

void InputParameters::usage()
{
    std::cout << hello << std::endl;
//    for (auto & item: sort::TestSort<T>::Algorithms)
//    {
//        std::cout << std::setw(3) << static_cast<int>(item.first) <<  ":\t"
//                  << item.second->name() << std::endl;
//    }
}

const char * InputParameters::hello =
        "Usage: algorithm X Y Z\n"
        "Where:\n"
        "  X - number of the algorithm\n"
        "  Y - repeat count, algorithm will be invoked Y times, doubling its element count each time\n"
        "  Z - initial elements count\n"
        "Sort algorithms:";

InputParameters getParameters(int argc, char *argv[])
{
    InputParameters parameters{};

    if (argc > 1)
    {
        parameters.algId = static_cast<unsigned>(atoi(argv[1]));
        parameters.categoryId = getAlgCategory(parameters.algId);
    }

    switch (parameters.categoryId)
    {
    case AlgCategoty::SORT:
    case AlgCategoty::UNION_FIND:
        if (argc > 3)
        {
            parameters.repeatCount = static_cast<unsigned>(atoi(argv[2]));
            parameters.elementsCount = static_cast<unsigned>(atoi(argv[3]));
        }
        break;
    case AlgCategoty::BINARY_SEARCH_TREE:
        if (argc > 2)
        {
            parameters.fileName = argv[2];
        }
        break;
    case AlgCategoty::GRAPH:
    case AlgCategoty::UNKNOWN:
        break;
    }

    return parameters;
}

} // namespace registry
//--------------------------------------------------------------------------------------------------
#endif // TESTREGISTRY_HPP
//--------------------------------------------------------------------------------------------------
