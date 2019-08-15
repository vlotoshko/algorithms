/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 30-May-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef TESTUNIONFIND_HPP
#define TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "UnionFind.hpp"

#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
//--------------------------------------------------------------------------------------------------


#include "Tools.hpp"

namespace tests
{


class IBenchmarkTestable {
public:
    virtual ~IBenchmarkTestable() = default;
    virtual void doubleData() = 0;
    virtual void execute() = 0;
    virtual double eplacedTime() const = 0;
};


class BenchmarkTestableBase : public IBenchmarkTestable {
public:
    BenchmarkTestableBase() : eplacedTime_(0) {}

    void execute() override {
        timer_.start();
        // do some heavy calculations
        doSomeHeavy();
        eplacedTime_ = timer_.timeSpent();
    }

    virtual void doSomeHeavy() = 0;

    double eplacedTime() const override { return eplacedTime_; }
private:
    tools::Timer timer_;
    double eplacedTime_;
};


class Example : public BenchmarkTestableBase {
public:
    void doubleData() override {}
    void doSomeHeavy() override {}
};




class BenchmarkTest {
public:
    BenchmarkTest(std::unique_ptr<IBenchmarkTestable> t, size_t i = 10, size_t iAM = 10)
        : epsilon_(0.01), iterations_(i), iterationsAM_(iAM), test_(std::move(t)) {}

    void run() {
        getMinimalRequiredState();

        size_t iterations = 1;
        while (iterations <= iterations_) {
            results_.push_back(getArithmeticMean());
            test_->doubleData();
            ++iterations;
        }
    }

    const std::vector<double> & getResults() const { return results_; }

private:
    void getMinimalRequiredState() {
        test_->execute();
        
        size_t attempts = 0;
        while (test_->eplacedTime() < epsilon_ && attempts < 100) {
            test_->doubleData();
            test_->execute();
            ++attempts;
        }
    }

    double getArithmeticMean() {
        test_->execute();
        double result = test_->eplacedTime();

        size_t iterations = 1;
        while (iterations <= iterationsAM_) {
            test_->execute();
            result += test_->eplacedTime();
            ++iterations;
        }
        return result/iterations;
    }

    double epsilon_;
    size_t iterations_;
    size_t iterationsAM_;
    std::unique_ptr<IBenchmarkTestable> test_;
    std::vector<double> results_;

};



class BM_Sort : public CppUnit::TestFixture
{
public:
    BM_Sort() = default;

    /**
     * @brief suite implements implicit intreface for the TestSuiteFactory.
     * @return test suite for the current tests.
     */
    static CppUnit::TestSuite * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite("Benchmark sort");
        suiteOfTests->addTest(new CppUnit::TestCaller<BM_Sort>(
                                  "DummySort",
                                  &BM_Sort::dummySort));
        suiteOfTests->addTest(new CppUnit::TestCaller<BM_Sort>(
                                  "BubleSorb",
                                  &BM_Sort::bubleSort));
        return suiteOfTests;
    }


protected:
    /**
     * @brief
     */
    void dummySort()
    {
        //BenchmarkTest(std::move(test_)).run();
    }

    /**
     * @brief
     */
    void bubleSort()
    {
    	std::unique_ptr<IBenchmarkTestable> ex (new Example);
        BenchmarkTest(std::move(ex)).run();
    }

private:
    std::unique_ptr<IBenchmarkTestable> test_;
};




/**
 * @class TestUnionFind
 * @brief The TestUnionFind template class tests union-find algorithms.
 * @tparam UF_Type type of the union-find struct
 * @tparam T type of the elements
 */
template <template <typename> class UF_Type, typename T>
class TestUnionFind : public CppUnit::TestFixture
{
public:
    TestUnionFind() = default;

    /**
     * @brief suite implements implicit intreface for the TestSuiteFactory.
     * @return test suite for the current tests.
     */
    static CppUnit::TestSuite * suite()
    {
        CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite(UF_Type<T>::name);
        suiteOfTests->addTest(new CppUnit::TestCaller<TestUnionFind<UF_Type, T>>(
                                  "find_ShouldReturnClusterId_WhenGivenComponent",
                                  &TestUnionFind::find_ShouldReturnClusterId_WhenGivenComponent));
        suiteOfTests->addTest(new CppUnit::TestCaller<TestUnionFind<UF_Type, T>>(
                                  "unionComponents_ShouldConnectComponentsIntoOneCluster",
                                  &TestUnionFind::unionComponents_ShouldConnectComponentsIntoOneCluster));
        return suiteOfTests;
    }

    /**
     * @brief setUp sets up union-find structure.
     */
    void setUp() override
    {
        uf_Type.unionComponents(ufData, 1, 3);
        uf_Type.unionComponents(ufData, 2, 8);
        uf_Type.unionComponents(ufData, 1, 7);
        uf_Type.unionComponents(ufData, 3, 9);
        uf_Type.unionComponents(ufData, 4, 8);
    }

protected:
    /**
     * @brief find_ShouldReturnClusterId_WhenGivenComponent tests returning correct cluster id.
     */
    void find_ShouldReturnClusterId_WhenGivenComponent()
    {
        CPPUNIT_ASSERT_EQUAL(static_cast<T>(1), uf_Type.find(ufData, 9));
        CPPUNIT_ASSERT_EQUAL(static_cast<T>(4), uf_Type.find(ufData, 2));
        CPPUNIT_ASSERT_EQUAL(static_cast<T>(6), uf_Type.find(ufData, 6));
    }

    /**
     * @brief unionComponents_ShouldConnectComponentsIntoOneCluster tests whether components
     * belong to one cluster.
     */
    void unionComponents_ShouldConnectComponentsIntoOneCluster()
    {
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 1, 3));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 2, 8));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 1, 7));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 3, 9));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 4, 8));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 7, 3));
        CPPUNIT_ASSERT(uf_Type.connected(ufData, 4, 2));
    }

private:
    uf::UnionFindInfo<T> ufData{10};
    UF_Type<T> uf_Type;
};

/**
 * @brief find_ShouldReturnClusterId_WhenGivenComponent tests returning correct cluster id.
 * Explicit instatiation.
 * @tparam UnionFind_QuickUnion_Balanced
 * @tparam size_t
 */
template<>
void TestUnionFind<uf::UnionFind_QuickUnion_Balanced, size_t>::find_ShouldReturnClusterId_WhenGivenComponent()
{
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(1), uf_Type.find(ufData, 9));
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(2), uf_Type.find(ufData, 2));
    CPPUNIT_ASSERT_EQUAL(static_cast<size_t>(6), uf_Type.find(ufData, 6));
}


// Had to use aliases for the test suite registration, because in this particulat case
// preprocessor does not accept templates with more that 1 parameter
/**
 * @brief TestUnionFind_QuickFind template class is the partial specialized template
 * for the TestUnionFind unit test.
 */
template<typename T> using TestUnionFind_QuickFind = TestUnionFind<uf::UnionFind_QuickFind, T>;
/**
 * @brief TesUnionFind_QuickUnion template class is the partial specialized template
 * for the TestUnionFind unit test.
 */
template<typename T> using TestUnionFind_QuickUnion = TestUnionFind<uf::UnionFind_QuickUnion, T>;

/**
 * @brief TestUnionFind_QuickUnion_Balanced template class is the partial
 *  specialized template for the TestUnionFind unit test.
 */
template<typename T> using TestUnionFind_QuickUnion_Balanced = TestUnionFind<uf::UnionFind_QuickUnion_Balanced, T>;


}// namespace tests

//--------------------------------------------------------------------------------------------------
#endif // TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
