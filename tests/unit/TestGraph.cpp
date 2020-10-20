/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 20-Oct-2020
 */

//--------------------------------------------------------------------------------------------------
#include "catch2/catch.hpp"
#include "Graph.hpp"
#include "GraphAlgorithms.hpp"
#include "MinimalSpanningTree.hpp"
#include "ShortPaths.hpp"
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------

namespace tests
{

SCENARIO( "Graph testing", "[graph]" ) {

    GIVEN( "Non directed graph" ) {

        graph::Graph graph {10};
        using Strategy = graph::NonDirectedGraphPolicy<graph::Graph>;
        Strategy::addEdge(graph, 0, 3);
        Strategy::addEdge(graph, 2, 4);
        Strategy::addEdge(graph, 2, 7);
        Strategy::addEdge(graph, 9, 4);
        Strategy::addEdge(graph, 6, 7);
        Strategy::addEdge(graph, 0, 8);
        Strategy::addEdge(graph, 6, 3);
        Strategy::addEdge(graph, 1, 9);
        Strategy::addEdge(graph, 7, 9);
        Strategy::addEdge(graph, 2, 2);

        WHEN( "Get average degree" ) {
            THEN( "Average degree of the graph returns" ) {
                REQUIRE( static_cast<size_t>(2) ==
                         graph::avgDegree<graph::NonDirectedGraphPolicy<graph::Graph>>(graph) );
            }
        }
        WHEN( "Get max degree" ) {
            THEN( "Max degree of the graph returns" ) {
                REQUIRE( static_cast<size_t>(4) == graph::maxDegree(graph) );
            }
        }
        WHEN( "Get self-loops of the graph" ) {
            THEN( "Count of self-loops returns" ) {
                REQUIRE( static_cast<size_t>(1) ==
                         graph::selfLoops<graph::NonDirectedGraphPolicy<graph::Graph>>(graph) );
            }
        }
        WHEN( "Graph is cyclic" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 0, 3);
            Strategy::addEdge(gr, 2, 4);
            Strategy::addEdge(gr, 2, 7);
            Strategy::addEdge(gr, 9, 4);
            Strategy::addEdge(gr, 6, 7);
            THEN( "isCyclic returnds true" ) {
                REQUIRE( graph::Cyclic<graph::Graph>{graph}.isCyclic() );
                REQUIRE( graph::Cyclic<graph::Graph>{gr}.isCyclic() );
            }
        }
    }
}

} // namespace tests
