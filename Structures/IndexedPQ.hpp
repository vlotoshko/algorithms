//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   17-Jul-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef INDEXED_PQ_HPP
#define INDEXED_PQ_HPP
//--------------------------------------------------------------------------------------------------
#include <vector>
#include <algorithm>
//--------------------------------------------------------------------------------------------------

namespace data_structs
{

// ------------------------------------------------------------------------------------------
// Structure that holds heap's pointer to the T and hold its index in the array
// Incapsulates compartor to compare two T elements, stored in the heap
//
template <typename T, typename Compare>
struct IndexedItem
{
    typedef T            value_type;
    typedef T *          pointer;
    typedef const T *    const_pointer;
    typedef T &          reference;
    typedef const T &    const_reference;
    typedef size_t       size_type;

    size_type  index;
    pointer    element;
    static bool cmp(const IndexedItem & lsh, const IndexedItem & rsh);
private:
    static Compare comp_;
};

template<typename T, typename Compare>
Compare IndexedItem<T, Compare>::comp_ = Compare();

template <typename T, typename Compare>
bool IndexedItem<T, Compare>::cmp(const IndexedItem & lsh, const IndexedItem & rsh)
{
    return comp_(*lsh.element, *rsh.element);
}


// ------------------------------------------------------------------------------------------
// Indexed priority queue. Holds vector of pointers to T to get T by index
// Holds container of Sequence type to store sorted elemets
// Indexed priority queue has fixed size(capasity) passed into the constructor
// Does not check any size overflow or emty
//
template<typename T, typename Compare  = std::less<T>,
         typename IndexedItem = IndexedItem<T, Compare>,
         typename Sequence = std::vector<IndexedItem>>
class IndexedPriorityQueue
{
public:
    typedef typename IndexedItem::value_type                value_type;
    typedef typename IndexedItem::pointer                   pointer;
    typedef typename IndexedItem::reference                 reference;
    typedef typename IndexedItem::const_reference           const_reference;
    typedef typename IndexedItem::size_type                 size_type;
    typedef          IndexedItem                            container_type;

public:
    IndexedPriorityQueue(size_t size) : byIndex_(size, nullptr) {}
    ~IndexedPriorityQueue()
    {
        for(auto & item : byOrder_)
        {
            delete item.element;
        }
    }

    const_reference top() const { return *byOrder_.front().element; }
    const_reference operator[] (size_t i) const { return *byIndex_[i]; }
    bool containes(size_t v) const { return byIndex_[v] != nullptr; }

    size_type capasity() const { return byIndex_.size(); }
    size_type size()     const { return byOrder_.size(); }
    bool      empty()    const { return byOrder_.empty(); }

    // Removes top element and returns its index
    size_t pop()
    {
        size_t index = byOrder_.front().index;
        std::pop_heap(byOrder_.begin(), byOrder_.end(), IndexedItem::cmp);
        byOrder_.pop_back();
        delete byIndex_[index];
        byIndex_[index] = nullptr;

        return index;
    }

    bool push(size_type v, value_type t)
    {
        bool newElement = !containes(v);
        if (newElement)
        {
            pointer item = new value_type(t);
            byIndex_[v] = item;
            byOrder_.push_back({v, item});
            std::push_heap(byOrder_.begin(), byOrder_.end(), IndexedItem::cmp);
        }
        else
        {
            auto item = byIndex_[v];
            *item = t;
            std::make_heap(byOrder_.begin(), byOrder_.end(), IndexedItem::cmp);
        }
        return newElement;
    }
private:
    std::vector<pointer> byIndex_;
    Sequence byOrder_;
};


} // data_structs

//--------------------------------------------------------------------------------------------------
#endif // INDEXED_PQ_HPP
//--------------------------------------------------------------------------------------------------


