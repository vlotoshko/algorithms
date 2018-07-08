//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "GraphAlgorithms.hpp"

#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
//--------------------------------------------------------------------------------------------------

namespace graph
{

using GNode = Graph::GNode;


//--------------------------------------------------------------------------------------------------
// ------- DeepFirstSearch -----------------------------------------------
//
DeepFirstSearch::DeepFirstSearch(const Graph &g, size_t s) : marked_(g.vertexCount(), false)
{
    dfs(g ,s);
}

void DeepFirstSearch::dfs(const Graph & g, size_t v)
{
    marked_[v] = true;
    ++count_;
    GNode* n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
//            std::cout << v << " - " << n->value << std::endl;
            dfs(g, n->value);
        }
        n = n->next;
    }
}


//--------------------------------------------------------------------------------------------------
// ------- DeepFirstPaths -----------------------------------------------
//

DeepFirstPaths::DeepFirstPaths(const Graph &g, size_t s)
    : marked_(g.vertexCount(), false), edgeTo_(g.vertexCount()), s_(s)
{
    dfs(g ,s);
}

void DeepFirstPaths::dfs(const Graph & g, size_t v)
{
    marked_[v] = true;

    GNode* n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
//            std::cout << v << " - " << n->value << std::endl;
            edgeTo_[n->value] = v;
            dfs(g, n->value);
        }
        n = n->next;
    }
}

std::string DeepFirstPaths::pathTo(size_t v) const
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



//--------------------------------------------------------------------------------------------------
// ------- DepthFirstOrder ----------------------------------------------------
//

DepthFirstOrder::DepthFirstOrder(const Graph & g)
  : marked_(g.vertexCount(), false)
  , reversePost_(), pre_(), post_()
{

    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        if (!marked_[v])
            dfs(g, v);
    }
}


void DepthFirstOrder::dfs(const Graph & g, size_t v)
{
    marked_[v] = true;
    pre_.push(v);

    Node<size_t>* n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
            dfs(g, n->value);
        }
        n = n->next;
    }
    post_.push(v);
    reversePost_.push(v);
}


//--------------------------------------------------------------------------------------------------
// ------- Topological ----------------------------------------------------
//

Topological::Topological(const Graph & g)
    : dfo_(Graph(0, std::make_shared<DirectedGraphStrategy>())), isDAG_(false)
{
    isDAG_ = !Cyclic(g).isCyclic();
    if (isDAG_)
    {
        dfo_ = DepthFirstOrder(g);
    }
}


//--------------------------------------------------------------------------------------------------
// ------- KosarajuSCC ----------------------------------------------------
//

KosarajuSCC::KosarajuSCC(const Graph & g)
    : count_(0), marked_(g.vertexCount(), false), id_(g.vertexCount())
{
    auto r = Graph::reverse(g);
    DepthFirstOrder order(*r);

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

void KosarajuSCC::dfs(const Graph & g, size_t v)
{
    marked_[v] = true;
    id_[v] = count_;

    GNode* n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
            dfs(g, n->value);
        }
        n = n->next;
    }
}


//--------------------------------------------------------------------------------------------------
// ------- TransitiveClosure ----------------------------------------------------
//

TransitiveClosure::TransitiveClosure(const Graph & g)
{
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        vDFS_.push_back(new DeepFirstSearch(g, v));
    }
}

TransitiveClosure::~TransitiveClosure()
{
    for (auto it = vDFS_.begin();  it != vDFS_.end(); ++it)
    {
        delete *it;
    }
}

bool TransitiveClosure::reachable(size_t v, size_t w)
{
    return vDFS_[v]->marked(w);
}


//--------------------------------------------------------------------------------------------------
// ------- BreadthFirstPaths -----------------------------------------------
//

BreadthFirstPaths::BreadthFirstPaths(const Graph & g, size_t s)
    : marked_(g.vertexCount(), false), edgeTo_(g.vertexCount()), s_(s)
{
    bfs(g ,s);
}

void BreadthFirstPaths::bfs(const Graph & g, size_t v)
{
    marked_[v] = true;
    std::queue<size_t> queue;
    queue.push(v);

    while (!queue.empty())
    {
        size_t x = queue.front();
        queue.pop();
        GNode* n = g[x].next;

        while (n)
        {
            if (!marked_[n->value])
            {
//                std::cout << x << " - " << n->value << std::endl;
                edgeTo_[n->value] = x;
                marked_[n->value] = true;
                queue.push(n->value);
            }
            n = n->next;
        }
    }
}

std::string BreadthFirstPaths::pathTo(size_t v) const
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


//--------------------------------------------------------------------------------------------------
// ------- CoupledComponents -------------------------------------------------------
//

CoupledComponents::CoupledComponents(const Graph & g)
    : count_(0),  marked_(g.vertexCount(), false), id_(g.vertexCount())
{
    for (size_t i = 0; i < g.vertexCount(); ++i)
    {
        if(!marked_[i])
        {
            dfs(g, i);
            ++count_;
        }
    }
}

void CoupledComponents::dfs(const Graph &g, size_t v)
{
    marked_[v] = true;
    id_[v] = count_;

    GNode * n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
            dfs(g, n->value);
        }
        n = n->next;
    }
}


//--------------------------------------------------------------------------------------------------
// ------- Cycle --------------------------------------------------------------------
//

Cyclic::Cyclic(const Graph & g) : hasCycle_(false), marked_(g.vertexCount(), false)
{
    for (size_t s = 0; s < g.vertexCount(); ++s)
    {
       if(!marked_[s])
           dfs(g ,s, s);
    }
}

void Cyclic::dfs(const Graph & g, size_t v, size_t u)
{
    marked_[v] = true;

    GNode* n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
            dfs(g, n->value, v);
        }
        else if (n->value != u)
        {
            hasCycle_ = true;
        }
        n = n->next;
    }
}


//--------------------------------------------------------------------------------------------------
// ------- TwoColored ----------------------------------------------------------------
//

TwoColored::TwoColored(const Graph & g)
  : isTwoColors_(true), marked_(g.vertexCount(), false), colors_(g.vertexCount(), false)
{

    for (size_t i = 0; i < g.vertexCount(); ++i)
    {
        if(!marked_[i])
        {
            dfs(g, i);
        }
    }
}

void TwoColored::dfs(const Graph & g, size_t v)
{
    marked_[v] = true;

    GNode* n = g[v].next;
    while (n)
    {
        if (!marked_[n->value])
        {
            colors_[n->value] = !colors_[v];
            dfs(g, n->value);
        }
        else if (colors_[n->value] == colors_[v])
        {
            std::cout << "color: " << n->value << " - " << v << std::endl;
            isTwoColors_ = false;
        }
        n = n->next;
    }
}

//--------------------------------------------------------------------------------------------------
// ------- SymbolGraph --------------------------------------------------------------
//

SymbolGraph::SymbolGraph(std::string fileName) : st_()
{
    std::ifstream file;
    file.open (fileName);
    std::string line;
    std::string delimiter = " ";

    // Generating map
    while (std::getline(file, line))
    {
        size_t pos = 0;
        std::string token;

        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            token = line.substr(0, pos);

            auto it = st_.begin();
            if (st_.find(token) == st_.end())
            {
                st_.insert(it, std::pair<std::string, size_t>(token, st_.size()));
            }
            line.erase(0, pos + delimiter.length());
        }

        auto it = st_.begin();
        if (st_.find(line) == st_.end())
        {
            st_.insert(it, std::pair<std::string, size_t>(line, st_.size()));
        }
    }

    // Generating inverted list
    keys_ = std::vector<std::string>(st_.size());
    for (auto i : st_)
    {
        keys_[i.second] = i.first;
    }

    // Generating graph
    g_ = new Graph(st_.size(), std::make_shared<NonDirectedGraphStrategy>());

    file.clear();
    file.seekg(0, std::ios::beg);

    while (std::getline(file, line))
    {
        size_t pos = 0;
        size_t v = 0;
        std::string vertex;

        if ((pos = line.find(delimiter)) != std::string::npos)
        {
            vertex = line.substr(0, pos);
            line.erase(0, pos + delimiter.length());
        }

        v = st_.find(vertex)->second;
//        std::cout << "vertex - " << vertex;
//        std::cout << " - " << v << std::endl;

        while ((pos = line.find(delimiter)) != std::string::npos)
        {
            std::string token = line.substr(0, pos);
//            std::cout << "vertex - " << vertex << "; token = " << token << std::endl;
            g_->addEdge(v, st_.find(token)->second);
            line.erase(0, pos + delimiter.length());
        }

        // add token after last delimiter
        g_->addEdge(v, st_.find(line)->second);
    }

    std::cout << "map: " << std::endl;
    for (auto i : st_)
    {
        std::cout << "[" << i.first << "] [" << i.second << "]" << std::endl;
    }
    std::cout << std::endl;

    std::cout << "inverted index: " << std::endl;
    for (size_t var = 0; var < st_.size(); ++var)
    {
        std::cout << var << " - " << keys_[var] << std::endl;
    }
    std::cout << std::endl;
}

SymbolGraph::~SymbolGraph()
{
    delete g_;
}

int SymbolGraph::index(std::string key) const
{
    auto it = st_.find(key);
    if (it == st_.end())
    {
        return -1;
    }
    else
        return static_cast<int>(it->second);
}

std::string SymbolGraph::name(size_t index) const
{
    if (index < keys_.size())
    {
        return keys_[index];
    }
    return  std::string();
}

std::string SymbolGraph::lexical(size_t index) const
{
    std::stringstream pathStr;
    if (index < keys_.size())
    {
        pathStr << name(index) << std::endl;

        GNode * n = (*g_)[index].next;
        while (n)
        {
            pathStr << "  " << name(n->value) << std::endl;
            n = n->next;
        }
    }
    return pathStr.str();
}


} // namespace graph
