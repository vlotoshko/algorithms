/**
 * -------------------------------------------------------------------------------------------------
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @skype vlotoshko
 * @date 11-Jun-2018
 * -------------------------------------------------------------------------------------------------
 */

// -------------------------------------------------------------------------------------------------
#ifndef GRAPH_ALGORITHMS_HPP
#define GRAPH_ALGORITHMS_HPP
// -------------------------------------------------------------------------------------------------

// -------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <string>
#include <vector>
#include <map>
#include <stack>
#include <queue>
#include <iostream>
#include <memory>
#include <sstream>
#include <functional>
// -------------------------------------------------------------------------------------------------

namespace graph
{

/**
 * ----------------------------------------------------------------------------------------
 * @brief The toString template function represents graph's information as string
 * @param graph
 * @return graph's information as string
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
std::string toString(const G & g)
{
    std::ostringstream os;
    os << "vertexes: " << g.vertexCount() << "; edges: " << g.edgeCount() << std::endl;
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        os << v << ": ";
        for (auto const & edge : edges)
        {
            os << edge.other(v) << " ";
        }
        os << std::endl;
    }
    return os.str();
}

/**
 * ----------------------------------------------------------------------------------------
 * @brief The degree template function returns the degree of the given vertex
 * @param graph
 * @param vertex
 * @return degree of given vertex
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
size_t degree(const G & g, const size_t & v) { return g[v].size(); }

/**
 * ----------------------------------------------------------------------------------------
 * @brief The maxDegree template function returns the max degree of the given graph
 * @param graph
 * @return max degree of given graph
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
size_t maxDegree(const G & g)
{
    size_t max = 0;
    for (size_t i = 0; i < g.vertexCount(); ++i)
    {
        size_t d = degree(g, i);
        if (d > max)
            max = d;
    }
    return max;
}

/**
 * ----------------------------------------------------------------------------------------
 * @brief The avgDegree template function calculates the average degree of the given graph
 * @param graph
 * @tparam strategy determines wether graph is directed or non-directed
 * @return average degree of given graph
 * ----------------------------------------------------------------------------------------
 */
template<typename Strategy, typename G>
size_t avgDegree(const G & g) { return Strategy::factor() * g.edgeCount() / g.vertexCount(); }

/**
 * ----------------------------------------------------------------------------------------
 * @brief The selfLoops template function calculates vertexes self loops
 * @param graph
 * @tparam strategy determines wether graph is directed or non-directed
 * @return vertexes self loops count
 * ----------------------------------------------------------------------------------------
 */
template<typename Strategy, typename G>
size_t selfLoops(const G & g)
{
    size_t count = 0;

    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            if (edge.other(v) == v)
            {
                ++count;
            }
        }
    }
    return count / Strategy::factor();
}

/**
 * ----------------------------------------------------------------------------------------
 * @brief The reverse template function reverses the given graph
 * @param graph
 * @tparam strategy determines wether graph is directed or non-directed
 * @return reversed graph
 * ----------------------------------------------------------------------------------------
 */
template<typename Strategy, typename G>
std::unique_ptr<G> reverse(const G & g)
{
    auto reversed = std::make_unique<Graph>(g.vertexCount());
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        auto const & edges = g[v];
        for (auto const & edge : edges)
        {
            Strategy::addEdge(*reversed, edge.other(v), v);
        }
    }
    return reversed;
}


/**
 * ----------------------------------------------------------------------------------------
 * @brief The depthFirstSearh template function traverses graph using Depth-first search
 * algorithm
 * @param graph
 * @param initial vertex
 * @param container to save results of accessing vertexes from initial vertex
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
void depthFirstSearh(const G & g, const size_t & s, std::vector<bool> & marked)
{
    std::function<void(const G & g, const size_t & s)> dfs;
    dfs = [&marked, &dfs](const G & g, const size_t & v) -> void {
        marked[v] = true;
        for (auto const & edge : g[v])
        {
            auto w = edge.other(v);
            if (!marked[w])
            {
    //            std::cout << v << " - " << w << std::endl;
                dfs(g, w);
            }
        }
    };

    dfs(g, s);
}


/**
 * ----------------------------------------------------------------------------------------
 * @class DepthFirstPaths
 * @brief The DepthFirstPaths template class finds paths to the vertexes in the given graph
 *
 * The DepthFirstPaths class finds paths to the vertexes in the given graph
 * using depth-first search algorithm.
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
class DepthFirstPaths
{
public:
    /**
     * @brief DepthFirstPaths constructor
     * @param graph
     * @param initial vertex
     *
     * DepthFirstPaths constructor explores graph and discovers paths from initial
     * vertex to other vertexes in the graph.
     */
    DepthFirstPaths(const G & g, const size_t & s);

    /// @return true if there is a paths to given vertex
    bool hasPathTo(const size_t & v) const { return marked_[v]; }

    /// @returns path as string to the given vertex
    std::string pathTo(const size_t &  v) const;
private:
    /**
     * @brief modification of the depth-first search algorithm
     * @param graph
     * @param initial vertex
     *
     * Explores graph using depth-first search algorithm and saves to the edge
     * container index of vertex from which current vertex was found.
     */
    void dfs(const Graph & g, const size_t & v);

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;
    /// container of edges from which current vertex was found
    std::vector<size_t> edgeTo_;
    /// initial vertex index
    size_t s_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class DepthFirstOrder
 * @brief The DepthFirstOrder template class saves vertexes in different orders exploring
 * the given graph
 *
 * The DepthFirstOrder class saves vertexes in pre-, post- and reversed orders while
 * exploring the given graph.
 * Graph is traversed using depth-first search algorithm.
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
class DepthFirstOrder
{
public:
    /**
     * @brief DepthFirstOrder constructor
     * @param graph
     *
     * DepthFirstOrder constructor explores graph and saves vertexes in pre-,
     * post- and reversed orders
     */
    explicit DepthFirstOrder(const G & g);

    /// @returns vertexes in the reversed order
    std::stack<size_t> & reversePost() { return reversePost_; }
    /// @returns vertexes in the pre- order
    std::queue<size_t> & pre() { return pre_; }
    /// @returns vertexes in the post- order
    std::queue<size_t> & post() { return post_; }
private:
    /**
     * @brief modification of the depth-first search algorithm
     * @param graph
     * @param initial vertex
     *
     * Explores graph using depth-first search algorithm and saves vertexes
     * into three containers unsing different order saving
     */
    void dfs(const G & g, const size_t & v);

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;
    /// holds vertexes in the reversed order
    std::stack<size_t> reversePost_;
    /// holds vertexes in the pre- order
    std::queue<size_t> pre_;
    /// holds vertexes in the post- order
    std::queue<size_t> post_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class Cyclic
 * @brief The Cyclic template class defines whether graph has cycles or not
 *
 * The Cyclic template class defines whether non-directed graph has cycles or not, using
 * depth-first search algorithm.
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
class Cyclic
{
public:
    /**
     * @brief Cyclic constructor explores graph and searches for the cycles
     * @param non-directed graph
     */
    explicit Cyclic(const G & g);

    /// @returns true if given graph is cyclic
    bool isCyclic() const { return hasCycle_; }
private:
    /**
     * @brief modification of the depth-first search algorithm to find cycles
     * @param graph
     * @param initial vertex
     * @param initial vertex of previous iteration
     */
    void dfs(const G & g, const size_t & v, const size_t & u);

    /// equals true if graph has cycles
    bool hasCycle_;
    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class DirectedCyclic
 * @brief The DirectedCyclic template class defines whether directed graph has cycles or not
 *
 * The DirectedCyclic template class defines whether directed graph has cycles or not,
 * using depth-first search algorithm.
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
class DirectedCyclic
{
public:
    /**
     * @brief DirectedCyclic constructor explores graph and searches for the cycles
     * @param directed graph
     */
    explicit DirectedCyclic(const G & g);

    /// @returns true if given graph is cyclic
    bool isCyclic() const { return cycle_.size() > 0; }

    /// @returns a container of cycle edges
    std::stack<size_t> cycle() const { return cycle; }
private:
    /**
     * @brief modification of the depth-first search algorithm to find cycles
     * @param directed graph
     * @param initial vertex
     *
     * Explores directed graph using depth-first search algorithm and saves vertexes
     * into three containers unsing different order saving
     */
    void dfs(const G & g, const size_t & v);

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;
    /// holds information wether vertex was already visited in the current iteration
    std::vector<bool> onStack_;
    /// edges from which current vertex was found
    std::vector<size_t> edgeTo_;
    /// cycle edges
    std::stack<size_t> cycle_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class Topological
 * @brief The Topological template class sorts directed graph in the topological way
 *
 * The Topological template class sorts directed graph in the topological way, using
 * DepthFirstOrder object.
 * Reversed post- order actually is the topological oreder.
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
class Topological
{
public:
    /**
     * @brief Topological constructor sorts graph in the topological way
     * @param directed graph
     */
    explicit Topological(const G & g);

    /// @returns vertexes ordered topologicaly
    std::stack<size_t> & order() { return dfo_.reversePost(); }

    /// @returns true if graph is directed uncyclic
    bool isDAG() const { return isDAG_; }
private:

    /// object that holds topologicaly ordered vertexes
    DepthFirstOrder<G> dfo_;
    /// true if graph is directed and uncycled
    bool isDAG_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class KosarajuSCC
 * @brief The KosarajuSCC template class searches for Strong Coupled Components in the
 * given graph
 *
 * The KosarajuSCC template class searches for Strong Coupled Components using
 * topologicaly sorted order
 * ----------------------------------------------------------------------------------------
 */
template<typename G>
class KosarajuSCC
{
public:
    /**
     * @brief KosarajuSCC constructor searches for Strong Coupled Components
     * @param directed graph
     */
    explicit KosarajuSCC(const G & g);

    /// @returns true if given two vertexes are strongly coupled
    bool stronglyConnected(const size_t & v, const size_t & w) const { return id_[v] == id_[w]; }

    /// @returns the count of strongly coupled components in the given graph
    size_t count() const { return count_; }

    /// @returns id of the component to which belongs the given vertex
    size_t id(const size_t & v) const { return id_[v]; }
private:
    /**
     * @brief modification of the depth-first search algorithm to find the
     * Strong Coupled Components
     * @param directed graph
     * @param initial vertex
     *
     * Explores directed graph using depth-first search algorithm and searches
     * for the Strong Coupled Components
     */
    void dfs(const G & g, const size_t & v);

    /// the count of strongly coupled components in the given graph
    size_t count_;

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;

    /// holds ids of Strong Coupled Components for erevy vertex
    std::vector<size_t> id_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class TransitiveClosure
 * @brief The TransitiveClosure class explores grash and finds out is there parh from one
 * vertex to other
 *
 * The TransitiveClosure class explores grash using depth-first search algorithm.
 * It fills bool matrix by results wether reachable one vertex from other.
 * ----------------------------------------------------------------------------------------
 */
class TransitiveClosure
{
public:
    /**
     * @brief TransitiveClosure constructor
     * @param graph whose paths will be explored
     *
     * TransitiveClosure constructor fills bool matrix by results wether
     * reachable one vertex from other.
     */
    explicit TransitiveClosure(const Graph & g);

    /**
     * @brief defines if the vertex is reachebla from other one
     * @param vertex from
     * @param vertex to
     * @return true if one vertex is reachable from other
     */
    bool reachable(const size_t & v, const size_t & w) const;
private:
    /// matrix with information wether reachable one vertex from other
    std::vector<std::vector<bool>> marked_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class BreadthFirstPaths
 * @brief The BreadthFirstPaths class finds paths to the vertexes in the given graph
 *
 * The BreadthFirstPaths class finds paths to the vertexes in the given graph using
 * breadth-first search algorithm.
 * ----------------------------------------------------------------------------------------
 */
class BreadthFirstPaths
{
public:
    /**
     * @brief BreadthFirstPaths constructor
     * @param graph
     * @param initial vertex
     *
     * BreadthFirstPaths constructor explores graph and discovers paths from initial
     * vertex to other vertexes in the graph.
     */
    BreadthFirstPaths(const Graph & g, const size_t & s);

    /// @return true if there is a paths to given vertex
    bool hasPathTo(const size_t & v) const { return marked_[v]; }

    /// @returns path as string to the given vertex
    std::string pathTo(const size_t & v) const;

private:
    /**
     * @brief implementation of the breadth-first search algorithm
     * @param graph
     * @param initial vertex
     *
     * Explores graph using breadth-first search algorithm and saves to the edge
     * container index of vertex from which current vertex was found.
     */
    void bfs(const Graph & g, const size_t & v);

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;
    /// container of edges from which current vertex was found
    std::vector<size_t> edgeTo_;
    /// initial vertex index
    size_t s_;
};

/**
 * ----------------------------------------------------------------------------------------
 * @class CoupledComponents
 * @brief The CoupledComponents class searches for coupled components
 *
 * The CoupledComponents class searches for coupled components in the given graph using
 * depth-first search algorithm.
 * ----------------------------------------------------------------------------------------
 */
class CoupledComponents
{
public:
    /**
     * @brief CoupledComponents constructor searches for coupled components
     * @param graph
     */
    explicit CoupledComponents(const Graph & g);

    /// @returns true if two vertexes are connected
    bool connected(const size_t & v, const size_t & w) const { return id_[v] == id_[w]; }

    /// @returns the count of strongly coupled components in the given graph
    size_t componentsCount() const { return count_; }

    /// @returns id of the component to which belongs the given vertex
    size_t id(const size_t & v) const { return id_[v]; }

private:
    /**
     * @brief modification of the depth-first search algorithm to find the coupled
     * components
     * @param graph
     * @param initial vertex
     *
     * Explores graph using depth-first search algorithm and searches for the coupled
     * components
     */
    void dfs(const Graph & g, const size_t & v);

    /// the count of strongly coupled components in the given graph
    size_t count_;

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;

    /// holds ids of Strong Coupled Components for erevy vertex
    std::vector<size_t> id_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class TwoColored
 * @brief The TwoColored class defines wether graph is bipartite or not
 *
 * The TwoColored class defines wether graph is bipartite or not, using depth-first search
 * algorithm.
 * ----------------------------------------------------------------------------------------
 */
class TwoColored
{
public:
    /**
     * @brief TwoColored constructor explores graph and defines wether graph is bipartite
     * @param non-directed graph
     */
    explicit TwoColored(const Graph& g);

    /// @returns true if graph is bipartite
    bool isBipartite() const { return isTwoColors_; }
private:
    /**
     * @brief modification of the depth-first search algorithm to define wether graph is
     * bipartite
     * @param graph
     * @param initial vertex
     */
    void dfs(const Graph& g, const size_t & v);

    /// true if graph is bipartite
    bool isTwoColors_;

    /// holds information wether vertex was already visited in the graph
    std::vector<bool> marked_;

    /// holds information about vertexes' 'colors'
    std::vector<bool> colors_;
};


/**
 * ----------------------------------------------------------------------------------------
 * @class SymbolGraph
 * @brief The SymbolGraph class represents graph where vertexes are strings
 *
 * The TwoColored class defines wether graph is bipartite or not, using depth-first search
 * algorithm.
 * ----------------------------------------------------------------------------------------
 */
class SymbolGraph
{
public:
    /**
     * @brief SymbolGraph constructor creates symbolic graph reading data from file
     * @param file name
     */
    explicit SymbolGraph(const std::string & fileName);

    /**
     * @brief SymbolGraph constructor creates empty symbolic graph of the given size
     * @param size of the graph
     */
    explicit SymbolGraph(const size_t & size);

    /// destructs graph created in the heap
    ~SymbolGraph();

    SymbolGraph(const SymbolGraph&) = delete;
    SymbolGraph& operator= (const SymbolGraph&) = delete;

    /**
     * @brief adds new adge to the graph
     * @param vertex from
     * @param vertex to
     * @returns true if graph is not full and adge was added
     */
    bool addEdge(const std::string & v, const std::string & w);

    /// @returns reference to the created graph
    Graph & G() const { return *g_; }

    /// @returns true if symbolic graph containes given key
    bool contains(const std::string & key) const;

    /// @returns index of the given key or -1 if key does not exist
    int index(const std::string & key) const;

    /// @returns the name of the key by the given index
    std::string name(const size_t & index) const;

    /// @returns as string the vertex by the given index and all vertexes reachable
    /// from given vertex
    std::string lexical(const size_t & index) const;
private:
    /// table of names string -> index
    std::map<std::string, size_t> st_;
    /// inverted indexes index -> string
    std::vector<std::string> keys_;
    /// base graph
    Graph * g_;
};



// -------------------------------------------------------------------------------
// ---------------- Template classes definitions ---------------------------------
// -------------------------------------------------------------------------------


// -------------------------------------------------------------------------------
// ----- DepthFirstPaths -----
//
template <typename G>
DepthFirstPaths<G>::DepthFirstPaths(const G & g, const size_t & s)
    : marked_(g.vertexCount(), false), edgeTo_(g.vertexCount()), s_(s)
{
    dfs(g ,s);
}

template <typename G>
std::string DepthFirstPaths<G>::pathTo(const size_t & v) const
{
    std::stringstream pathStr;
    if (!hasPathTo(v))
    {
        pathStr << "none";
        return pathStr.str();
    }

    std::stack<size_t> path;

    for (size_t i = v; i != s_; i = edgeTo_[i])
    {
        path.push(i);
    }
    path.push(s_);

    while (!path.empty())
    {
       pathStr << path.top();
       path.pop();
       pathStr << (!path.empty() ? " - " : "");
    }
    return pathStr.str();
}

template <typename G>
void DepthFirstPaths<G>::dfs(const Graph & g, const size_t & v)
{
    marked_[v] = true;
    for (auto const & edge : g[v])
    {
        auto w = edge.other(v);
        if (!marked_[w])
        {
//            std::cout << v << " - " <<w << std::endl;
            edgeTo_[w] = v;
            dfs(g, w);
        }
    }
}


// -------------------------------------------------------------------------------
// ----- DepthFirstOrder -----
//
template <typename G>
DepthFirstOrder<G>::DepthFirstOrder(const G & g)
    : marked_(g.vertexCount(), false), reversePost_(), pre_(), post_()
{
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        if (!marked_[v])
            dfs(g, v);
    }
}

template <typename G>
void DepthFirstOrder<G>::dfs(const G & g, const size_t & v)
{
    marked_[v] = true;
    pre_.push(v);
    for (auto const & edge : g[v])
    {
        auto w = edge.other(v);
        if (!marked_[w])
        {
            dfs(g, w);
        }
    }

    post_.push(v);
    reversePost_.push(v);
}


// -------------------------------------------------------------------------------
// ----- Cyclic -----
//

template <typename G>
Cyclic<G>::Cyclic(const G & g) : hasCycle_(false), marked_(g.vertexCount(), false)
{
    for (size_t s = 0; s < g.vertexCount(); ++s)
    {
       if(!marked_[s])
           dfs(g ,s, s);
    }
}

template <typename G>
void Cyclic<G>::dfs(const G & g, const size_t & v, const size_t & u)
{
    marked_[v] = true;
    for (auto const & edge : g[v])
    {
        auto w = edge.other(v);
        if (!marked_[w])
        {
            dfs(g, w, v);
        }
        else if (w != u)
        {
            hasCycle_ = true;
        }
    }
}


// -------------------------------------------------------------------------------
// ----- DirectedCyclic -----
//

template <typename G>
DirectedCyclic<G>::DirectedCyclic(const G & g)
    : marked_(g.vertexCount(), false), onStack_(g.vertexCount(), false), edgeTo_(g.vertexCount())
{
    for (size_t s = 0; s < g.vertexCount(); ++s)
    {
       if(!marked_[s])
           dfs(g ,s);
    }
}

template <typename G>
void DirectedCyclic<G>::dfs(const G & g, const size_t & v)
{
    marked_[v] = true;
    onStack_[v] = true;
    auto const & edges = g[v];
    for (auto const & edge : edges)
    {
        auto w = edge.other(v);
        if(isCyclic())
        {
            return;
        }
        else if (!marked_[w])
        {
            edgeTo_[w] = v;
            dfs(g, w);
        }
        else if (onStack_[w])
        {
            for (size_t i = v; i != w; i = edgeTo_[i])
            {
                cycle_.push(i);
            }
            cycle_.push(w);
            cycle_.push(v);
        }
    }
    onStack_[v] = false;
}


// -------------------------------------------------------------------------------
// ----- Topological -----
//

template <typename G>
Topological<G>::Topological(const G & g) : dfo_(G(0)), isDAG_(false)
{
    isDAG_ = !DirectedCyclic<G>(g).isCyclic();
    if (isDAG_)
    {
        dfo_ = DepthFirstOrder<G>(g);
    }
}


// -------------------------------------------------------------------------------
// ----- KosarajuSCC -----
//

template <typename G>
KosarajuSCC<G>::KosarajuSCC(const G & g) : count_(0), marked_(g.vertexCount(), false), id_(g.vertexCount())
{
    auto r = reverse<DirectedGraphPolicy<G>>(g);
    DepthFirstOrder<G> order(*r);

    while (order.reversePost().size() > 0)
    {
        size_t i = order.reversePost().top();
        if (!marked_[i])
        {
            dfs(g, i);
            ++count_;
        }
        order.reversePost().pop();
    }
}

template <typename G>
void KosarajuSCC<G>::dfs(const G & g, const size_t & v)
{
    marked_[v] = true;
    id_[v] = count_;
    for (auto const & edge : g[v])
    {
        auto w = edge.other(v);
        if (!marked_[w])
        {
            dfs(g, w);
        }
    }
}

} // namespace graph

//--------------------------------------------------------------------------------------------------
#endif // GRAPH_ALGORITHMS_HPP
//--------------------------------------------------------------------------------------------------

