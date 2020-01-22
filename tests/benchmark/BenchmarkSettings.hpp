/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 19-Jan-2020
 */

//--------------------------------------------------------------------------------------------------
#ifndef BENCHMARKSETTINGS_HPP
#define BENCHMARKSETTINGS_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Tools.hpp"

#include <memory>
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace benchmark
{

class Interruptable
{
public:
    virtual ~Interruptable();
    virtual bool interrupt() = 0;
};

class InterruptByTime : public Interruptable
{
public:
    explicit InterruptByTime(unsigned int t);
    bool interrupt() override;
private:
    unsigned int timeout_;
    tools::Timer timer_;
};

class BenchmarkSettings {
public:
    BenchmarkSettings(double e = 0.01, size_t i = 5, size_t iAM = 10,
                      std::unique_ptr<Interruptable> in = std::unique_ptr<Interruptable>());
    double getEpsilon() const { return epsilon_; }
    size_t getIterationsCount() const { return iterations_; }
    size_t getIterationsAMCount() const { return iterationsAM_; }
    const Interruptable & getInteruptable() const { return *interuptable_; }
private:
    const double epsilon_;
    const size_t iterations_;
    const size_t iterationsAM_;
    std::unique_ptr<Interruptable> interuptable_;
};

} // namespace benchmark

//--------------------------------------------------------------------------------------------------
#endif // BENCHMARKSETTINGS_HPP
//--------------------------------------------------------------------------------------------------
