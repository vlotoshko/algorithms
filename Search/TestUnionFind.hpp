//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   30-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTUNIONFIND_HPP
#define TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ITestable.hpp"
#include "Search/UnionFind.hpp"

#include <map>
#include <memory>
//--------------------------------------------------------------------------------------------------

namespace uf // unionfind
{

enum class AlgId : int
{
    QUICK_FIND = 100,
    QUICK_UNION,
    QUICK_UNION_BALANCED,
};


// ------------------------------------------------------------------------------------------
// Runs union-find algorithm specified by the algorithm's id
//
template <typename T>
class TestUnionFind : public ITestable
{
public:
    using Alg = std::shared_ptr<UnionFind<T>>;
    TestUnionFind(AlgId algId, size_t count) : algId_(algId), elementsCount_(count) {}

    void runTest(tools::Timer & timer) override
    {
        auto iter = Algorithms.find(algId_);
        if(iter != Algorithms.end())
        {
            UnionFindInfo<T> uf(elementsCount_);

            // Generate pairs
//            std::cout << "generating data... " << std::flush;
            std::vector<std::pair<T, T>> pairs(elementsCount_);
            for (auto & item : pairs)
            {
                item.first  = tools::random<T>(0, elementsCount_);
                item.second = tools::random<T>(0, elementsCount_);
            }
            if (algId_ == AlgId::QUICK_UNION_BALANCED)
            {
                uf.sizes = std::vector<unsigned>(elementsCount_, 1);
            }
//            std::cout << "Ok" << std::endl;

            auto unionFind = iter->second;
            timer.start();
            for (auto & item : pairs)
            {
                unionFind->unionComponents(uf, item.first, item.second);
            }
            std::cout << unionFind->name() << std::endl;
            std::cout << "clasters: " << uf.clasters
                      << "; invoke find(): " << uf.findInvokes
                      << "; invoke union(): " << uf.unionInvokes
                      << std::endl;
        }
    }

    static std::map<AlgId, Alg> Algorithms;
private:
    AlgId algId_;
    size_t elementsCount_;
};


// ------------------------------------------------------------------------------------------
// Registry of the union-find algorithms
//
template <typename T>
std::map<AlgId, typename TestUnionFind<T>::Alg> TestUnionFind<T>::Algorithms =
{
      {AlgId::QUICK_FIND,           std::make_shared<UnionFind_QuickFind<T>>()}
    , {AlgId::QUICK_UNION,          std::make_shared<UnionFind_QuickUnion<T>>()}
    , {AlgId::QUICK_UNION_BALANCED, std::make_shared<UnionFind_QuickUnion_Balanced<T>>()}
};

} // namespace unionfind

//--------------------------------------------------------------------------------------------------
#endif // TESTUNIONFIND_HPP
//--------------------------------------------------------------------------------------------------
