/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 18-Aug-2019
 */

//--------------------------------------------------------------------------------------------------
#ifndef BENCHMARK_HPP
#define BENCHMARK_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Benchmarkable.hpp"

#include <memory>
#include <vector>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace benchmark
{

class Benchmark
{
public:
    Benchmark(std::unique_ptr<IBenchmarkable> t, size_t i = 5, size_t iAM = 10);
    void run();
    inline const std::vector<double> & getResults() const { return results_; }

private:
    double epsilon_;
    size_t iterations_;
    size_t iterationsAM_;
    std::unique_ptr<IBenchmarkable> test_;
    std::vector<double> results_;
};


} // namespace benchmark

//--------------------------------------------------------------------------------------------------
#endif // BENCHMARK_HPP
//--------------------------------------------------------------------------------------------------
