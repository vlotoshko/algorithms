/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 18-Aug-2019
 */

//--------------------------------------------------------------------------------------------------
#include "Benchmark.hpp"
#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
//--------------------------------------------------------------------------------------------------

namespace benchmark
{

// -------------------------------------------------------------------------------
// ----- Helper functions declaration -----
//
void getMinimalRequiredState(std::unique_ptr<IBenchmarkable> & test, double epsilon);
double getArithmeticMean(std::unique_ptr<IBenchmarkable> & test, size_t iterations);


// -------------------------------------------------------------------------------
// ----- Benchmark methods definition -----
//

Benchmark::Benchmark(std::unique_ptr<IBenchmarkable> t, size_t i, size_t iAM)
    : epsilon_(0.005), iterations_(i), iterationsAM_(iAM), test_(std::move(t)) {}

void Benchmark::run()
{
    getMinimalRequiredState(test_, epsilon_);
    std::cout << std::endl;
    size_t iterations = 1;
    while (iterations <= iterations_)
    {
        results_.push_back(getArithmeticMean(test_, iterationsAM_));
        test_->doubleData();
        ++iterations;
    }

    if (results_.size() > 1)
    {
        tools::CalcRatio cr;
        cr.getRatio(results_[0]);
        double rat = 0;

        for (size_t i = 1; i < results_.size(); ++i) {
            double rr = cr.getRatio(results_[i]);
            rat += rr;
            std::cout << " rr = " << rr << std::endl;
        }
        std::cout << "ratio = " << rat/(results_.size() -1) << std::endl;
    }
}


// -------------------------------------------------------------------------------
// ----- Helper functions definition -----
//

void getMinimalRequiredState(std::unique_ptr<IBenchmarkable> & test, double epsilon)
{
    test->execute();

    size_t attempts = 0;
    while (test->eplacedTime() < epsilon && attempts < 100) {
        test->doubleData();
        test->execute();
        ++attempts;
    }
}

double getArithmeticMean(std::unique_ptr<IBenchmarkable> & test, size_t iterations)
{
    test->execute();
    double result = test->eplacedTime();

    size_t itersDone = 1;
    while (itersDone <= iterations)
    {
        test->execute();
        result += test->eplacedTime();
        ++itersDone;
    }
    std::cout << "  am = " << result/itersDone << std::endl;
    return result/itersDone;
}

} // namespace benchmark
