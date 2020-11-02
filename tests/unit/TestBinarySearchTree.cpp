/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 19-Oct-2020
 */

//--------------------------------------------------------------------------------------------------
#include "catch2/catch.hpp"
#include "BstUnbalanced.hpp"
#include "BstRedBlack.hpp"
#include "Tools.hpp"
//--------------------------------------------------------------------------------------------------

namespace tests
{

SCENARIO( "BinarySearchTree testing", "[bst]" ) {
    GIVEN( "BinarySearchTree with some items" ) {
        bst::BinarySearchTree<std::string, size_t> bst;
        bst.put("word", 0);
        bst.put("select", 0);
        bst.put("connect", 0);
        bst.put("car", 0);
        bst.put("car", 0);
        bst.put("cat", 0);
        bst.put("android", 0);
        bst.put("word", 0);

        WHEN( "Get value by key" ) {
            THEN( "Proper value returns" ) {
                REQUIRE( static_cast<size_t>(2) == bst.get("word") );
                REQUIRE( static_cast<size_t>(1) == bst.get("select") );
                REQUIRE( static_cast<size_t>(0) == bst.get("zero") );
            }
        }
        WHEN( "Delete node from BST" ) {
            REQUIRE( static_cast<size_t>(2) == bst.get("car") );
            bst.deleteNode("car");

            THEN( "Node should be deleted" ) {
                REQUIRE( static_cast<size_t>(0) == bst.get("car") );
            }
        }
        WHEN( "Get minimal value" ) {
            auto key = bst.min();
            THEN( "Key with minimal value returns" ) {
                REQUIRE( std::string{"android"} == key );
            }
        }
        WHEN( "Get maximal value" ) {
            auto key = bst.max();
            THEN( "Key with maximal value returns" ) {
                REQUIRE( std::string{"word"} == key );
            }
        }
        WHEN( "Get size of BST" ) {
            REQUIRE( static_cast<size_t>(6) == bst.size() );
            bst.deleteNode("car");
            bst.deleteNode("select");

            THEN( "Count of nodes returns" ) {
                REQUIRE( static_cast<size_t>(4) == bst.size() );
            }
        }
        WHEN( "Get sum of the values of BST" ) {
            REQUIRE( static_cast<size_t>(8) == bst.valueSum() );
            bst.deleteNode("car");
            bst.deleteNode("select");

            THEN( "Sum of all values returns" ) {
                REQUIRE( static_cast<size_t>(5) == bst.valueSum() );
            }
        }
        WHEN( "Get floor of the element" ) {
            THEN( "The floor element returns" ) {
                REQUIRE( std::string{"connect"} == bst.floor("cow") );
                REQUIRE( std::string{"android"} == bst.floor("ara") );
            }
        }
        WHEN( "Get ceiling of the element" ) {
            THEN( "The ceiling element returns" ) {
                REQUIRE( std::string{"select"} == bst.ceiling("flower") );
                REQUIRE( std::string{"word"} == bst.ceiling("star") );
            }
        }
        WHEN( "Get get element by rank" ) {
            THEN( "Proper element returns" ) {
                REQUIRE( std::string{"connect"} == bst.select(3) );
                REQUIRE( std::string{"android"} == bst.select(0) );
            }
        }
        WHEN( "Get get rank of the element" ) {
            THEN( "Proper rank returns" ) {
                REQUIRE( static_cast<size_t>(2) == bst.rank("cat") );
                REQUIRE( static_cast<size_t>(5) == bst.rank("word") );
                REQUIRE( static_cast<size_t>(0) == bst.rank("android") );
            }
        }
    }
}

} // namespace tests
