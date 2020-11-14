/**
 * @author Volodymyr Lotoshko (vlotoshko@gmail.com)
 * @date 01-Nov-2020
 */

//--------------------------------------------------------------------------------------------------
#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#include <algorithm>
#include <list>
#include <vector>
//--------------------------------------------------------------------------------------------------

namespace hash
{

/**
 * @class HashTableChaining
 * @brief The HashTableChaining class is the hash table with the chaining method collision resolve
 * @tparam Key key type of the table
 * @tparam Value value type of the table
 */
template<typename Key, typename Value>
class HashTableChaining
{
public:
    using HashTable = std::vector<std::list<std::pair<Key, Value>>>;

    /// @brief The HashTableChaining constructor/destructor.
    explicit HashTableChaining(size_t size) : hashTable_(size) {}
    ~HashTableChaining() {}

    /// @brief Puts new value into the table.
    void put(Key k, Value v);

    /// @brief Gets value from the table.
    Value get(Key k) const;

    /// @brief Deletes item with the given key.
    void del(Key k);

private:
    /// @brief hashTable_ container that contains items
    HashTable hashTable_;

    /// @brief Simple modular hash-fucntion
    size_t hash(Key k) const { return k % hashTable_.size(); }

    /// @brief Comparator is used to find item by key
    class Comparator {
    public:
        explicit Comparator(Key k) : k_(k){}
        bool operator()(const std::pair<Key, Value> & pair) const {return k_ == pair.first; }
    private:
        Key k_;
    };
};

template<typename Key, typename Value>
void HashTableChaining<Key, Value>::put(Key k, Value v)
{
    auto & chain = hashTable_[hash(k)];
    auto it = std::find_if(chain.begin(), chain.end(), Comparator{k});
    if (it != chain.end())
    {
        (*it).second = v;
    }
    else
    {
        chain.push_back(std::pair<Key, Value>{k, v});
    }
}

template<typename Key, typename Value>
Value HashTableChaining<Key, Value>::get(Key k) const
{
    const auto & chain = hashTable_[hash(k)];
    auto it = std::find_if(chain.begin(), chain.end(), Comparator{k});
    if (it != chain.end())
    {
        return (*it).second;
    }
    return Value{};
}

template<typename Key, typename Value>
void HashTableChaining<Key, Value>::del(Key k)
{
    auto & chain = hashTable_[hash(k)];
    chain.erase(std::remove_if(chain.begin(), chain.end(), Comparator{k}), chain.end());
}

} // namespace hash

//--------------------------------------------------------------------------------------------------
#endif // HASH_TABLE_HPP
//--------------------------------------------------------------------------------------------------
