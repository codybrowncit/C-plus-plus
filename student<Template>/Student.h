#ifndef _STUDENT_H_
#define _STUDENT_H_
#include <iostream>
const int max_char = 64;
const int max_ssn = 12;
class Student
{
    public:
        Student();
        Student(const int age, const char last[], const char first[], const char email[], const char ssn[]);
        Student(const Student &src);
        ~Student();
        Student &operator=(const Student &rhs);
        int getAge() const;
        const char *getLast() const;
        const char *getFirst() const;
        const char *getEmail() const;
        const char *getSsn() const;
        bool setAge(const int age);
        bool setLast(const char last[]);
        bool setFirst(const char first[]);
        bool setEmail(const char email[]);
        bool setSsn(const char ssn[]);
        bool operator==(const Student &rhs) const;
        bool operator!=(const Student &rhs) const;
        bool operator<(const Student &rhs) const;
        bool operator<=(const Student &rhs) const;
        bool operator>(const Student &rhs) const;
        bool operator>=(const Student &rhs) const;
    private:
        int mAge;
        char *mLast;
        char *mFirst;
        char *mEmail;
        char mSsn[max_ssn];
};
std::ostream &operator<<(std::ostream &os, const Student &rhs);
std::istream &operator>>(std::istream &is, Student &rhs);

#endif
