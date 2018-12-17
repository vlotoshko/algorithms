//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   04-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef EDGE_HPP
#define EDGE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <cmath>
#include <cstddef>
//--------------------------------------------------------------------------------------------------

namespace graph
{

class EdgeNonWeighted
{
public:
    EdgeNonWeighted(size_t v = 0, size_t w = 0) : v_(v), w_(w) {}
    EdgeNonWeighted(const EdgeNonWeighted & other) : v_(other.v_), w_(other.w_) {}

    size_t either() const { return v_; }
    size_t other(size_t v) const
    {
        if (v == v_) return w_;
        else if (v == w_) return v_;
        else throw("Invalid edge");
    }
    bool operator== (const EdgeNonWeighted& e) const { return  v_ == e.v_ && w_ == e.w_; }
    bool operator!= (const EdgeNonWeighted& e) const { return !(*this == e); }
private:
    size_t v_;
    size_t w_;
};

class EdgeWeighted
{
public:
    EdgeWeighted(size_t v = 0, size_t w = 0, double weight = 0) : v_(v), w_(w), weight_(weight) {}
    EdgeWeighted(const EdgeWeighted & other) : v_(other.v_), w_(other.w_), weight_(other.weight_) {}

    double weight() const { return weight_; }
    size_t either() const { return v_; }
    size_t other(size_t v) const
    {
        if (v == v_) return w_;
        else if (v == w_) return v_;
        else throw("Invalid edge");
    }
    bool operator< (const EdgeWeighted& e) const { return weight_ < e.weight_; }
    bool operator> (const EdgeWeighted& e) const { return weight_ > e.weight_; }
    bool operator== (const EdgeWeighted& e) const
    {
        return  v_ == e.v_ && w_ == e.w_ && // TODO: check double comparsion
                std::abs(weight_ - e.weight_) < 0.0001;

    }
    bool operator!= (const EdgeWeighted& e) const { return !(*this == e); }
private:
    size_t v_;
    size_t w_;
    double weight_;
};

}

//--------------------------------------------------------------------------------------------------
#endif // EDGE_HPP
//--------------------------------------------------------------------------------------------------


