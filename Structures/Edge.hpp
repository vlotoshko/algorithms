//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   04-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef EDGE_HPP
#define EDGE_HPP
//--------------------------------------------------------------------------------------------------
#include <cstddef>
//--------------------------------------------------------------------------------------------------

namespace graph
{

class Edge
{
public:
    Edge(size_t v = 0, size_t w = 0, double weight = 0) : v_(v), w_(w), weight_(weight) {}
    Edge(const Edge & other) : v_(other.v_), w_(other.w_), weight_(other.weight_) {}

    double weight() const { return weight_; }
    size_t either() const { return v_; }
    size_t other(size_t v) const
    {
        if (v == v_) return w_;
        else if (v == w_) return v_;
        else throw("Invalid edge");
    }
    bool operator< (const Edge& e) const { return weight_ < e.weight_; }
    bool operator> (const Edge& e) const { return weight_ > e.weight_; }
private:
    size_t v_;
    size_t w_;
    double weight_;
};

}

//--------------------------------------------------------------------------------------------------
#endif // EDGE_HPP
//--------------------------------------------------------------------------------------------------


