/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#ifdef COMPILE_WITH_CPPUNIT
#include "UnitTests.hpp"
#endif

#ifdef COMPILE_WITH_BENCHMARK
#include "BenchmarkTests.hpp"
#endif
//--------------------------------------------------------------------------------------------------


void launchTests()
{
#ifdef COMPILE_WITH_CPPUNIT
    tests::launchUnitTests();
#endif

#ifdef COMPILE_WITH_BENCHMARK
    tests::launchBenchmarkTests();
#endif
}

int main(/*int argc, char *argv[]*/)
{
    launchTests();
    return 0;
}

//--------------------------------------------------------------------------------------------------
