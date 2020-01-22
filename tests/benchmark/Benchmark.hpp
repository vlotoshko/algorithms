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
#include "BenchmarkSettings.hpp"

#include <memory>
#include <vector>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace benchmark
{

class Benchmark
{
public:
    Benchmark(std::unique_ptr<IBenchmarkable> t, std::unique_ptr<BenchmarkSettings> s);
    void run();
    inline const std::vector<double> & getResults() const { return results_; }

private:
    std::unique_ptr<IBenchmarkable> test_;
    std::unique_ptr<BenchmarkSettings> settings_;
//    BenchmarkSettings settings_;
    std::vector<double> results_;
};

} // namespace benchmark

//--------------------------------------------------------------------------------------------------
#endif // BENCHMARK_HPP
//--------------------------------------------------------------------------------------------------
