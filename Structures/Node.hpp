//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef NODE_HPP
#define NODE_HPP
//--------------------------------------------------------------------------------------------------

#include <iostream>

template <typename T>
struct ObjectCounter
{
    ObjectCounter()  { std::cout << "{=} <<< exists " << ++count << std::endl; }
    ~ObjectCounter() { std::cout << "{=} >>> left "   << --count << std::endl; }
    static size_t count;
};

template <typename T>
size_t ObjectCounter<T>::count = 0;

template<typename Value>
//class Node : public ObjectCounter<Node<Value>>
class Node11
{
public:
    Node11() : value(), next(nullptr), marked_(false) {}
    explicit Node11(Value v) : value(v), next(nullptr), marked_(false) {}
    ~Node11();

    // Moveable
    Node11(Node11&&);
    Node11& operator= (Node11&&);

    // Not copyable
    Node11(const Node11&)             = delete;
    Node11& operator= (const Node11&) = delete;

    Value value;
    Node11* next;

    Node11* last();
    Node11* add(Node11* n);
    void  clear();
private:
     bool marked_;
};

template<typename Value>
Node11<Value>* Node11<Value>::last()
{
    marked_ = true;

    Node11* n;
    if (next != nullptr && !next->marked_)
    {
        n = next->last();
    }
    else
    {
        n = this;
    }

    marked_ = false;
    return n;
}

template<typename Value>
void Node11<Value>::clear()
{
    marked_ = true;
    if (next != nullptr)
    {
        if (!next->marked_)
        {
            next->clear();
            delete next;
            next = nullptr;
        }

    }
    marked_ = false;
}

template<typename Value>
Node11<Value>::~Node11()
{
    clear();
}

template<typename Value>
Node11<Value>::Node11(Node11 && that) : value(0), next(nullptr)
{
    value = that.value;
    next = that.next;

    that.value = -1;
    that.next = nullptr;
}

template<typename Value>
Node11<Value>& Node11<Value>::operator=(Node11&& that)
{
    if (this != &that)
    {
        clear();

        value = that.value;
        next = that.next;

        that.value = -1;
        that.next = nullptr;
    }

    return *this;
}

template<typename Value>
Node11<Value>* Node11<Value>::add(Node11* n)
{
    last()->next = n;
    return this;
}

//--------------------------------------------------------------------------------------------------
#endif // NODE_HPP
//--------------------------------------------------------------------------------------------------


