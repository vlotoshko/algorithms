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

namespace tests
{

SCENARIO( "Graph testing", "[graph]" ) {

    GIVEN( "Non directed graph" ) {
        using Strategy = graph::NonDirectedGraphPolicy<graph::Graph>;
        graph::Graph graph {10};
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
            THEN( "isCyclic returns true" ) {
                REQUIRE( graph::Cyclic<graph::Graph>{graph}.isCyclic() );
                REQUIRE( !graph::Cyclic<graph::Graph>{gr}.isCyclic() );
            }
        }
        WHEN( "Depth-first search of the graph" ) {
            std::vector<bool> b(graph.vertexCount());
            graph::depthFirstSearh(graph, 0, b);
            THEN( "Count of steps returns" ) {
                REQUIRE( b[4] );
                REQUIRE( b[0] );
                REQUIRE( !b[5] );
            }
        }
        WHEN( "Depth-first paths generate" ) {
            graph::DepthFirstPaths<graph::Graph > dfp(graph, 0);
            THEN( "Depth-first paths are generated" ) {
                REQUIRE( dfp.hasPathTo(4) );
                REQUIRE( dfp.hasPathTo(0) );
                REQUIRE( !dfp.hasPathTo(5) );
                // TODO: dfp.pathTo
            }
        }
        WHEN( "Graph is Bipartite" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 0, 3);
            Strategy::addEdge(gr, 2, 4);
            Strategy::addEdge(gr, 3, 9);
            Strategy::addEdge(gr, 9, 4);
            THEN( "TwoColored.isBipartite returns true" ) {
                REQUIRE( graph::TwoColored{gr}.isBipartite() );

                Strategy::addEdge(gr, 0, 2);
                REQUIRE( !graph::TwoColored{gr}.isBipartite() );
            }
        }
        WHEN( "Breadth-first paths generate" ) {
            graph::BreadthFirstPaths bfp(graph, 0);
            THEN( "Breadth-first paths are generated" ) {
                REQUIRE( bfp.hasPathTo(4) );
                REQUIRE( bfp.hasPathTo(0) );
                REQUIRE( !bfp.hasPathTo(5) );
            }
        }
    }

    GIVEN( "Directed graph" ) {
        using Strategy = graph::DirectedGraphPolicy<graph::Graph>;

        WHEN( "Reverse directed graph" ) {
            graph::Graph graph {10};
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
            graph::BreadthFirstPaths bfp(graph, 0);
            THEN( "Reversed graph returns" ) {
                auto reversed = graph::reverse<Strategy>(graph);
        //        std::cout << graph::toString(graph_);
        //        std::cout << graph::toString(*reversed);
            }
        }
        WHEN( "Directed graph is cyclic" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 5, 4);
            Strategy::addEdge(gr, 4, 7);
            Strategy::addEdge(gr, 5, 7);
            Strategy::addEdge(gr, 5, 1);
            Strategy::addEdge(gr, 4, 0);
            Strategy::addEdge(gr, 0, 2);
            Strategy::addEdge(gr, 3, 7);
            Strategy::addEdge(gr, 1, 3);
            Strategy::addEdge(gr, 7, 2);
            Strategy::addEdge(gr, 6, 2);
            Strategy::addEdge(gr, 3, 6);
            Strategy::addEdge(gr, 6, 0);
            Strategy::addEdge(gr, 6, 4);
            THEN( "isCyclic returns true" ) {
                REQUIRE( !graph::DirectedCyclic<graph::Graph>{gr}.isCyclic() );
                Strategy::addEdge(gr, 6, 5);
                REQUIRE( graph::DirectedCyclic<graph::Graph>{gr}.isCyclic() );
            }
        }
        WHEN( "Depth-first ordering traversing" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 0, 3);
            Strategy::addEdge(gr, 2, 4);
            Strategy::addEdge(gr, 2, 7);
            Strategy::addEdge(gr, 9, 4);
            Strategy::addEdge(gr, 0, 6);
            Strategy::addEdge(gr, 3, 9);
            Strategy::addEdge(gr, 6, 7);
            graph::DepthFirstOrder<graph::Graph> dfo(gr);

            auto preOder = dfo.pre();
            auto preGet = [&preOder](){ auto item = preOder.front(); preOder.pop(); return item; };

            auto postOder = dfo.post();
            auto postGet = [&postOder](){ auto item = postOder.front(); postOder.pop(); return item; };

            auto revPostOder = dfo.reversePost();
            auto revPostGet = [&revPostOder](){ auto item = revPostOder.top(); revPostOder.pop(); return item; };
            THEN( "Orderings of the graph returns" ) {
                REQUIRE( static_cast<size_t>(0) == preGet() );
                REQUIRE( static_cast<size_t>(3) == preGet() );
                REQUIRE( static_cast<size_t>(9) == preGet() );
                REQUIRE( static_cast<size_t>(4) == preGet() );
                REQUIRE( static_cast<size_t>(6) == preGet() );
                REQUIRE( static_cast<size_t>(7) == preGet() );
                REQUIRE( static_cast<size_t>(1) == preGet() );
                REQUIRE( static_cast<size_t>(2) == preGet() );
                REQUIRE( static_cast<size_t>(5) == preGet() );
                REQUIRE( static_cast<size_t>(8) == preGet() );

                REQUIRE( static_cast<size_t>(4) == postGet() );
                REQUIRE( static_cast<size_t>(9) == postGet() );
                REQUIRE( static_cast<size_t>(3) == postGet() );
                REQUIRE( static_cast<size_t>(7) == postGet() );
                REQUIRE( static_cast<size_t>(6) == postGet() );
                REQUIRE( static_cast<size_t>(0) == postGet() );
                REQUIRE( static_cast<size_t>(1) == postGet() );
                REQUIRE( static_cast<size_t>(2) == postGet() );
                REQUIRE( static_cast<size_t>(5) == postGet() );
                REQUIRE( static_cast<size_t>(8) == postGet() );

                REQUIRE( static_cast<size_t>(8) == revPostGet() );
                REQUIRE( static_cast<size_t>(5) == revPostGet() );
                REQUIRE( static_cast<size_t>(2) == revPostGet() );
                REQUIRE( static_cast<size_t>(1) == revPostGet() );
                REQUIRE( static_cast<size_t>(0) == revPostGet() );
                REQUIRE( static_cast<size_t>(6) == revPostGet() );
                REQUIRE( static_cast<size_t>(7) == revPostGet() );
                REQUIRE( static_cast<size_t>(3) == revPostGet() );
                REQUIRE( static_cast<size_t>(9) == revPostGet() );
                REQUIRE( static_cast<size_t>(4) == revPostGet() );
            }
        }
        WHEN( "Kosaraju SCC is calculated for the graph" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 0, 3);
            Strategy::addEdge(gr, 2, 4);
            Strategy::addEdge(gr, 2, 7);
            Strategy::addEdge(gr, 9, 4);
            Strategy::addEdge(gr, 0, 6);
            Strategy::addEdge(gr, 3, 9);
            Strategy::addEdge(gr, 6, 7);
            Strategy::addEdge(gr, 4, 0);
            graph::KosarajuSCC<graph::Graph> KSCC(gr);
            THEN( "Information about strong coupled components returns" ) {
                REQUIRE( static_cast<size_t>(7) == KSCC.count() );
                REQUIRE( static_cast<size_t>(5) == KSCC.id(0) );
                REQUIRE( static_cast<size_t>(5) == KSCC.id(3) );
                REQUIRE( static_cast<size_t>(5) == KSCC.id(4) );
                REQUIRE( static_cast<size_t>(5) == KSCC.id(9) );
                REQUIRE( static_cast<size_t>(0) == KSCC.id(8) );

                REQUIRE( KSCC.stronglyConnected(0, 9) );
                REQUIRE( KSCC.stronglyConnected(3, 4) );
                REQUIRE( !KSCC.stronglyConnected(3, 7) );
            }
        }
        WHEN( "CoupledComponent structure generates" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 0, 3);
            Strategy::addEdge(gr, 2, 4);
            Strategy::addEdge(gr, 2, 7);
            Strategy::addEdge(gr, 9, 4);
            Strategy::addEdge(gr, 0, 6);
            Strategy::addEdge(gr, 3, 9);
            Strategy::addEdge(gr, 6, 7);
            Strategy::addEdge(gr, 4, 0);
            graph::CoupledComponents coupledComponents(gr);
            THEN( "Structure with properly coupled components returns" ) {
                REQUIRE( coupledComponents.connected(0, 9) );
                REQUIRE( coupledComponents.connected(6, 7) );
                REQUIRE( !coupledComponents.connected(8, 7) );
                REQUIRE( static_cast<size_t>(0) == coupledComponents.id(9) );
                REQUIRE( static_cast<size_t>(4) == coupledComponents.id(8) );
            }
        }
        WHEN( "Transitive closure structure generates" ) {
            graph::Graph gr{10};
            Strategy::addEdge(gr, 0, 3);
            Strategy::addEdge(gr, 2, 4);
            Strategy::addEdge(gr, 2, 7);
            Strategy::addEdge(gr, 9, 4);
            graph::TransitiveClosure tc(gr);
            THEN( "Returns true if components are reachable" ) {
                REQUIRE( tc.reachable(0, 3) );
                REQUIRE( tc.reachable(7, 7) );
                REQUIRE( !tc.reachable(0, 9) );
            }
        }
    }
}

} // namespace tests
