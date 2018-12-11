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
class Node
{
public:
    Node() : value(), next(nullptr), marked_(false) {}
    explicit Node(Value v) : value(v), next(nullptr), marked_(false) {}
    ~Node();

    // Moveable
    Node(Node&&);
    Node& operator= (Node&&);

    // Not copyable
    Node(const Node&)             = delete;
    Node& operator= (const Node&) = delete;

    Value value;
    Node* next;

    Node* last();
    Node* add(Node* n);
    void  clear();
private:
     bool marked_;
};

template<typename Value>
Node<Value>* Node<Value>::last()
{
    marked_ = true;

    Node* n;
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
void Node<Value>::clear()
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
Node<Value>::~Node()
{
    clear();
}

template<typename Value>
Node<Value>::Node(Node && that) : value(0), next(nullptr)
{
    value = that.value;
    next = that.next;

    that.value = -1;
    that.next = nullptr;
}

template<typename Value>
Node<Value>& Node<Value>::operator=(Node&& that)
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
Node<Value>* Node<Value>::add(Node* n)
{
    last()->next = n;
    return this;
}

//--------------------------------------------------------------------------------------------------
#endif // NODE_HPP
//--------------------------------------------------------------------------------------------------


