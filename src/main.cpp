/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#include "vector"
#ifdef COMPILE_WITH_CPPUNIT
#include "UnitTests.hpp"
#endif

//#ifdef COMPILE_WITH_BENCHMARK
//#include "BenchmarkTests.hpp"
//#endif
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

void vector_create()
{
    for (int i = 0; i < 1'000'000; ++i)
    {
         std::vector<int> v;
         (void)v;
    }
}

void vector_reserve()
{
    for (int i = 0; i < 1'000'000; ++i)
    {
         std::vector<int> v;
         v.reserve(1);
    }
}

void vector_push_back()
{
    for (int i = 0; i < 1'000'000; ++i)
    {
         std::vector<int> v;
         v.reserve(1);
         v.push_back(42);
    }
}

int main(/*int argc, char *argv[]*/)
{
    launchTests();
//    vector_create();
//    vector_reserve();
//    vector_push_back();
    return 0;
}

//--------------------------------------------------------------------------------------------------
