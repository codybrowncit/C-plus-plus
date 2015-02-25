#include "StudentLinkedList.h"
#include "StudentLinkedList.h" // included twice to test #ifndef
#include "gtest/gtest.h"
#include <cstring>
#include <sstream>
#include <string>

// default constructor
TEST(StudentLinkedList, CONSTRUCTOR_1) {
  const StudentLinkedList lst_a;
}

// copy constructor
TEST(StudentLinkedList, COPY_CONSTRUCTOR_1) {
  const StudentLinkedList lst_a;
  const StudentLinkedList lst_b(lst_a);
}

// assignment operator
TEST(StudentLinkedList, ASSIGNMENT_OPERATOR_1) {
  const StudentLinkedList lst_a;
  StudentLinkedList lst_b;
  lst_b = lst_a;
}

// positive insert
TEST(StudentLinkedList, INSERT_1) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Insert(s), true);
}

// negative exists
TEST(StudentLinkedList, EXISTS_1) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Exists(s), false);
}

// positive exists
TEST(StudentLinkedList, EXISTS_2) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
}

// negative insert
TEST(StudentLinkedList, INSERT_2) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Insert(s), false);
}

// negative delete
TEST(StudentLinkedList, DELETE_1) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Delete(s), false);
}

// positive delete
TEST(StudentLinkedList, DELETE_2) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
  EXPECT_EQ(lst.Delete(s), true);
  EXPECT_EQ(lst.Exists(s), false);
  EXPECT_EQ(lst.Delete(s), false);
}

// positive retrieve
TEST(StudentLinkedList, RETRIEVE_1) {
  StudentLinkedList lst;
  Student s,t;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999";
  ss >> s;

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
  t = lst.Retrieve(s);
  EXPECT_EQ(t == s, true);
}

// negative retrieve
TEST(StudentLinkedList, RETRIEVE_2) {
  StudentLinkedList lst;
  Student s,t,d;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999";
  ss >> s;

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);

  ss >> s;

  EXPECT_EQ(lst.Exists(s), false);
  t = lst.Retrieve(s);
  EXPECT_EQ(t == d, true);
}


// copy constructor
TEST(StudentLinkedList, COPY_CONSTRUCTOR_2) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "70 Doe Jane chevy.chase@hollywood.com 999-55-9999" << std::endl;

  while(ss >> s)
    {
      if(!lst.Exists(s))
        {
          EXPECT_EQ(lst.Insert(s), true);
        }
      else
        {
          EXPECT_EQ(lst.Insert(s), false);
        }
      EXPECT_EQ(lst.Exists(s), true);
    }

  StudentLinkedList lst_copy(lst);

  ss.clear(); ss.seekg(0); // rewind to beginning

  while(ss >> s)
    {
      EXPECT_EQ(lst_copy.Exists(s), true);
    }
}


// assignment operator
TEST(StudentLinkedList, ASSIGNMENT_OPERATOR_2) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "70 Doe Jane chevy.chase@hollywood.com 999-55-9999" << std::endl;

  while(ss >> s)
    {
      if(!lst.Exists(s))
        {
          EXPECT_EQ(lst.Insert(s), true);
        }
      else
        {
          EXPECT_EQ(lst.Insert(s), false);
        }
      EXPECT_EQ(lst.Exists(s), true);
    }

  StudentLinkedList lst_copy;
  lst_copy = lst;

  ss.clear(); ss.seekg(0); // rewind to beginning

  while(ss >> s)
    {
      EXPECT_EQ(lst_copy.Exists(s), true);
    }
}
