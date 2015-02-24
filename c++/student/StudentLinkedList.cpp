#include "StudentLinkedList.h"

StudentLinkedList::StudentLinkedList()
    : top(0)
{
}

StudentLinkedList::StudentLinkedList(const StudentLinkedList &src)
    : top(0)
{
    *this = src;
}

StudentLinkedList::~StudentLinkedList()
{
    while (this->top != 0)
    {
        if(this->top)
        {
            Node *curr = this->top;
            this->top = this->top->next;
            delete curr;
        }
    }
}

StudentLinkedList &StudentLinkedList::operator=(const StudentLinkedList &rhs)
{
    while (this->top != 0)
    {
        if(this->top)
        {
            Node *curr = this->top;
            this->top = this->top->next;
            delete curr;
        }
    }
    this->CopyFromLink(rhs.top);
    return *this;
}

bool StudentLinkedList::Exists(const Student &key) const
{
    Node *curr;
    for (curr=top; curr!=0; curr=curr->next)
  {
    if (curr->data == key)
      return true;
  }
  return false;
}

bool StudentLinkedList::Insert(const Student &value)
{
    if (!Exists(value))
    {
        Node *new_node = new Node;
        new_node->next = this->top;
        new_node->data = value;
        this->top = new_node;
        return true;
    }
    return false;
}

bool StudentLinkedList::Delete(const Student &key)
{
    Node *curr;
    Node *prev;
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

Student StudentLinkedList::Retrieve(const Student &key) const
{
    Node *curr;
    for (curr=top; curr!=0; curr=curr->next)
    {
        if (curr->data == key)
        {
            return curr->data;
        }

    }
    Student t;
    return t;
}

void StudentLinkedList::CopyFromLink(const Node *link_in)
{
    if(link_in)
    {
        this->CopyFromLink(link_in->next);
        this->Insert(link_in->data);
    }
}

void StudentLinkedList::Display(std::ostream &os) const
{
    Node *curr;
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

std::ostream &operator<<(std::ostream &os, const StudentLinkedList &rhs)
{
    rhs.Display(os);
    return os;
}

std::istream &operator>>(std::istream &is, StudentLinkedList &rhs)
{
    Student student = Student();
    while (is >> student)
    {
        rhs.Insert(student);
    }
    return is;
}
