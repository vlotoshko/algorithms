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
std::vector<double> calculateResults(std::unique_ptr<IBenchmarkable> & test, size_t i, size_t iAM);

std::vector<double> getRatios(const std::vector<double> & items);
bool goodResults(const std::vector<double> & items);
double arithmeticMean(const std::vector<double> & items);


// -------------------------------------------------------------------------------
// ----- Benchmark methods definition -----
//

Benchmark::Benchmark(std::unique_ptr<IBenchmarkable> t, size_t i, size_t iAM)
    : epsilon_(0.005), iterations_(i), iterationsAM_(iAM), test_(std::move(t)) {}

void Benchmark::run()
{
    std::cout << std::endl;
    getMinimalRequiredState(test_, epsilon_);

    std::vector<double> results = calculateResults(test_, iterations_, iterationsAM_);
    std::vector<double> ratios = getRatios(results);

    int attempts = 0;
    int allAttempts = 10;
    while(!goodResults(ratios) && attempts < allAttempts)
    {
        ++attempts;
        std::cout << "Results are not good enough, specifying... "
                  << attempts << "/" << allAttempts << std::endl;
        double ratioAM = arithmeticMean(ratios);

        getMinimalRequiredState(test_, epsilon_);
        ratios = getRatios(calculateResults(test_, iterations_, iterationsAM_));
        ratios.push_back(ratioAM);
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
    while (test->eplacedTime() < epsilon && attempts < 100) {
        test->doubleData();
        test->execute();
        ++attempts;
    }
}

std::vector<double> calculateResults(std::unique_ptr<IBenchmarkable> & test, size_t i, size_t iAM)
{
    std::vector<double> results;
    size_t itersDone = 0;
    while (itersDone < i)
    {
        std::vector<double> resultsForAM;
        size_t itersDoneAM = 0;
        while (itersDoneAM < iAM)
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
    for (auto & r1 : items)
    {
        for (auto r2 : items)
        {
            if (r1 - r2 > spread || r2 - r1 > spread)
            {
                std::cout << r1 << " " << r2 << " " << spread << std::endl;
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
