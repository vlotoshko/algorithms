/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 11-Jun-2018
 */

// -------------------------------------------------------------------------------------------------
#include "GraphAlgorithms.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
// -------------------------------------------------------------------------------------------------

namespace graph
{

//--------------------------------------------------------------------------------------------------
// ------- TransitiveClosure ----------------------------------------------------
//

TransitiveClosure::TransitiveClosure(const Graph & g)
    : marked_(g.vertexCount(), std::vector<bool>(g.vertexCount(), false))
{
    for (size_t v = 0; v < g.vertexCount(); ++v)
    {
        depthFirstSearh<Graph>(g,v, marked_[v]);
        marked_.push_back(marked_[v]);
    }
}

bool TransitiveClosure::reachable(const size_t & v, const size_t & w) const
{
    return marked_[v][w];
}


//--------------------------------------------------------------------------------------------------
// ------- BreadthFirstPaths -----------------------------------------------
//

BreadthFirstPaths::BreadthFirstPaths(const Graph & g, const size_t & s)
    : marked_(g.vertexCount(), false), edgeTo_(g.vertexCount()), s_(s)
{
    bfs(g ,s);
}

void BreadthFirstPaths::bfs(const Graph & g, const size_t & v)
{
    marked_[v] = true;
    std::queue<size_t> queue;
    queue.push(v);

    while (!queue.empty())
    {
        size_t x = queue.front();
        queue.pop();

        auto const & edges = g[x];
        for (auto const & edge : edges)
        {
            auto w = edge.other(edge.either());
            if (!marked_[w])
            {
//                std::cout << x << " - " << w << std::endl;
                edgeTo_[w] = x;
                marked_[w] = true;
                queue.push(w);
            }
        }
    }
}

std::string BreadthFirstPaths::pathTo(const size_t & v) const
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

void CoupledComponents::dfs(const Graph & g, const size_t & v)
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

void TwoColored::dfs(const Graph & g, const size_t & v)
{
    marked_[v] = true;
    for (auto const & edge : g[v])
    {
        auto w = edge.other(v);
        if (!marked_[w])
        {
            colors_[w] = !colors_[v];
            dfs(g, w);
        }
        else if (colors_[w] == colors_[v])
        {
//            std::cout << "color: " << w << " - " << v << std::endl;
            isTwoColors_ = false;
        }
    }
}

//--------------------------------------------------------------------------------------------------
// ------- SymbolGraph --------------------------------------------------------------
//

SymbolGraph::SymbolGraph(const std::string & fileName)
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

            if (st_.find(token) == st_.end())
            {
                st_.insert(std::pair<std::string, size_t>(token, st_.size()));
            }
            line.erase(0, pos + delimiter.length());
        }

        if (st_.find(line) == st_.end())
        {
            st_.insert(std::pair<std::string, size_t>(line, st_.size()));
        }
    }

    // Generating inverted list
    keys_ = std::vector<std::string>(st_.size());
    for (const auto & i : st_)
    {
        keys_[i.second] = i.first;
    }

    // Generating graph
    g_ = new Graph(st_.size());

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

            NonDirectedGraphPolicy<Graph>::addEdge(*g_, v, st_.find(token)->second);
            line.erase(0, pos + delimiter.length());
        }

        // add token after last delimiter
        NonDirectedGraphPolicy<Graph>::addEdge(*g_, v, st_.find(line)->second);
    }

    std::cout << "map: " << std::endl;
    for (const auto & i : st_)
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

SymbolGraph::SymbolGraph(const size_t & size)  : keys_(size), g_(new Graph(size)) {}

SymbolGraph::~SymbolGraph()
{
    delete g_;
}

bool SymbolGraph::addEdge(const std::string & v, const std::string & w)
{
    if (st_.size() == keys_.size())
    {
        return false;
    }
    auto add = [this](const std::string s)
    {
        if (st_.find(s) == st_.end())
        {
            auto index = st_.size();
            st_.insert(std::pair<std::string, size_t>(s, index));
            keys_[index] = s;
        }
    };

    add(v);
    add(w);

    NonDirectedGraphPolicy<Graph>::addEdge(*g_, st_.find(v)->second, st_.find(w)->second);
    return true;
}

bool SymbolGraph::contains(const std::string & key) const
{
    return st_.find(key) != st_.end();
}

int SymbolGraph::index(const std::string & key) const
{
    auto it = st_.find(key);
    if (it == st_.end())
    {
        return -1;
    }
    return static_cast<int>(it->second);
}

std::string SymbolGraph::name(const size_t & index) const
{
    if (index < keys_.size())
    {
        return keys_[index];
    }
    return std::string{};
}

std::string SymbolGraph::lexical(const size_t & index) const
{
    std::stringstream pathStr;
    if (index < keys_.size())
    {
        pathStr << name(index) << std::endl;

        auto const & edges = (*g_)[index];
        for (auto const & edge : edges)
        {
            pathStr << "  " << name(edge.other(index)) << std::endl;
        }
    }
    return pathStr.str();
}


} // namespace graph
