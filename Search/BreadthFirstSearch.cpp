//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   11-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "BreadthFirstSearch.hpp"

#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
//--------------------------------------------------------------------------------------------------

namespace graph
{
using GNode = Graph::GNode;

//--------------------------------------------------------------------------------------------------
// ------- BreadthFirstPaths -----------------------------------------------
//

BreadthFirstPaths::BreadthFirstPaths(const Graph & g, size_t s)
    : marked_(g.vertexes(), false), edgeTo_(g.vertexes()), s_(s)
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
        GNode* n = g.adj(x)->next;

        while(n)
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
    if(!hasPathTo(v))
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
    : count_(0),  marked_(g.vertexes(), false), id_(g.vertexes())
{
    for (size_t i = 0; i < g.vertexes(); ++i)
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

    GNode * n = g.adj(v)->next;
    while(n)
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

Cyclic::Cyclic(const Graph & g) : hasCycle_(false), marked_(g.vertexes(), false)
{
    for (size_t s = 0; s < g.vertexes(); ++s)
    {
       if(!marked_[s])
           dfs(g ,s, s);
    }
}

void Cyclic::dfs(const Graph & g, size_t v, size_t u)
{
    marked_[v] = true;

    GNode* n = g.adj(v)->next;
    while(n)
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
  : isTwoColors_(true), marked_(g.vertexes(), false), colors_(g.vertexes(), false)
{

    for (size_t i = 0; i < g.vertexes(); ++i)
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

    GNode* n = g.adj(v)->next;
    while(n)
    {
        if (!marked_[n->value])
        {
            colors_[n->value] = !colors_[v];
            dfs(g, n->value);
        }
        else if(colors_[n->value] == colors_[v])
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

int SymbolGraph::index(std::string key)
{
    auto it = st_.find(key);
    if (it == st_.end())
    {
        return -1;
    }
    else
        return static_cast<int>(it->second);
}


} // namespace graph
