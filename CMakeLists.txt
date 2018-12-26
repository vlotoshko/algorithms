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
include_directories(Tests)

set(CPP_FILES
    "Search/GraphAlgorithms.cpp"
    "Search/MinimalSpanningTree.cpp"
    "Search/ShortPathes.cpp"
    "Tests/TestGraph.cpp"
    "Tools.cpp"
    "main.cpp"
    )

set(HPP_FILES
    "Tools.hpp"
    "Search/GraphAlgorithms.hpp"
    "Search/MinimalSpanningTree.hpp"
    "Search/UnionFind.hpp"
    "Search/ShortPathes.hpp"
    "Sort/ISortable.hpp"
    "Sort/Sort.hpp"
    "Structures/BinarySearchTree.hpp"
    "Structures/Edge.hpp"
    "Structures/Graph.hpp"
    "Structures/GraphDirectionPolicies.hpp"
    "Structures/IndexedPQ.hpp"
    "Tests/ITestable.hpp"
    "Tests/TestGraph.hpp"
    "Tests/TestRegistry.hpp"
    "Tests/TestFactory.hpp"
    "Tests/TestBinarySearchTree.hpp"
    "Tests/TestUnionFind.hpp"
    "Tests/TestSort.hpp"
    )

set(FILES ${CPP_FILES} ${HPP_FILES})

add_executable(${PROJECT_NAME} ${FILES})
target_link_libraries  (${PROJECT_NAME} cppunit)
