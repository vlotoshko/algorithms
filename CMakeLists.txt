cmake_minimum_required(VERSION 3.8)
project(algorithms VERSION 0.0.1 LANGUAGES C CXX)


set(MAIN_TARGET algorithms)

set(MAIN_TARGET_CPP_FILES
    src/GraphAlgorithms.cpp
    src/MinimalSpanningTree.cpp
    src/ShortPaths.cpp
    src/Tools.cpp
    src/main.cpp
    )

set(MAIN_TARGET_HPP_FILES
    include/Tools.hpp
    include/GraphAlgorithms.hpp
    include/MinimalSpanningTree.hpp
    include/UnionFind.hpp
    include/ShortPaths.hpp
    include/Sort.hpp
    include/Sort_Impl.hpp
    include/BinarySearchTree.hpp
    include/Edge.hpp
    include/Graph.hpp
    include/GraphDirectionPolicies.hpp
    include/IndexedPQ.hpp
    test/unit/CustomListeners.hpp
    test/unit/TestGraph.hpp
    test/unit/TestBinarySearchTree.hpp
    test/unit/TestUnionFind.hpp
    test/unit/TestSort.hpp
    test/unit/UnitTests.hpp
    )

add_executable(${MAIN_TARGET} ${MAIN_TARGET_CPP_FILES} ${MAIN_TARGET_HPP_FILES})

target_include_directories(${MAIN_TARGET} PRIVATE include)
target_include_directories(${MAIN_TARGET} PRIVATE test/unit)

target_compile_features(${MAIN_TARGET} PRIVATE cxx_std_14)

set_target_properties(${MAIN_TARGET} PROPERTIES
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
    target_compile_definitions(${MAIN_TARGET} PRIVATE COMPILE_WITH_CPPUNIT)
    add_subdirectory(test/unit/cppunit)
    target_link_libraries(${MAIN_TARGET} PRIVATE cppunit)
else()
    target_include_directories(${MAIN_TARGET} PRIVATE lib/include/)
endif()

