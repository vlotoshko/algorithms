cmake_minimum_required(VERSION 3.1)
project(algorithms)

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
    "test/unit/UnitTests.hpp"
    )

add_executable(${PROJECT_NAME} ${CPP_FILES} ${HPP_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC test/unit)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
    )

if(NOT WIN32)
    set(LINKER_FLAGS "-pthread")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
endif (NOT WIN32)
set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS})


if(COMPILE_WITH_CPPUNIT)
    target_compile_definitions(${PROJECT_NAME} PRIVATE COMPILE_WITH_CPPUNIT)
    if(WIN32)
        include_directories("S:/Projects/cppunit/include/")
        link_directories("S:/Projects/cppunit/lib/")
    endif()
    if(WIN32 AND CMAKE_BUILD_TYPE MATCHES "Debug")
        target_link_libraries(${PROJECT_NAME} cppunitd)
    else()
        target_link_libraries(${PROJECT_NAME} cppunit)
    endif()
endif()

