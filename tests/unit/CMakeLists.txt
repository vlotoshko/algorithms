# ---------------------------------------------------------------------------
# Unit tests app building section
#

set(UNIT_TESTS_TARGET ${ALGORITHMS_TARGET}_unit_tests)
set(UNIT_TEST_SRC_APP_DIR ${PROJECT_SOURCE_DIR}/tests/unit/)
set(UNIT_TEST_SRC
    ${UNIT_TEST_SRC_APP_DIR}/catch2/catch.hpp
    ${UNIT_TEST_SRC_APP_DIR}/main.cpp
    ${UNIT_TEST_SRC_APP_DIR}/TestBinarySearchTree.cpp
    ${UNIT_TEST_SRC_APP_DIR}/TestGraph.cpp
    ${UNIT_TEST_SRC_APP_DIR}/TestSort.cpp
    ${UNIT_TEST_SRC_APP_DIR}/TestUnionFind.cpp
    ${UNIT_TEST_SRC_APP_DIR}/TestHashTable.cpp
    )

add_executable(${UNIT_TESTS_TARGET}
    ${UNIT_TEST_SRC}
    $<TARGET_OBJECTS:${ALGORITHMS_TARGET}>
    )

target_include_directories(${UNIT_TESTS_TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/include)

set_target_properties(${UNIT_TESTS_TARGET} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
    )
