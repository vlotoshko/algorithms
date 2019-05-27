
# ---------------------------------------------------------------------------
# Benchmark tests app building section
#

set(BENCHMARK_TESTS_TARGET ${ALGORITHMS_TARGET}_benchmark_tests)

set(BENCHMARK_TEST_SRC_APP_DIR ${PROJECT_SOURCE_DIR}/tests/benchmark/)

set(BENCHMARK_TEST_SRC
    ${BENCHMARK_TEST_SRC_APP_DIR}/main.cpp

    ${BENCHMARK_TEST_SRC_APP_DIR}/BenchmarkTests.hpp
    )

add_executable(${BENCHMARK_TESTS_TARGET}
    ${BENCHMARK_TEST_SRC}
    $<TARGET_OBJECTS:${ALGORITHMS_TARGET}>
    )

target_include_directories(${BENCHMARK_TESTS_TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${BENCHMARK_TESTS_TARGET} PRIVATE
    cppunit
    )

set_target_properties(${BENCHMARK_TESTS_TARGET} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
    )

