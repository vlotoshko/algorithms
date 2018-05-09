//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   09-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef ITESTABLE_HPP
#define ITESTABLE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "tools.hpp"
//--------------------------------------------------------------------------------------------------

// ------------------------------------------------------------------------------------------
// Interface for a test invocation
//
class ITestable
{
public:
    virtual ~ITestable() = default;
    virtual void runTest(tools::Timer & timer) = 0;
};

//--------------------------------------------------------------------------------------------------
#endif // ITESTABLE_HPP
//--------------------------------------------------------------------------------------------------
