//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include "Graph.hpp"

#include <fstream>
#include <stack>
#include <queue>

//--------------------------------------------------------------------------------------------------


Graph::Graph(size_t v) : v_(v), e_(0), adj_(new Node<int>[v])
{
    for (int i = 0; i < static_cast<int>(v_); ++i)
    {
        adj_[i].value = i;
    }
}

Graph::Graph(std::string fileName) : e_(0)
{
    std::ifstream file;
    file.open (fileName);
    file >> v_;

    adj_ = new Node<int>[v_];
    for (int i = 0; i < static_cast<int>(v_); ++i)
    {
        adj_[i].value = i;
    }

    int v;
    int w;
    while (file >> v && file >> w)
    {
        addEdge(v, w);
    }
}

Graph::~Graph()
{
    delete[] adj_;
}

void Graph::addEdge(int v, int w)
{
    adj_[v].add(new Node<int>(w));
    adj_[w].add(new Node<int>(v));
    ++e_;
}

Node<int>* Graph::adj(size_t v)
{
    return &adj_[v];
}

void Graph::toString()
{
    std::string s;

    std::cout << "vertex: " << v_ << "; edges: " << e_ << std::endl;
    for (size_t var = 0; var < vortexes(); ++var)
    {
        std::cout << adj(var)->value << ": ";
        Node<int>* n = adj(var)->next;
        while (n) {
            std::cout << n->value << " ";
            n = n->next;
        }
        std::cout << std::endl;
    }
}


size_t Graph::degree(Graph *g, size_t v)
{
    size_t degree = 0;
    Node<int> * n = g->adj(v);
    while(n->next)
    {
        ++degree;
        n = n->next;
    }
    return degree;
}

size_t Graph::maxDegree(Graph *g)
{
    size_t max = 0;
    for (size_t i = 0; i < g->vortexes(); ++i)
    {
        size_t d = degree(g, i);
        if (d > max)
            max = d;
    }
    return max;
}

size_t Graph::avgDegree(Graph *g)
{
    return 2 * g->edges() / g->vortexes();
}

int Graph::selfLoops(Graph *g)
{
    int count = 0;
    for (size_t v = 0; v < g->vortexes(); ++v)
    {
        Node<int>* n = g->adj(v)->next;
        while(n)
        {
            if (n->value == v)
                ++count;
            n = n->next;
        }
    }
    return count / 2;
}
