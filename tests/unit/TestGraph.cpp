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
                REQUIRE_FALSE( graph::Cyclic<graph::Graph>{gr}.isCyclic() );
            }
        }
        WHEN( "Depth-first search of the graph" ) {
            std::vector<bool> b(graph.vertexCount());
            graph::depthFirstSearh(graph, 0, b);
            THEN( "Count of steps returns" ) {
                REQUIRE( b[4] );
                REQUIRE( b[0] );
                REQUIRE_FALSE( b[5] );
            }
        }
        WHEN( "Depth-first paths generate" ) {
            graph::DepthFirstPaths<graph::Graph > dfp(graph, 0);
            THEN( "Depth-first paths are generated" ) {
                REQUIRE( dfp.hasPathTo(4) );
                REQUIRE( dfp.hasPathTo(0) );
                REQUIRE_FALSE( dfp.hasPathTo(5) );
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
                REQUIRE_FALSE( graph::TwoColored{gr}.isBipartite() );
            }
        }
        WHEN( "Breadth-first paths generate" ) {
            graph::BreadthFirstPaths bfp(graph, 0);
            THEN( "Breadth-first paths are generated" ) {
                REQUIRE( bfp.hasPathTo(4) );
                REQUIRE( bfp.hasPathTo(0) );
                REQUIRE_FALSE( bfp.hasPathTo(5) );
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
                REQUIRE_FALSE( graph::DirectedCyclic<graph::Graph>{gr}.isCyclic() );
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
                REQUIRE_FALSE( KSCC.stronglyConnected(3, 7) );
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
                REQUIRE_FALSE( coupledComponents.connected(8, 7) );
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
                REQUIRE_FALSE( tc.reachable(0, 9) );
            }
        }
    }
    GIVEN( "SymbolGraph graph" ) {
        graph::SymbolGraph graph{10};
        graph.addEdge("key1", "key2");

        WHEN( "Edge was added to the graph" ) {
            graph.addEdge("key3", "key4");
            THEN( "Graph contains edge" ) {
                REQUIRE( graph.contains("key3") );
                REQUIRE( graph.contains("key4") );
            }
        }
        WHEN( "Capasity is over" ) {
            THEN( "Edge was not added to the graps" ) {
                REQUIRE( graph.addEdge("key3", "key7") );
                REQUIRE( graph.addEdge("key4", "key8") );
                REQUIRE( graph.addEdge("key5", "key9") );
                REQUIRE( graph.addEdge("key6", "key0") );
                REQUIRE_FALSE( graph.addEdge("keyX", "keyXX") );
            }
        }
        WHEN( "Given key exists" ) {
            THEN( "Contains function returns true" ) {
                REQUIRE( graph.contains("key1") );
                REQUIRE_FALSE( graph.contains("key0") );
            }
        }
        WHEN( "Given key exists" ) {
            THEN( "Index function returns index" ) {
                REQUIRE( 0 == graph.index("key1") );
                REQUIRE( 1 == graph.index("key2") );
                REQUIRE( -1 == graph.index("key does not exist") );
            }
        }
        WHEN( "Given indexes" ) {
            THEN( "Name of the key by index returns" ) {
                REQUIRE( std::string("key1") == graph.name(0) );
                REQUIRE( std::string("key2") == graph.name(1) );
                REQUIRE( std::string{} == graph.name(1000) );
            }
        }
        WHEN( "Graph has keys" ) {
            graph.addEdge("key1", "key3");
            graph.addEdge("key1", "key4");
            std::stringstream test;
            test << "key1" << std::endl
                 << "  " << "key2" << std::endl
                 << "  " << "key3" << std::endl
                 << "  " << "key4" << std::endl;
            THEN( "Lexical representation can be build" ) {
                REQUIRE( test.str() == graph.lexical(0));
            }
        }
    }

}

SCENARIO( "MinimalSpanningTree testing", "[mst]" ) {
    using Strategy = graph::NonDirectedGraphPolicy<graph::EdgeWeightedGraph>;
    using Edge = graph::EdgeWeightedGraph::EdgeType;

    GIVEN( "Non directed graph" ) {
        graph::EdgeWeightedGraph gr{10};

        Strategy::addEdge(gr, Edge{0, 1, 7});
        Strategy::addEdge(gr, Edge{1, 2, 4});
        Strategy::addEdge(gr, Edge{1, 3, 4});
        Strategy::addEdge(gr, Edge{1, 4, 11}); // this edge should not be present in MST
        Strategy::addEdge(gr, Edge{2, 5, 5});  // this edge should not be present in MST
        Strategy::addEdge(gr, Edge{3, 4, 6});
        Strategy::addEdge(gr, Edge{3, 5, 3});
        Strategy::addEdge(gr, Edge{4, 5, 13}); // this edge should not be present in MST

        auto checkEdgesExist = [](const auto & edges)
        {
            auto edgeExists = [](const auto & edges, Edge e)
            {
                return std::find(edges.begin(), edges.end(), e) != edges.end();
            };

            REQUIRE( edgeExists(edges, Edge{0, 1, 7}) );
            REQUIRE( edgeExists(edges, Edge{1, 2, 4}) );
            REQUIRE( edgeExists(edges, Edge{1, 3, 4}) );
            REQUIRE( edgeExists(edges, Edge{3, 5, 3}) );
            REQUIRE( edgeExists(edges, Edge{3, 4, 6}) );
            REQUIRE_FALSE( edgeExists(edges, Edge{2, 5, 5}) );
            REQUIRE_FALSE( edgeExists(edges, Edge{1, 4, 11}) );
            REQUIRE_FALSE( edgeExists(edges, Edge{4, 5, 13}) );

            double mstWeight = 0;
            for (auto const & edge : edges)
            {
                mstWeight += edge.weight();
            }
            REQUIRE( 24.0 == mstWeight );
        };

        WHEN( "PrimMST_Lazy algorithm applied to graph" ) {
            THEN( "Generated MST returns" ) {
                const auto edges = graph::PrimMST_Lazy(gr).edges();
                checkEdgesExist(edges);
            }
        }
        WHEN( "PrimMST_Energy algorithm applied to graph" ) {
            THEN( "Generated MST returns" ) {
                const auto edges = graph::PrimMST_Energy(gr).edges();
                checkEdgesExist(edges);
            }
        }
        WHEN( "KruskalMST algorithm applied to graph" ) {
            THEN( "Generated MST returns" ) {
                const auto edges = graph::KruskalMST(gr).edges();
                checkEdgesExist(edges);
            }
        }
    }
}

SCENARIO( "ShortPathes testing", "[short_paths]" ) {
    GIVEN( "EdgeWeightedGraph directed graph" ) {
        using Strategy = graph::DirectedGraphPolicy<graph::EdgeWeightedGraph>;
        using Edge = graph::EdgeWeightedGraph::EdgeType;
        graph::EdgeWeightedGraph gr{10};

        auto edgeExists = [](const auto & edges, Edge e)
        {
            return std::find(edges.begin(), edges.end(), e) != edges.end();
        };

        auto checkDistancies = [](const auto & sp)
        {
            REQUIRE( Approx(1.51) == sp.distTo(6) );
            REQUIRE( Approx(0.73) == sp.distTo(5) );
            REQUIRE( Approx(1.05) == sp.distTo(1) );
        };

        auto checkPaths = [](const auto & sp)
        {
            REQUIRE( sp.hasPathTo(1) );
            REQUIRE( sp.hasPathTo(5) );
            REQUIRE( sp.hasPathTo(6) );
            REQUIRE_FALSE( sp.hasPathTo(8) );
        };

        WHEN( "DijkstraSP algorithm applied to graph" ) {
            Strategy::addEdge(gr, Edge{4, 5, 0.35});
            Strategy::addEdge(gr, Edge{5, 4, 0.35});
            Strategy::addEdge(gr, Edge{4, 7, 0.37});
            Strategy::addEdge(gr, Edge{5, 7, 0.28});
            Strategy::addEdge(gr, Edge{7, 5, 0.28});
            Strategy::addEdge(gr, Edge{5, 1, 0.32});
    //        Strategy::addEdge(gr, Edge{4, 0, 0.38});
            Strategy::addEdge(gr, Edge{0, 4, 0.38});
            Strategy::addEdge(gr, Edge{0, 2, 0.26});
    //        Strategy::addEdge(gr, Edge{3, 7, 0.39});
            Strategy::addEdge(gr, Edge{7, 3, 0.39});
            Strategy::addEdge(gr, Edge{1, 3, 0.29});
            Strategy::addEdge(gr, Edge{2, 7, 0.34});
    //        Strategy::addEdge(gr, Edge{7, 2, 0.34});
            Strategy::addEdge(gr, Edge{6, 2, 0.40});
            Strategy::addEdge(gr, Edge{3, 6, 0.52});
            Strategy::addEdge(gr, Edge{6, 0, 0.58});
            Strategy::addEdge(gr, Edge{6, 4, 0.93});

            graph::DijkstraSP sp(gr, 0);
            THEN( "Distancies to the vertexes returns" ) {
                checkDistancies(sp);
            }
            THEN( "Information is there path to the given vertex returns" ) {
                checkPaths(sp);
            }
            THEN( "Edges to the destination point returns" ) {
                auto edges = sp.pathTo(6);
                REQUIRE( edgeExists(edges, Edge{0, 2, 0.26}) );
                REQUIRE( edgeExists(edges, Edge{2, 7, 0.34}) );
                REQUIRE( edgeExists(edges, Edge{7, 3, 0.39}) );
                REQUIRE( edgeExists(edges, Edge{3, 6, 0.52}) );

                REQUIRE_FALSE( edgeExists(edges, Edge{6, 2, 0.40}) );
                REQUIRE_FALSE( edgeExists(edges, Edge{6, 4, 0.93}) );
                REQUIRE_FALSE( edgeExists(edges, Edge{7, 5, 0.28}) );
            }
        }
        WHEN( "AcyclicShortPaths algorithm applied to graph" ) {
            Strategy::addEdge(gr, Edge{5, 4, 0.35});
            Strategy::addEdge(gr, Edge{4, 7, 0.37});
            Strategy::addEdge(gr, Edge{5, 7, 0.28});
            Strategy::addEdge(gr, Edge{5, 1, 0.32});
            Strategy::addEdge(gr, Edge{0, 2, 0.26});
            Strategy::addEdge(gr, Edge{3, 7, 0.39});
            Strategy::addEdge(gr, Edge{1, 3, 0.29});
            Strategy::addEdge(gr, Edge{7, 2, 0.34});
            Strategy::addEdge(gr, Edge{6, 2, 0.40});
            Strategy::addEdge(gr, Edge{3, 6, 0.17});
            Strategy::addEdge(gr, Edge{6, 4, 0.93});
            Strategy::addEdge(gr, Edge{0, 5, 0.73});

            REQUIRE_FALSE( graph::DirectedCyclic<graph::EdgeWeightedGraph>{gr}.isCyclic() );
            graph::AcyclicShortPaths sp(gr, 0);
            THEN( "Distancies to the vertexes returns" ) {
                checkDistancies(sp);
            }
            THEN( "Information is there path to the given vertex returns" ) {
                checkPaths(sp);
            }
            THEN( "Edges to the destination point returns" ) {
                auto edges = sp.pathTo(6);
                REQUIRE( edgeExists(edges, Edge{0, 5, 0.73}) );
                REQUIRE( edgeExists(edges, Edge{5, 1, 0.32}) );
                REQUIRE( edgeExists(edges, Edge{3, 6, 0.17}) );

                REQUIRE_FALSE( edgeExists(edges, Edge{6, 2, 0.40}) );
                REQUIRE_FALSE( edgeExists(edges, Edge{6, 4, 0.93}) );
                REQUIRE_FALSE( edgeExists(edges, Edge{5, 7, 0.28}) );
            }
        }
        WHEN( "AcyclicLongPaths algorithm applied to graph" ) {
            Strategy::addEdge(gr, Edge{5, 4, 0.35});
            Strategy::addEdge(gr, Edge{4, 7, 0.37});
            Strategy::addEdge(gr, Edge{5, 7, 0.28});
            Strategy::addEdge(gr, Edge{5, 1, 0.32});
            Strategy::addEdge(gr, Edge{0, 2, 0.26});
            Strategy::addEdge(gr, Edge{3, 7, 0.39});
            Strategy::addEdge(gr, Edge{1, 3, 0.29});
            Strategy::addEdge(gr, Edge{7, 2, 0.34});
            Strategy::addEdge(gr, Edge{6, 2, 0.40});
            Strategy::addEdge(gr, Edge{3, 6, 0.17});
            Strategy::addEdge(gr, Edge{6, 4, 0.93});
            Strategy::addEdge(gr, Edge{0, 5, 0.73});

            Strategy::addEdge(gr, Edge{1, 9, 0.73});
            Strategy::addEdge(gr, Edge{9, 6, 0.73});

            REQUIRE_FALSE( graph::DirectedCyclic<graph::EdgeWeightedGraph>{gr}.isCyclic() );
            graph::AcyclicLongPaths sp(gr, 0);
            THEN( "Distancies to the vertexes returns" ) {
                REQUIRE( Approx(2.51) == sp.distTo(6) );
            }
            THEN( "Information is there path to the given vertex returns" ) {
                checkPaths(sp);
            }
            THEN( "Edges to the destination point returns" ) {
                auto edges = sp.pathTo(6);
                REQUIRE( edgeExists(edges, Edge{0, 5, 0.73}) );
                REQUIRE( edgeExists(edges, Edge{5, 1, 0.32}) );
                REQUIRE( edgeExists(edges, Edge{1, 9, 0.73}) );

                REQUIRE_FALSE( edgeExists(edges, Edge{6, 2, 0.40}) );
                REQUIRE_FALSE( edgeExists(edges, Edge{6, 4, 0.93}) );
                REQUIRE_FALSE( edgeExists(edges, Edge{5, 7, 0.28}) );
            }
        }
    }

}

SCENARIO( "CriticalPathMethod testing", "[critical_path]" ) {
    GIVEN( "ContinuousJobs graph" ) {
        graph::ContinuousJobs jobs;

        jobs.emplace_back(graph::ContinuousJob{41.0, {1, 7, 9}});
        jobs.emplace_back(graph::ContinuousJob{51.0, {2}});
        jobs.emplace_back(graph::ContinuousJob{50.0, {}});
        jobs.emplace_back(graph::ContinuousJob{36.0, {}});
        jobs.emplace_back(graph::ContinuousJob{38.0, {}});
        jobs.emplace_back(graph::ContinuousJob{45.0, {}});
        jobs.emplace_back(graph::ContinuousJob{21.0, {3, 8}});
        jobs.emplace_back(graph::ContinuousJob{32.0, {3, 8}});
        jobs.emplace_back(graph::ContinuousJob{32.0, {2}});
        jobs.emplace_back(graph::ContinuousJob{29.0, {4, 6}});

        WHEN( "CriticalPathMethod algorithm applied to graph" ) {
            std::vector<graph::AcyclicLongPaths> alp;
            alp.push_back(graph::criticalPathMethod(jobs));
            auto const & acyclicLP = alp.front();
            THEN( "AcyclicLongPaths for critical path returns" ) {
                REQUIRE( Approx(0.0) == acyclicLP.distTo(0) );
                REQUIRE( Approx(41.0) == acyclicLP.distTo(1) );
                REQUIRE( Approx(123.0) == acyclicLP.distTo(2) );
                REQUIRE( Approx(91.0) == acyclicLP.distTo(3) );
                REQUIRE( Approx(70.0) == acyclicLP.distTo(4) );
                REQUIRE( Approx(0.0) == acyclicLP.distTo(5) );
                REQUIRE( Approx(70.0) == acyclicLP.distTo(6) );
                REQUIRE( Approx(41.0) == acyclicLP.distTo(7) );
                REQUIRE( Approx(91.0) == acyclicLP.distTo(8) );
                REQUIRE( Approx(41.0) == acyclicLP.distTo(9) );
                REQUIRE( Approx(173.0) == acyclicLP.distTo(21) );
            }
        }
    }
}

} // namespace tests
