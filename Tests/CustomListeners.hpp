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

#include <cppunit/TestListener.h>
//--------------------------------------------------------------------------------------------------

namespace tests
{

class ShowStartListener : public CppUnit::TestListener
{
public:
    void startSuite( CppUnit::Test * ) override
    {
        std::cout << "--- START SUITE ------------------------ " << std::endl;
    }
};

class ShowEndListener : public CppUnit::TestListener
{
public:
    void endSuite( CppUnit::Test * ) override
    {
        std::cout << "--- END SUITE -------------------------- " << std::endl << std::endl;
    }
};

} // namespace tests

//--------------------------------------------------------------------------------------------------
#endif // CUSTOMLISTENERS_HPP
//--------------------------------------------------------------------------------------------------
