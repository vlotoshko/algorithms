# ---------------------------------------------------------------------------
# Cppunit library building section
#

# Building cppunit library from sources
set(CPPUNIT_LIB_SRC_DIR ${PROJECT_SOURCE_DIR}/lib/src/cppunit)
set(CPPUNIT_LIB_INC_DIR ${PROJECT_SOURCE_DIR}/lib/include/cppunit)

set(CPPUNIT_CPP_FILES
    ${CPPUNIT_LIB_SRC_DIR}/AdditionalMessage.cpp
    ${CPPUNIT_LIB_SRC_DIR}/Asserter.cpp
    ${CPPUNIT_LIB_SRC_DIR}/BriefTestProgressListener.cpp
    ${CPPUNIT_LIB_SRC_DIR}/CompilerOutputter.cpp
    ${CPPUNIT_LIB_SRC_DIR}/DefaultProtector.h
    ${CPPUNIT_LIB_SRC_DIR}/DefaultProtector.cpp
    ${CPPUNIT_LIB_SRC_DIR}/DynamicLibraryManager.cpp
    ${CPPUNIT_LIB_SRC_DIR}/DynamicLibraryManagerException.cpp
    ${CPPUNIT_LIB_SRC_DIR}/Exception.cpp
    ${CPPUNIT_LIB_SRC_DIR}/Message.cpp
    ${CPPUNIT_LIB_SRC_DIR}/RepeatedTest.cpp
    ${CPPUNIT_LIB_SRC_DIR}/PlugInManager.cpp
    ${CPPUNIT_LIB_SRC_DIR}/PlugInParameters.cpp
    ${CPPUNIT_LIB_SRC_DIR}/Protector.cpp
    ${CPPUNIT_LIB_SRC_DIR}/ProtectorChain.h
    ${CPPUNIT_LIB_SRC_DIR}/ProtectorContext.h
    ${CPPUNIT_LIB_SRC_DIR}/ProtectorChain.cpp
    ${CPPUNIT_LIB_SRC_DIR}/SourceLine.cpp
    ${CPPUNIT_LIB_SRC_DIR}/StringTools.cpp
    ${CPPUNIT_LIB_SRC_DIR}/SynchronizedObject.cpp
    ${CPPUNIT_LIB_SRC_DIR}/Test.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestAssert.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestCase.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestCaseDecorator.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestComposite.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestDecorator.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestFactoryRegistry.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestFailure.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestLeaf.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestNamer.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestPath.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestPlugInDefaultImpl.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestResult.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestResultCollector.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestRunner.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestSetUp.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestSuccessListener.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestSuite.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TestSuiteBuilderContext.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TextOutputter.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TextTestProgressListener.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TextTestResult.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TextTestRunner.cpp
    ${CPPUNIT_LIB_SRC_DIR}/TypeInfoHelper.cpp
    ${CPPUNIT_LIB_SRC_DIR}/UnixDynamicLibraryManager.cpp
    ${CPPUNIT_LIB_SRC_DIR}/ShlDynamicLibraryManager.cpp
    ${CPPUNIT_LIB_SRC_DIR}/XmlDocument.cpp
    ${CPPUNIT_LIB_SRC_DIR}/XmlElement.cpp
    ${CPPUNIT_LIB_SRC_DIR}/XmlOutputter.cpp
    ${CPPUNIT_LIB_SRC_DIR}/XmlOutputterHook.cpp
    ${CPPUNIT_LIB_SRC_DIR}/Win32DynamicLibraryManager.cpp
    )

set(CPPUNIT_HPP_FILES
    ${CPPUNIT_LIB_INC_DIR}/AdditionalMessage.h
    ${CPPUNIT_LIB_INC_DIR}/Asserter.h
    ${CPPUNIT_LIB_INC_DIR}/BriefTestProgressListener.h
    ${CPPUNIT_LIB_INC_DIR}/CompilerOutputter.h
    ${CPPUNIT_LIB_INC_DIR}/Exception.h
    ${CPPUNIT_LIB_INC_DIR}/Message.h
    ${CPPUNIT_LIB_INC_DIR}/Outputter.h
    ${CPPUNIT_LIB_INC_DIR}/Portability.h
    ${CPPUNIT_LIB_INC_DIR}/Protector.h
    ${CPPUNIT_LIB_INC_DIR}/SourceLine.h
    ${CPPUNIT_LIB_INC_DIR}/SynchronizedObject.h
    ${CPPUNIT_LIB_INC_DIR}/Test.h
    ${CPPUNIT_LIB_INC_DIR}/TestAssert.h
    ${CPPUNIT_LIB_INC_DIR}/TestCase.h
    ${CPPUNIT_LIB_INC_DIR}/TestCaller.h
    ${CPPUNIT_LIB_INC_DIR}/TestComposite.h
    ${CPPUNIT_LIB_INC_DIR}/TestFailure.h
    ${CPPUNIT_LIB_INC_DIR}/TestFixture.h
    ${CPPUNIT_LIB_INC_DIR}/TestLeaf.h
    ${CPPUNIT_LIB_INC_DIR}/TestPath.h
    ${CPPUNIT_LIB_INC_DIR}/TestResult.h
    ${CPPUNIT_LIB_INC_DIR}/TestResultCollector.h
    ${CPPUNIT_LIB_INC_DIR}/TestRunner.h
    ${CPPUNIT_LIB_INC_DIR}/TestSuccessListener.h
    ${CPPUNIT_LIB_INC_DIR}/TestSuite.h
    ${CPPUNIT_LIB_INC_DIR}/TextOutputter.h
    ${CPPUNIT_LIB_INC_DIR}/TextTestProgressListener.h
    ${CPPUNIT_LIB_INC_DIR}/TextTestResult.h
    ${CPPUNIT_LIB_INC_DIR}/TextTestRunner.h
    ${CPPUNIT_LIB_INC_DIR}/TestListener.h
    ${CPPUNIT_LIB_INC_DIR}/XmlOutputter.h
    ${CPPUNIT_LIB_INC_DIR}/XmlOutputterHook.h

    ${CPPUNIT_LIB_INC_DIR}/config-auto.h

    ${CPPUNIT_LIB_INC_DIR}/config/config-bcb5.h
    ${CPPUNIT_LIB_INC_DIR}/config/config-evc4.h
    ${CPPUNIT_LIB_INC_DIR}/config/config-mac.h
    ${CPPUNIT_LIB_INC_DIR}/config/config-msvc6.h
    ${CPPUNIT_LIB_INC_DIR}/config/SelectDllLoader.h
    ${CPPUNIT_LIB_INC_DIR}/config/CppUnitApi.h
    ${CPPUNIT_LIB_INC_DIR}/config/SourcePrefix.h

    ${CPPUNIT_LIB_INC_DIR}/extensions/TestFactory.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/AutoRegisterSuite.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/HelperMacros.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/Orthodox.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/RepeatedTest.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/ExceptionTestCaseDecorator.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestCaseDecorator.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestDecorator.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestFactoryRegistry.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestFixtureFactory.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestNamer.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestSetUp.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestSuiteBuilderContext.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TestSuiteFactory.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/TypeInfoHelper.h
    ${CPPUNIT_LIB_INC_DIR}/extensions/XmlInputHelper.h

    ${CPPUNIT_LIB_INC_DIR}/plugin/DynamicLibraryManager.h
    ${CPPUNIT_LIB_INC_DIR}/plugin/DynamicLibraryManagerException.h
    ${CPPUNIT_LIB_INC_DIR}/plugin/TestPlugIn.h
    ${CPPUNIT_LIB_INC_DIR}/plugin/TestPlugInDefaultImpl.h
    ${CPPUNIT_LIB_INC_DIR}/plugin/PlugInManager.h
    ${CPPUNIT_LIB_INC_DIR}/plugin/PlugInParameters.h

    ${CPPUNIT_LIB_INC_DIR}/portability/FloatingPoint.h
    ${CPPUNIT_LIB_INC_DIR}/portability/Stream.h

    ${CPPUNIT_LIB_INC_DIR}/tools/Algorithm.h
    ${CPPUNIT_LIB_INC_DIR}/tools/StringTools.h
    ${CPPUNIT_LIB_INC_DIR}/tools/StringHelper.h
    ${CPPUNIT_LIB_INC_DIR}/tools/XmlElement.h
    ${CPPUNIT_LIB_INC_DIR}/tools/XmlDocument.h

    ${CPPUNIT_LIB_INC_DIR}/ui/text/TestRunner.h
    ${CPPUNIT_LIB_INC_DIR}/ui/text/TextTestRunner.h
    )

add_library(cppunit STATIC
    ${CPPUNIT_CPP_FILES}
    ${CPPUNIT_HPP_FILES}
    )

target_include_directories(cppunit PUBLIC
    ${PROJECT_SOURCE_DIR}/lib/include/
    )

set_target_properties(cppunit PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE C
    )


# ---------------------------------------------------------------------------
# Unit tests app building section
#

set(UNIT_TESTS_TARGET ${ALGORITHMS_TARGET}_unit_tests)

set(UNIT_TEST_SRC_APP_DIR ${PROJECT_SOURCE_DIR}/tests/unit/)

set(UNIT_TEST_SRC
    ${UNIT_TEST_SRC_APP_DIR}/main.cpp
    ${UNIT_TEST_SRC_APP_DIR}/CustomListeners.hpp
    ${UNIT_TEST_SRC_APP_DIR}/TestGraph.hpp
    ${UNIT_TEST_SRC_APP_DIR}/TestBinarySearchTree.hpp
    ${UNIT_TEST_SRC_APP_DIR}/TestUnionFind.hpp
    ${UNIT_TEST_SRC_APP_DIR}/TestSort.hpp
    ${UNIT_TEST_SRC_APP_DIR}/UnitTests.hpp
    )

add_executable(${UNIT_TESTS_TARGET}
    ${UNIT_TEST_SRC}
    $<TARGET_OBJECTS:${ALGORITHMS_TARGET}>
    )

target_include_directories(${UNIT_TESTS_TARGET} PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${UNIT_TESTS_TARGET} PRIVATE
    cppunit
    )

set_target_properties(${UNIT_TESTS_TARGET} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    LINKER_LANGUAGE CXX
    )
