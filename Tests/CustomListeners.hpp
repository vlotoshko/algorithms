//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   30-Dec-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef CUSTOMLISTENERS_HPP
#define CUSTOMLISTENERS_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <iostream>
#include <iomanip>

#include <cppunit/TestListener.h>
#include <cppunit/Test.h>
#include <cppunit/TestFailure.h>
//--------------------------------------------------------------------------------------------------

namespace tests
{

class ShowStartListener : public CppUnit::TestListener
{
public:
    void startSuite( CppUnit::Test * test) override
    {
        suiteName_ = test->getName();
//        std::cout << "--- START SUITE -- " << test->getName() << std::endl;
    }

    void startTest( CppUnit::Test * test) override
    {
        auto str = suiteName_ + " : " + test->getName();
        std::cout << std::setw(90) << str.c_str() << "... ";
    }
private:
    std::string suiteName_;
};

class ShowEndListener : public CppUnit::TestListener
{
public:
    ShowEndListener () : testFailed_(false) {}

    void endTest( CppUnit::Test * ) override
    {
        std::cout << (testFailed_ ? "[ FAILED ]" : "[ OK ]") << std::endl;
        testFailed_ = false;
    }

    void addFailure( const CppUnit::TestFailure & ) override
    {
        testFailed_ = true;
    }

    void endSuite( CppUnit::Test *) override
    {
        std::cout << std::endl;
    }
private:
    bool testFailed_;
};

} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // CUSTOMLISTENERS_HPP
//--------------------------------------------------------------------------------------------------
