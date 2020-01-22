/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 18-Aug-2019
 */

//--------------------------------------------------------------------------------------------------
#ifndef BENCHMARKABLE_HPP
#define BENCHMARKABLE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Tools.hpp"
//--------------------------------------------------------------------------------------------------

namespace benchmark
{


namespace types
{
using Results = std::vector<double>;
}

using namespace types;

class IBenchmark {
public:
    virtual ~IBenchmark() = default;
    virtual void run() = 0;
    virtual Results & getResults() const = 0;
};


class IBenchmarkable {
public:
    virtual ~IBenchmarkable() = default;
    virtual void init() = 0;
    virtual void reset() = 0;
    virtual void doubleData() = 0;
    virtual void execute() = 0;
    virtual double eplacedTime() const = 0;
};


class BenchmarkableBase : public IBenchmarkable {
public:
    BenchmarkableBase();
    void execute() override;

    virtual void doSomeHeavy() = 0;
    inline double eplacedTime() const override { return eplacedTime_; }
private:
    tools::Timer timer_;
    double eplacedTime_;
};



} // namespace benchmark

//--------------------------------------------------------------------------------------------------
#endif // BENCHMARKABLE_HPP
//--------------------------------------------------------------------------------------------------
