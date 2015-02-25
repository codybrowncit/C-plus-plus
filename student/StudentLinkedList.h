#ifndef _STUDENT_LINKED_LIST_H_
#define _STUDENT_LINKED_LIST_H_
#include "Student.h"

class Node
{
    public:
        Student data;
        Node *next;
};

class StudentLinkedList
{
    public:
        StudentLinkedList();
        StudentLinkedList(const StudentLinkedList &src);
        ~StudentLinkedList();
        StudentLinkedList &operator=(const StudentLinkedList &rhs);
        bool Exists(const Student &key) const;
        bool Insert(const Student &value);
        bool Delete(const Student &key);
        Student Retrieve(const Student &key) const;
        void Display(std::ostream &os) const;
    private:
        Node *top;
        void CopyFromLink(const Node *link_in);
};
std::ostream &operator<<(std::ostream &os, const StudentLinkedList &rhs);
std::istream &operator>>(std::istream &is, StudentLinkedList &rhs);
#endif
