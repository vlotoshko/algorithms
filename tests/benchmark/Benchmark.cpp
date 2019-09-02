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

class Interruptable
{
public:
    virtual ~Interruptable();
    virtual bool interrupt() = 0;
};

Interruptable::~Interruptable() = default;

class InterruptByTime : public Interruptable
{
public:
    explicit InterruptByTime(unsigned int t);
    bool interrupt() override;
private:
    unsigned int timeout_;
    tools::Timer timer_;
};

InterruptByTime::InterruptByTime(unsigned int t) : timeout_(t) {}
bool InterruptByTime::interrupt()
{
    return timer_.timeSpent() > timeout_;
}

// -------------------------------------------------------------------------------
// ----- Helper functions declaration -----
//

void getMinimalRequiredState(std::unique_ptr<IBenchmarkable> & test, double epsilon);
std::vector<double> calculateResults(std::unique_ptr<IBenchmarkable> & test, size_t i, size_t iAM,
                                     Interruptable & interrupt);

std::vector<double> getRatios(const std::vector<double> & items);
bool goodResults(const std::vector<double> & items);
double arithmeticMean(const std::vector<double> & items);


// -------------------------------------------------------------------------------
// ----- Benchmark methods definition -----
//

Benchmark::Benchmark(std::unique_ptr<IBenchmarkable> t, size_t i, size_t iAM)
    : epsilon_(0.01), iterations_(i), iterationsAM_(iAM), test_(std::move(t)) {}

void Benchmark::run()
{
    std::cout << std::endl;
    InterruptByTime interruption{300};
    size_t allIterations = iterations_;
    tools::Timer timer;
    getMinimalRequiredState(test_, epsilon_);

    std::vector<double> results = calculateResults(test_, allIterations, iterationsAM_, interruption);
    std::vector<double> ratios = getRatios(results);

    size_t attempts = 0;
    while(!goodResults(ratios) && !interruption.interrupt())
    {
        ++attempts;
        std::cout << "Results are not good enough. Specifying it, attemption #"
                  << attempts << " ..." << std::endl;
        double ratioAM = arithmeticMean(ratios);

        getMinimalRequiredState(test_, epsilon_);
        for (size_t i = 0; i < attempts; ++i)
        {
            test_->doubleData();
        }
        ratios = getRatios(calculateResults(test_, allIterations, iterationsAM_, interruption));
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

std::vector<double> calculateResults(std::unique_ptr<IBenchmarkable> & test, size_t i, size_t iAM,
                                     Interruptable & interruption)
{
    std::vector<double> results;
    size_t itersDone = 0;
    while (itersDone < i && !interruption.interrupt())
    {
        std::vector<double> resultsForAM;
        size_t itersDoneAM = 0;
        while (itersDoneAM < iAM && !interruption.interrupt())
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
    // TODO: make normal cycle
    for (auto & r1 : items)
    {
        for (auto r2 : items)
        {
            auto delta = std::abs(r1 - r2);
            if (delta > spread)
            {
                std::cout << "delta is bigger than spread: " << delta << std::endl;
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


} // namespace benchmark
