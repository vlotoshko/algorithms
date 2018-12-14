cmake_minimum_required(VERSION 2.8.12)

project(algorithms)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(LINKER_FLAGS "-pthread")
set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS})

include_directories(Search)
include_directories(Sort)
include_directories(Structures)

set(CPP_FILES
    "Search/GraphAlgorithms.cpp"
    "Search/MinimalSpanningTree.cpp"
    "Search/ShortPathes.cpp"
    "Structures/EdgeWeightedGraph.cpp"
    "Structures/Graph.cpp"
    "Structures/TestGraph.cpp"
    "tools.cpp"
    "main.cpp"
    )

set(HPP_FILES
    "ITestable.hpp"
    "TestRegistry.hpp"
    "TestFactory.hpp"
    "tools.hpp"
    "Search/GraphAlgorithms.hpp"
    "Search/MinimalSpanningTree.hpp"
    "Search/TestBinarySearchTree.hpp"
    "Search/TestUnionFind.hpp"
    "Search/UnionFind.hpp"
    "Search/ShortPathes.hpp"
    "Sort/ISortable.hpp"
    "Sort/Sort.hpp"
    "Sort/TestSort.hpp"
    "Structures/BinarySearchTree.hpp"
    "Structures/Edge.hpp"
    "Structures/EdgeWeightedGraph.hpp"
    "Structures/Graph.hpp"
	"Structures/IndexedPQ.hpp"
    "Structures/TestGraph.hpp"
    )

set(FILES ${CPP_FILES} ${HPP_FILES})

add_executable(${PROJECT_NAME} ${FILES})
