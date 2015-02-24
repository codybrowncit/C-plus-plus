#include "Student.h"
#include <iostream>
#include <cstring>

Student::Student()
    : mAge(0), mLast(0), mFirst(0), mEmail(0)
{
    this->mSsn[0] = 0;
}

Student::Student(const int age, const char last[], const char first[], const char email[], const char ssn[])
    : mAge(0), mLast(0), mFirst(0), mEmail(0)
{
    this->setAge(age);
    this->setLast(last);
    this->setFirst(first);
    this->setEmail(email);
    this->setSsn(ssn);
}

Student::~Student()
{
    if (this->mLast || this->mFirst || this->mEmail)
    {
        delete [] this->mLast;
        delete [] this->mFirst;
        delete [] this->mEmail;
        this->mLast = 0;
        this->mFirst = 0;
        this->mEmail = 0;
    }
}

Student::Student(const Student &src)
    :mAge(0), mLast(0), mFirst(0), mEmail(0)
{
    *this = src;
}

Student &Student::operator=(const Student &rhs)
{
    this->setAge(rhs.mAge);
    this->setLast(rhs.mLast);
    this->setFirst(rhs.mFirst);
    this->setEmail(rhs.mEmail);
    this->setSsn(rhs.mSsn);
    return *this;
}

bool Student::operator==(const Student &rhs) const
{
    if(this->mSsn && rhs.mSsn)
    {
        int order = std::strcmp(this->mSsn, rhs.mSsn);
        if(order != 0)
        {
            return false;
        }
    }
    else if(this->mSsn || rhs.mSsn)
    {
        return false;
    }
    return true;
}

bool Student::operator!=(const Student &rhs) const
{
    return !(*this == rhs);
}

bool Student::operator<(const Student &rhs) const
{
    if(this->mSsn && rhs.mSsn)
    {
        int order = std::strcmp(this->mSsn, rhs.mSsn);
        if(order < 0)
        {
            return true;
        }
        else if(order > 0)
        {
            return false;
        }
    }
    else if(this->mSsn)
    {
        return false;
    }
    else if(rhs.mSsn)
    {
        return true;
    }
    return false;
}

bool Student::operator<=(const Student &rhs) const
{
    return *this == rhs || *this < rhs;
}

bool Student::operator>(const Student &rhs) const
{
    return rhs < *this;
}

bool Student::operator>=(const Student &rhs) const
{
    return *this == rhs || rhs < *this;
}

int Student::getAge() const
{
    return this->mAge;
}

const char *Student::getLast() const
{
    return this->mLast;
}

const char *Student::getFirst() const
{
    return this->mFirst;
}

const char *Student::getEmail() const
{
    return this->mEmail;
}

const char *Student::getSsn() const
{
    return this->mSsn;
}

bool Student::setAge(const int age)
{
    if (age >= 0 && age <= 150)
    {
        this->mAge = age;
        return true;
    }
    else
    {
        this->mAge = 0;
        return false;
    }
}

bool Student::setLast(const char last[])
{
    if(this->mLast)
    {
        delete [] this->mLast;
        this->mLast = 0;
    }
    if(last == 0)
    {
        this->mLast = 0;
        return true;
    }
    this->mLast = new char [std::strlen(last)+1];
    if(this->mLast)
    {
        std::strcpy(this->mLast, last);
        return true;
    }
    else
    {
        return false;
    }
}

bool Student::setFirst(const char first[])
{
    if(this->mFirst)
    {
        delete [] this->mFirst;
        this->mFirst = 0;
    }
    if(first == 0)
    {
        this->mFirst = 0;
        return true;
    }
    this->mFirst = new char [std::strlen(first)+1];
    if(this->mFirst)
    {
        std::strcpy(this->mFirst, first);
        return true;
    }
    else
    {
        return false;
    }
}

bool Student::setEmail(const char email[])
{
    if(this->mEmail)
    {
        delete [] this->mEmail;
        this->mEmail = 0;
    }
    if(email == 0)
    {
        this->mEmail = 0;
        return true;
    }
    this->mEmail = new char [std::strlen(email)+1];
    if(this->mEmail)
    {
        std::strcpy(this->mEmail, email);
        return true;
    }
    else
    {
        return false;
    }
}

bool Student::setSsn(const char ssn[])
{
    if(std::strlen(ssn) == max_ssn-1)
    {
        std::strcpy(this->mSsn, ssn);
        return true;
    }
    else
    {
        this->mSsn[0] = 0;
        return false;
    }
}

std::ostream &operator<<(std::ostream &os, const Student &rhs)
{
    const char *last = rhs.getLast();
    const char none[5] = "NONE";
    if ( last == 0)
    {
      last = none;
    }
    const char *first = rhs.getFirst();
    if (first == 0)
    {
       first = none;
    }
    const char *email = rhs.getEmail();
    if (email == 0)
    {
      email = none;
    }
    const char *ssn = rhs.getSsn();
    if (ssn[0] == 0)
    {
      ssn = none;
    }
    os << rhs.getAge() << " " << last << " " << first << " " << email << " " << ssn;
    return os;
}

std::istream &operator>>(std::istream &is, Student &rhs)
{
  int  age;
  char *last = new char[max_char];
  char *first = new char[max_char];
  char *email = new char[max_char];
  char ssn[max_ssn];
  is >> age >> last >> first >> email >> ssn;
  if(is)
    {
      rhs.setAge(age);
      char none[5] = "NONE";
      if (std::strcmp (last, none) == 0)
      {
          last = 0;
      }
      rhs.setLast(last);
      if (std::strcmp (first, none) == 0)
      {
          first = 0;
      }
      rhs.setFirst(first);
      if (std::strcmp (email, none) == 0)
      {
          email = 0;
      }
      rhs.setEmail(email);
      rhs.setSsn(ssn);
    }
    delete [] last;
    last = 0;
    delete [] first;
    first = 0;
    delete [] email;
    email = 0;
  return is;
}
