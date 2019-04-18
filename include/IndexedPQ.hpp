/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 17-Jul-2018
 */

//--------------------------------------------------------------------------------------------------
#ifndef INDEXED_PQ_HPP
#define INDEXED_PQ_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <vector>
#include <algorithm>
#include <functional>
#include <map>

//--------------------------------------------------------------------------------------------------

namespace data_structs
{


/**
 * @struct IndexedItem
 * @brief The IndexedItem template class holds heap's pointer to the T and hold its
 * index in the array.
 * Incapsulates compartor to compare two T elements, stored in the heap.
 * @tparam T type of the element
 * @tparam Compare type of the comparator
 *
 */
template <typename T, typename Compare>
struct IndexedItem
{
    /// @brief value type
    typedef T            value_type;
    /// @brief ponter type
    typedef T *          pointer;
    /// @brief const pointer type
    typedef const T *    const_pointer;
    /// @brief reference type
    typedef T &          reference;
    /// @brief const reference type
    typedef const T &    const_reference;
    /// @brief size type
    typedef size_t       size_type;

    /// @brief index in the array
    size_type index;

    /// @brief pointer to element in the heap
    pointer element;

    /**
     * @brief Compares two elements using comparator.
     * @param[in] lsh left-side-hand element
     * @param[in] rsh right-side-hand element
     * @return true if comparator returns true.
     */
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


/**
 * @class IndexedPriorityQueue
 * @brief The IndexedPriorityQueue template class is indexed priority queue.
 * Holds container of Sequence type to store sorted elemets.
 * Indexed priority queue has fixed size(capasity) passed into the constructor.
 * Does not check any size overflow or empty.
 * @tparam T type of element
 * @tparam IndexedItem type of indexed element
 * @tparam Sequence type of container
 */
template<typename T, typename Compare  = std::less<T>,
         typename IndexedItem = IndexedItem<T, Compare>,
         typename Sequence = std::vector<IndexedItem>>
class IndexedPriorityQueue
{
public:
    /// @brief value type
    typedef typename IndexedItem::value_type                value_type;
    /// @brief pointer type
    typedef typename IndexedItem::pointer                   pointer;
    /// @brief reference type
    typedef typename IndexedItem::reference                 reference;
    /// @brief const reference type
    typedef typename IndexedItem::const_reference           const_reference;
    /// @brief size type
    typedef typename IndexedItem::size_type                 size_type;
    /// @brief container type
    typedef          IndexedItem                            container_type;

public:
    /**
     * @brief The IndexedPriorityQueue constructor explores all graph and calculates
     * shortest paths, using topolocigal sort.
     * @param[in] size size of the queue
     */
    explicit IndexedPriorityQueue(size_t size) : byIndex_(size, nullptr) {}
    ~IndexedPriorityQueue()
    {
        for(auto & item : byOrder_)
        {
            delete item.element;
        }
    }

    /**
     * @brief Gets top element.
     * @return top element.
     */
    const_reference top() const { return *byOrder_.front().element; }

    /**
     * @brief Gets element by index
     * @param[in] i index
     * @return elememt by index.
     */
    const_reference operator[] (size_t i) const { return *byIndex_[i]; }

    /**
     * @brief Defines whether queue containes element with the given index.
     * @param[in] v index
     * @return true if queue containes element with the given index.
     */
    bool containes(size_t v) const { return byIndex_[v] != nullptr; }

    /// @return capasity of the queue.
    size_type capasity() const { return byIndex_.size(); }

    /// @return size of the queue.
    size_type size() const { return byOrder_.size(); }

    /// @return true if queue is empty.
    bool empty() const { return byOrder_.empty(); }

    /**
     * @brief Removes top element.
     * @return returns index of the removed element.
     */
    size_t pop()
    {
        size_t index = byOrder_.front().index;
        std::pop_heap(byOrder_.begin(), byOrder_.end(), IndexedItem::cmp);
        byOrder_.pop_back();
        delete byIndex_[index];
        byIndex_[index] = nullptr;

        return index;
    }

    /**
     * @brief Adds or updates element in the queue.
     * @param[in] i index of the element
     * @param[in] v value of the element
     * @return true if new element was added.
     */
    bool push(size_type i, value_type v)
    {
        bool newElement = !containes(i);
        if (newElement)
        {
            pointer item = new value_type(v);
            byIndex_[i] = item;
            byOrder_.push_back({i, item});
            std::push_heap(byOrder_.begin(), byOrder_.end(), IndexedItem::cmp);
        }
        else
        {
            auto item = byIndex_[i];
            *item = v;
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


