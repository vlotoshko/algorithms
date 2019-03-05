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
    test/benchmark/BenchmarkTests.hpp
    test/unit/CustomListeners.hpp
    test/unit/TestGraph.hpp
    test/unit/TestBinarySearchTree.hpp
    test/unit/TestUnionFind.hpp
    test/unit/TestSort.hpp
    test/unit/UnitTests.hpp
    )

add_executable(${MAIN_TARGET} ${MAIN_TARGET_CPP_FILES} ${MAIN_TARGET_HPP_FILES})

target_include_directories(${MAIN_TARGET} PRIVATE include)
target_include_directories(${MAIN_TARGET} PRIVATE test/benchmark)
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


if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
    # first we can indicate the documentation build as an option and set it to ON by default
    option(BUILD_DOC "Build documentation" ON)

    # check if Doxygen is installed
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        # set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

        # request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
        message("Doxygen build started")

        # note the option ALL which allows to build the docs together with the application
        add_custom_target( doc_doxygen ALL
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM )
    else (DOXYGEN_FOUND)
      message("Doxygen need to be installed to generate the doxygen documentation")
    endif (DOXYGEN_FOUND)
endif()

