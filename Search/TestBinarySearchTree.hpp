//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   30-May-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef TESTBINARYSEARCHTREE_HPP
#define TESTBINARYSEARCHTREE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "ITestable.hpp"
#include "Structures/BinarySearchTree.hpp"

#include <fstream>

//--------------------------------------------------------------------------------------------------

namespace bst // binary search tree
{

// ------------------------------------------------------------------------------------------
// Fills binary search tree with words from the text file
//
template <typename T>
class TestBST : public ITestable
{
public:
    TestBST(const std::string & fileName, unsigned /*repeats*/) : fileName_(fileName) {}

    void runTest(tools::Timer & timer) override
    {
        if(true)
        {
            timer.start();

            std::ifstream file;
            file.open (fileName_);
            BinarySearchTree<std::string, int> bst;

            std::string word;
            while (file >> word)
            {
                bst.put(word, 0);
            }

            if (bst.size() > 0)
            {
                std::cout << "size: " << bst.size() << std::endl;
                std::cout << "count: " << bst.valueSum() << std::endl;
                std::cout << "min: " << bst.min() << std::endl;
                std::cout << "max: " << bst.max() << std::endl;
//                std::string key;
//                std::cin >> key;
//                std::cout << "floor: " << bst.floor(key) << std::endl;
//                std::cout << "ceiling: " << bst.ceiling(key) << std::endl;
//                std::cout << "select: " << bst.select(1) << std::endl;
//                std::cout << "rank \"love\": " << bst.rank("memory") << std::endl;
//                bst.deleteNode("love");
//                std::cout << "rank \"love\": " << bst.rank("memory") << std::endl;
//                bst.put("love", 0);
//                bst.print();
//                std::cout << std::endl;

//                auto v = bst.keys("f", "m");
//                for (auto e : v)
//                {
//                    std::cout << e << " ";
//                }
//                std::cout << std::endl;
            }
        }
    }

private:
    std::string fileName_;
};


} // namespace binary search tree

//--------------------------------------------------------------------------------------------------
#endif // TESTBINARYSEARCHTREE_HPP
//--------------------------------------------------------------------------------------------------
