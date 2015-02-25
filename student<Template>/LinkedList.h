#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_
#include "Student.h"

template <class Type>
class Node
{
    public:
        Type data;
        Node *next;
};

template <class Type>
class LinkedList
{
    public:
        LinkedList();
        LinkedList(const LinkedList &src);
        ~LinkedList();
        LinkedList &operator=(const LinkedList &rhs);
        bool Exists(const Type &key) const;
        bool Insert(const Type &value);
        bool Delete(const Type &key);
        Type Retrieve(const Type &key) const;
        void Display(std::ostream &os) const;
    private:
        Node<Type> *top;
        void CopyFromLink(const Node<Type> *link_in);
};

template <class Type>
LinkedList<Type>::LinkedList()
    : top(0)
{
}

template <class Type>
LinkedList<Type>::LinkedList(const LinkedList<Type> &src)
    : top(0)
{
    *this = src;
}

template <class Type>
LinkedList<Type>::~LinkedList()
{
    while (this->top != 0)
    {
        if(this->top)
        {
            Node<Type> *curr = this->top;
            this->top = this->top->next;
            delete curr;
        }
    }
}

template <class Type>
LinkedList<Type> &LinkedList<Type>::operator=(const LinkedList<Type> &rhs)
{
    while (this->top != 0)
    {
        if(this->top)
        {
            Node<Type> *curr = this->top;
            this->top = this->top->next;
            delete curr;
        }
    }
    this->CopyFromLink(rhs.top);
    return *this;
}

template <class Type>
bool LinkedList<Type>::Exists(const Type &key) const
{
    Node<Type> *curr;
    for (curr=top; curr!=0; curr=curr->next)
  {
    if (curr->data == key)
      return true;
  }
  return false;
}

template <class Type>
bool LinkedList<Type>::Insert(const Type &value)
{
    if (!Exists(value))
    {
        Node<Type> *new_node = new Node<Type>;
        new_node->next = this->top;
        new_node->data = value;
        this->top = new_node;
        return true;
    }
    return false;
}

template <class Type>
bool LinkedList<Type>::Delete(const Type &key)
{
    Node<Type> *curr;
    Node<Type> *prev;
    prev = 0;
    for (curr=top; curr!=0; curr=curr->next)
    {
        if (curr->data == key)
        {
            if (!prev)
            {
                this->top = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
            return true;
        }
        prev = curr;
    }
    return false;
}

template <class Type>
Type LinkedList<Type>::Retrieve(const Type &key) const
{
    Node<Type> *curr;
    for (curr=top; curr!=0; curr=curr->next)
    {
        if (curr->data == key)
        {
            return curr->data;
        }

    }
    return Type();
}

template <class Type>
void LinkedList<Type>::CopyFromLink(const Node<Type> *link_in)
{
    if(link_in)
    {
        this->CopyFromLink(link_in->next);
        this->Insert(link_in->data);
    }
}

template <class Type>
void LinkedList<Type>::Display(std::ostream &os) const
{
    Node<Type> *curr;
    for(curr = this->top; curr; curr = curr->next)
    {
        if (curr->next)
	    {
            os << curr->data << "\n";
	    }
        else
	    {
	        os << curr->data;
	    }
    }
}

template <class Type>
std::ostream &operator<<(std::ostream &os, const LinkedList<Type> &rhs)
{
    rhs.Display(os);
    return os;
}

template <class Type>
std::istream &operator>>(std::istream &is, LinkedList<Type> &rhs)
{
    Type t;
    while (is >> t)
    {
        rhs.Insert(t);
    }
    return is;
}

#endif
