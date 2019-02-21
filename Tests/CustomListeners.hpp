/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 30-Dec-2018
 */

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

constexpr int DEFAULT_WIDTH = 70;
/**
 * @class ShowStartListener
 * @brief The ShowStartListener class outputs test properties before test starts.
 */
class ShowStartListener : public CppUnit::TestListener
{
public:
    /**
     * @brief startSuite saves the name of the started suite test.
     * @param[in] test suite test
     */
    void startSuite(CppUnit::Test * test) override
    {
        suiteName_ = test->getName();
        std::string str = "---  " + suiteName_ + "  ";
        char prev = std::cout.fill ('-');
        std::cout << std::setw(DEFAULT_WIDTH + 12) << setiosflags(std::ios::left)
                  << str.c_str() << std::endl;
        std::cout.fill(prev);

    }

    /**
     * @brief startTest outputs the name of the started test.
     * @param[in] test test
     */
    void startTest(CppUnit::Test * test) override
    {
        auto str =/* suiteName_ + */ "| " + test->getName();
        std::cout << std::setw(DEFAULT_WIDTH) << setiosflags(std::ios::left) << str.c_str() << "... ";
    }
private:
    std::string suiteName_;
};


/**
 * @class ShowEndListener
 * @brief The ShowEndListener class outputs test result after test ends.
 */
class ShowEndListener : public CppUnit::TestListener
{
public:
    ShowEndListener () : testFailed_(false) {}

    /**
     * @brief endTest outputs result of the test.
     */
    void endTest(CppUnit::Test *) override
    {
        std::cout << (testFailed_ ? "[ FAILED ]" : "[ OK ]") << " |" << std::endl;
        testFailed_ = false;
    }

    /**
     * @brief addFailure marks test as failed.
     */
    void addFailure( const CppUnit::TestFailure & ) override
    {
        testFailed_ = true;
    }

    /**
     * @brief endSuite outputs extra endline to split suite test.
     */
    void endSuite( CppUnit::Test *) override
    {
        char prev = std::cout.fill ('-');
        std::cout.width (DEFAULT_WIDTH + 12);
        std::cout << "-" << '\n';
        std::cout.fill(prev);
        std::cout << std::endl;
    }
private:
    bool testFailed_;
};

} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // CUSTOMLISTENERS_HPP
//--------------------------------------------------------------------------------------------------
