/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 09-May-2018
 */

//--------------------------------------------------------------------------------------------------
#ifdef COMPILE_WITH_CPPUNIT
#include "UnitTests.hpp"
#endif
//--------------------------------------------------------------------------------------------------

int launchUnitTests()
{
    int result = 0;

#ifdef COMPILE_WITH_CPPUNIT
    tests::registerUnitTests();
    result = tests::runUnitTests() ? 0 : 1;
#endif

    return result;
}
int main(/*int argc, char *argv[]*/)
{
    return launchUnitTests();
}

//--------------------------------------------------------------------------------------------------
