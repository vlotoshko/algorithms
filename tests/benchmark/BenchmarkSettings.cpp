/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 18-Aug-2019
 */

//--------------------------------------------------------------------------------------------------
#include "BenchmarkSettings.hpp"
//--------------------------------------------------------------------------------------------------

namespace benchmark
{

Interruptable::~Interruptable() = default;

InterruptByTime::InterruptByTime(unsigned int t) : timeout_(t) {}
bool InterruptByTime::interrupt()
{
    return timer_.timeSpent() > timeout_;
}

BenchmarkSettings::BenchmarkSettings(double e, size_t i, size_t iAM, std::unique_ptr<Interruptable> t)
    : epsilon_(e), iterations_(i), iterationsAM_(iAM), interuptable_(std::move(t)) {}

} // namespace benchmark
