/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 04-Jul-2018
 */

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

/**
 * @class EdgeNonWeighted
 * @brief The EdgeNonWeighted class
 */
class EdgeNonWeighted
{
public:
    /**
     * @brief The EdgeNonWeighted constructor creates edge from one vertex to other.
     * @param[in] v vertex 'from'
     * @param[in] w vertex 'to'
     */
    EdgeNonWeighted(size_t v = 0, size_t w = 0) : v_(v), w_(w) {}

    /// Default copy constructor
    EdgeNonWeighted(const EdgeNonWeighted & other) = default;

    /// Default assignment operator
    EdgeNonWeighted& operator= (const EdgeNonWeighted &) = default;

    /// @return vertex 'from' of the edge.
    size_t either() const { return v_; }

    /**
     * @brief retruns other vertex in accordance to v or throws exception.
     * @param[in] v vertex of the edge
     * @return other vertex in accordance to v.
     */
    size_t other(size_t v) const
    {
        if (v == v_) return w_;
        else if (v == w_) return v_;
        else throw("Invalid edge");
    }

    /**
     * @brief Compares two edges.
     * @param[in] e edge to compare
     * @return true if edges are equal.
     */
    bool operator== (const EdgeNonWeighted & e) const { return  v_ == e.v_ && w_ == e.w_; }

    /**
     * @brief Compares two edges.
     * @param[in] e edge to compare
     * @return true if edges are different.
     */
    bool operator!= (const EdgeNonWeighted & e) const { return !(*this == e); }
private:
    size_t v_;
    size_t w_;
};

/**
 * @class EdgeWeighted
 * @brief The EdgeWeighted class
 */
class EdgeWeighted
{
public:
    /**
     * @brief The EdgeWeighted constructor creates weigthed edge from one vertex to other.
     * @param[in] v vertex 'from'
     * @param[in] w vertex 'to'
     * @param[in] weight weight of the edge.
     */
    EdgeWeighted(size_t v = 0, size_t w = 0, double weight = 0) : v_(v), w_(w), weight_(weight) {}

    /// Default copy constructor
    EdgeWeighted(const EdgeWeighted & other) = default;

    /// Default assignment operator
    EdgeWeighted& operator= (const EdgeWeighted &) = default;

    /// @return weight of the edge.
    double weight() const { return weight_; }

    /// @return vertex 'from' of the edge.
    size_t either() const { return v_; }

    /**
     * @brief retruns other vertex in accordance to v or throws exception.
     * @param[in] v vertex of the edge
     * @return other vertex in accordance to v.
     */
    size_t other(size_t v) const
    {
        if (v == v_) return w_;
        else if (v == w_) return v_;
        else throw("Invalid edge");
    }
    /**
     * @brief Compares two edges.
     * @param[in] e edge to compare
     * @return true if weight of given edge is less the weight of e.
     */
    bool operator< (const EdgeWeighted& e) const { return weight_ < e.weight_; }

    /**
     * @brief Compares two edges.
     * @param[in] e edge to compare
     * @return true if weight of given edge is greater the weight of e.
     */
    bool operator> (const EdgeWeighted& e) const { return weight_ > e.weight_; }

    /**
     * @brief Compares two edges.
     * @param[in] e edge to compare
     * @return true if edges are equal.
     */
    bool operator== (const EdgeWeighted& e) const
    {
        return  v_ == e.v_ && w_ == e.w_ && std::abs(weight_ - e.weight_) < 0.0001;
    }

    /**
     * @brief Compares two edges.
     * @param[in] e edge to compare
     * @return true if edges are different.
     */
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


