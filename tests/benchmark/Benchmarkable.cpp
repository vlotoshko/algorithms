/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 18-Aug-2019
 */

//--------------------------------------------------------------------------------------------------
#include "Benchmarkable.hpp"
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
namespace benchmark
{

BenchmarkableBase::BenchmarkableBase() : eplacedTime_(0) {}

void BenchmarkableBase::execute() {
    init();
    timer_.start();
    // do some heavy calculations
    doSomeHeavy();
    eplacedTime_ = timer_.timeSpent();
}

} // namespace benchmark
