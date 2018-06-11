//--------------------------------------------------------------------------------------------------
// Author: Volodymyr Lotoshko (vlotoshko@gmail.com)
// skype:  vlotoshko
// Date:   10-Jun-2018
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
#ifndef NODE_HPP
#define NODE_HPP
//--------------------------------------------------------------------------------------------------


template<typename Value>
class Node {
public:
    Node() : value(), next(nullptr), marked_(false) {}
    explicit Node(Value v) : value(v), next(nullptr), marked_(false) {}
    ~Node();
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
        }

    }
    marked_ = false;
}

template<typename Value>
Node<Value>::~Node<Value>()
{
    clear();
}

template<typename Value>
Node<Value>* Node<Value>::add(Node *n)
{
    last()->next = n;
    return this;
}

//--------------------------------------------------------------------------------------------------
#endif // NODE_HPP
//--------------------------------------------------------------------------------------------------

