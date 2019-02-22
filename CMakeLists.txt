cmake_minimum_required(VERSION 2.8.12)

project(algorithms)

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
if (!WIN32)
    set(LINKER_FLAGS "-pthread")
endif (WIN32)
set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS})


include_directories(include)
include_directories(src)
include_directories(test/unit)

if (WIN32)
    include_directories("S:/Projects/cppunit/include/")
    link_directories("S:/Projects/cppunit/lib/")
endif (WIN32)


set(CPP_FILES
    "src/GraphAlgorithms.cpp"
    "src/MinimalSpanningTree.cpp"
    "src/ShortPaths.cpp"
    "src/Tools.cpp"
    "src/main.cpp"
    )

set(HPP_FILES
    "include/Tools.hpp"
    "include/GraphAlgorithms.hpp"
    "include/MinimalSpanningTree.hpp"
    "include/UnionFind.hpp"
    "include/ShortPaths.hpp"
    "include/Sort.hpp"
    "include/Sort_Impl.hpp"
    "include/BinarySearchTree.hpp"
    "include/Edge.hpp"
    "include/Graph.hpp"
    "include/GraphDirectionPolicies.hpp"
    "include/IndexedPQ.hpp"
    "test/unit/CustomListeners.hpp"
    "test/unit/TestGraph.hpp"
    "test/unit/TestBinarySearchTree.hpp"
    "test/unit/TestUnionFind.hpp"
    "test/unit/TestSort.hpp"
    )

set(FILES ${CPP_FILES} ${HPP_FILES})

add_executable(${PROJECT_NAME} ${FILES})
if (WIN32 AND CMAKE_BUILD_TYPE MATCHES "Debug")
    target_link_libraries (${PROJECT_NAME} cppunitd)
else()
    target_link_libraries (${PROJECT_NAME} cppunit)
endif ()
