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

namespace
{

void getMinimalRequiredState(std::unique_ptr<IBenchmarkable> & test, double epsilon);
std::vector<double> calculateResults(std::unique_ptr<IBenchmarkable> & test,
                                     const BenchmarkSettings & s, Interruptable & interrupt);

std::vector<double> getRatios(const std::vector<double> & items);
bool goodResults(const std::vector<double> & items);
double arithmeticMean(const std::vector<double> & items);

}



// -------------------------------------------------------------------------------
// ----- Benchmark methods definition -----
//

Benchmark::Benchmark(std::unique_ptr<IBenchmarkable> t, std::unique_ptr<BenchmarkSettings> s)
    : test_(std::move(t)), settings_(std::move(s)) {}

void Benchmark::run()
{
    std::cout << std::endl;
    InterruptByTime interruption{900};
    tools::Timer timer;
    getMinimalRequiredState(test_, settings_->getEpsilon());

    std::vector<double> results = calculateResults(test_, *settings_, interruption);
    std::vector<double> ratios = getRatios(results);

    size_t attempts = 0;
    while(!goodResults(ratios) && !interruption.interrupt())
    {
        ++attempts;
        std::cout << "Multiply coefficient is: " << arithmeticMean(ratios)
                  << ". Results are not good enough. Specifying it, attemption #"
                  << attempts << " ..." << std::endl;
        double ratioAM = arithmeticMean(ratios);

        getMinimalRequiredState(test_, settings_->getEpsilon());
//        for (size_t i = 0; i < attempts; ++i)
//        {
//            test_->doubleData();
//        }
        ratios = getRatios(calculateResults(test_, *settings_, interruption));
        ratios.push_back(ratioAM);
    }

    if (interruption.interrupt())
    {
        std::cout << "Benchmark was interrupted at " << timer.timeSpent() << std::endl;
    }
    std::cout << "Multiply coefficient is: " << arithmeticMean(ratios) << std::endl;
}


// -------------------------------------------------------------------------------
// ----- Helper functions definition -----
//

namespace
{

void getMinimalRequiredState(std::unique_ptr<IBenchmarkable> & test, double epsilon)
{
    test->reset();
    test->execute();

    size_t attempts = 0;
    while (test->eplacedTime() < epsilon && attempts < 100)
    {
        test->doubleData();
        test->execute();
        ++attempts;
    }
}

std::vector<double> calculateResults(std::unique_ptr<IBenchmarkable> & test,
                                     const BenchmarkSettings & settings, Interruptable & interruption)
{
    std::vector<double> results;
    size_t itersDone = 0;
    while (itersDone < settings.getIterationsCount() && !interruption.interrupt())
    {
        std::vector<double> resultsForAM;
        size_t itersDoneAM = 0;
        while (itersDoneAM < settings.getIterationsAMCount() && !interruption.interrupt())
        {
            test->execute();
            resultsForAM.push_back(test->eplacedTime());
            ++itersDoneAM;
        }

        results.push_back(arithmeticMean(resultsForAM));
        test->doubleData();
        ++itersDone;
    }

//    for (auto & item : results) std::cout << "res = " << item << std::endl;
    return results;
}

std::vector<double> getRatios(const std::vector<double> & items)
{
    std::vector<double> ratios;
    if (items.size() > 1)
    {
        tools::CalcRatio cr;
        cr.getRatio(items[0]);

        for (size_t i = 1; i < items.size(); ++i) {
            ratios.push_back(cr.getRatio(items[i]));
        }
    }
    return ratios;
}

bool goodResults(const std::vector<double> & items)
{
    double spread = 0.1;
    double delta = 0;

    size_t length = items.size();
    for (size_t i = 0; i < length - 1; ++i)
    {
        for (size_t j = 1; j < length; ++j)
        {
            delta = std::abs(items[i] - items[j]);
            if (delta > spread)
            {
                std::cout << "Delta is bigger than spread: " << delta << std::endl;
                return false;
            }
        }
    }
    return true;
}

double arithmeticMean(const std::vector<double> & items)
{
    double d = 0;
    for (const auto & i : items)
    {
        d += i;
    }
    return d/items.size();
}

}

} // namespace benchmark
