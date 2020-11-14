cmake_minimum_required(VERSION 3.8)
project(algorithms VERSION 0.0.1 LANGUAGES C CXX)


# ---------------------------------------------------------------------------
# Linker settings section
#

if(NOT WIN32)
    set(LINKER_FLAGS "-pthread")
    set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -Wpedantic")
endif (NOT WIN32)
set(CMAKE_EXE_LINKER_FLAGS ${LINKER_FLAGS})


# ---------------------------------------------------------------------------
# Options section
#

option(OPTION_BUILD_UNIT_TESTS "Build unit test application" ON)
option(OPTION_BUILD_DOCUMENTATION "Build documentation" OFF)
option(OPTION_CHECK_WITH_CPPCHECK "" OFF)


# ---------------------------------------------------------------------------
# Algorithms target building section
#

set(ALGORITHMS_TARGET algorithms)

set(ALGORITHMS_TARGET_SRC_FILES
    src/GraphAlgorithms.cpp
    src/MinimalSpanningTree.cpp
    src/ShortPaths.cpp
    src/Tools.cpp

    include/Tools.hpp
    include/GraphAlgorithms.hpp
    include/MinimalSpanningTree.hpp
    include/UnionFind.hpp
    include/ShortPaths.hpp
    include/Sort.hpp
    include/Sort_Impl.hpp
    include/BstHelperFunctions.hpp
    include/BstRedBlack.hpp
    include/BstUnbalanced.hpp
    include/Edge.hpp
    include/Graph.hpp
    include/GraphDirectionPolicies.hpp
    include/HashTableChaining.hpp
    include/IndexedPQ.hpp
    )

add_library(${ALGORITHMS_TARGET} OBJECT ${ALGORITHMS_TARGET_SRC_FILES})

target_include_directories(${ALGORITHMS_TARGET} PRIVATE include)

set_target_properties(${ALGORITHMS_TARGET} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
    )


# ---------------------------------------------------------------------------
# Optional targets building section
#

if(OPTION_BUILD_UNIT_TESTS)
    add_subdirectory(tests/unit)
endif()


if(OPTION_BUILD_DOCUMENTATION)
#    set(DOC_TARGET ${MAIN_TARGET}_documentation)
#    add_executable(${DOC_TARGET} ${MAIN_TARGET_CPP_FILES} ${MAIN_TARGET_HPP_FILES})
endif()


#if (CMAKE_BUILD_TYPE MATCHES "^[Rr]elease")
#    # first we can indicate the documentation build as an option and set it to ON by default
#    option(BUILD_DOC "Build documentation" ON)

#    # check if Doxygen is installed
#    find_package(Doxygen)
#    if (DOXYGEN_FOUND)
#        # set input and output files
#        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
#        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

#        # request to configure the file
#        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
#        message("Doxygen build started")

#        # note the option ALL which allows to build the docs together with the application
#        add_custom_target( doc_doxygen ALL
#            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
#            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#            COMMENT "Generating API documentation with Doxygen"
#            VERBATIM )
#    else (DOXYGEN_FOUND)
#      message("Doxygen need to be installed to generate the doxygen documentation")
#    endif (DOXYGEN_FOUND)
#endif()

