/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#include "vector"

#include "BenchmarkTests.hpp"
//--------------------------------------------------------------------------------------------------


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
    tests::launchBenchmarkTests();
//    vector_create();
//    vector_reserve();
//    vector_push_back();
    return 0;
}

//--------------------------------------------------------------------------------------------------
