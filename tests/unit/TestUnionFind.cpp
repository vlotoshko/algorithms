/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 22-Oct-2020
 */

//--------------------------------------------------------------------------------------------------
#include "catch2/catch.hpp"
#include "UnionFind.hpp"
#include "Tools.hpp"
//--------------------------------------------------------------------------------------------------

namespace tests
{
//TEMPLATE_PRODUCT_TEST_CASE("Union-find testing", "[union_find]",
//                           (uf::UnionFind_QuickFind, uf::UnionFind_QuickUnion), (size_t)) {
//    uf::UnionFindInfo<typename TestType::ElementType> ufData{10};
//    TestType unionFind;
//    unionFind.unionComponents(ufData, 1, 3);
//    unionFind.unionComponents(ufData, 2, 8);
//    unionFind.unionComponents(ufData, 1, 7);
//    unionFind.unionComponents(ufData, 3, 9);
//    unionFind.unionComponents(ufData, 4, 8);
//    GIVEN( "Non directed graph" ) {
//        WHEN( "Get average degree" ) {
//            THEN( "Average degree of the graph returns" ) {
//                REQUIRE( static_cast<typename TestType::ElementType>(1) == unionFind.find(ufData, 9) );
//                REQUIRE( static_cast<typename TestType::ElementType>(4) == unionFind.find(ufData, 2) );
//                REQUIRE( static_cast<typename TestType::ElementType>(6) == unionFind.find(ufData, 6) );
//            }
//        }
//        WHEN( "Get average degree" ) {
//            THEN( "Average degree of the graph returns" ) {
//                REQUIRE( unionFind.connected(ufData, 1, 3));
//                REQUIRE( unionFind.connected(ufData, 2, 8));
//                REQUIRE( unionFind.connected(ufData, 1, 7));
//                REQUIRE( unionFind.connected(ufData, 3, 9));
//                REQUIRE( unionFind.connected(ufData, 4, 8));
//                REQUIRE( unionFind.connected(ufData, 7, 3));
//                REQUIRE( unionFind.connected(ufData, 4, 2));
//            }
//        }
//    }
//}

SCENARIO( "Union-find testing", "[union_find]" ) {
    uf::UnionFindInfo<size_t> ufData{10};

    auto unionComponents = [](auto & unionFind, auto & ufData)
    {
        unionFind.unionComponents(ufData, 1, 3);
        unionFind.unionComponents(ufData, 2, 8);
        unionFind.unionComponents(ufData, 1, 7);
        unionFind.unionComponents(ufData, 3, 9);
        unionFind.unionComponents(ufData, 4, 8);
    };

    auto checkClusterFound = [](auto & unionFind, auto & ufData)
    {
        REQUIRE( static_cast<size_t>(1) == unionFind.find(ufData, 9) );
        REQUIRE( static_cast<size_t>(4) == unionFind.find(ufData, 2) );
        REQUIRE( static_cast<size_t>(6) == unionFind.find(ufData, 6) );
    };


    auto checkComponentsConnected = [](auto & unionFind, auto & ufData)
    {
        REQUIRE( unionFind.connected(ufData, 1, 3));
        REQUIRE( unionFind.connected(ufData, 2, 8));
        REQUIRE( unionFind.connected(ufData, 1, 7));
        REQUIRE( unionFind.connected(ufData, 3, 9));
        REQUIRE( unionFind.connected(ufData, 4, 8));
        REQUIRE( unionFind.connected(ufData, 7, 3));
        REQUIRE( unionFind.connected(ufData, 4, 2));
    };

    GIVEN( "UnionFind struct with quick find" ) {
        uf::UnionFind_QuickFind<size_t> unionFind;
        unionComponents(unionFind, ufData);
        WHEN( "Components are united" ) {
            THEN( "Their clusters can be found" ) {
                checkClusterFound(unionFind, ufData);
            }
        }
        WHEN( "Given UnionFindInfo" ) {
            THEN( "Check componets are connected" ) {
                checkComponentsConnected(unionFind, ufData);
            }
        }
    }
    GIVEN( "UnionFind struct with quick union" ) {
        uf::UnionFind_QuickUnion<size_t> unionFind;
        unionComponents(unionFind, ufData);
        WHEN( "Components are united" ) {
            THEN( "Their clusters can be found" ) {
                checkClusterFound(unionFind, ufData);
            }
        }
        WHEN( "Given UnionFindInfo" ) {
            THEN( "Check componets are connected" ) {
                checkComponentsConnected(unionFind, ufData);
            }
        }
    }
    GIVEN( "UnionFind balanced struct with quick union" ) {
        uf::UnionFind_QuickUnion_Balanced<size_t> unionFind;
        unionComponents(unionFind, ufData);
        WHEN( "Components are united" ) {
            THEN( "Their clusters can be found" ) {
                REQUIRE( static_cast<size_t>(1) == unionFind.find(ufData, 9) );
                REQUIRE( static_cast<size_t>(2) == unionFind.find(ufData, 2) );
                REQUIRE( static_cast<size_t>(6) == unionFind.find(ufData, 6) );
            }
        }
        WHEN( "Given UnionFindInfo" ) {
            THEN( "Check componets are connected" ) {
                checkComponentsConnected(unionFind, ufData);
            }
        }
    }
}

}// namespace tests
