#include "LinkedList.h"
#include "LinkedList.h" // included twice to test #ifndef
#include "gtest/gtest.h"
#include <cstring>
#include <sstream>
#include <string>

// default constructor
TEST(IntLinkedList, CONSTRUCTOR_1) {
  const LinkedList<int> lst_a;
}

// copy constructor
TEST(IntLinkedList, COPY_CONSTRUCTOR_1) {
  const LinkedList<int> lst_a;
  const LinkedList<int> lst_b(lst_a);
}

// assignment operator
TEST(IntLinkedList, ASSIGNMENT_OPERATOR_1) {
  const LinkedList<int> lst_a;
  LinkedList<int> lst_b;
  lst_b = lst_a;
}

// positive insert
TEST(IntLinkedList, INSERT_1) {
  LinkedList<int> lst;
  int s = 1;
  EXPECT_EQ(lst.Insert(s), true);
}

// negative exists
TEST(IntLinkedList, EXISTS_1) {
  LinkedList<int> lst;
  int s = 1;
  EXPECT_EQ(lst.Exists(s), false);
}

// positive exists
TEST(IntLinkedList, EXISTS_2) {
  LinkedList<int> lst;
  int s = 1;
  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
}

// negative insert
TEST(IntLinkedList, INSERT_2) {
  LinkedList<int> lst;
  int s = 1;
  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Insert(s), false);
}

// negative delete
TEST(IntLinkedList, DELETE_1) {
  LinkedList<int> lst;
  int s = 1;
  EXPECT_EQ(lst.Delete(s), false);
}

// positive delete
TEST(IntLinkedList, DELETE_2) {
  LinkedList<int> lst;
  int s = 1;
  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
  EXPECT_EQ(lst.Delete(s), true);
  EXPECT_EQ(lst.Exists(s), false);
  EXPECT_EQ(lst.Delete(s), false);
}

// positive retrieve
TEST(IntLinkedList, RETRIEVE_1) {
  LinkedList<int> lst;
  int s = 1, t;

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
  t = lst.Retrieve(s);
  EXPECT_EQ(t == s, true);
}

// negative retrieve
TEST(IntLinkedList, RETRIEVE_2) {
  LinkedList<int> lst;
  int s = 1, t, d(0);

  EXPECT_EQ(lst.Insert(s), true);
  EXPECT_EQ(lst.Exists(s), true);
  s = 2;
  EXPECT_EQ(lst.Exists(s), false);
  t = lst.Retrieve(s);
  EXPECT_EQ(t == d, true);
}


// copy constructor
TEST(IntLinkedList, COPY_CONSTRUCTOR_2) {
  LinkedList<int> lst;
  unsigned int i;
  int values[6] = { -13, 42, 95, -7, 113, -7 };
  int s;
  for(i = 0; i < sizeof(values)/sizeof(values[0]); i++)
    {
      s = values[i];
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

  LinkedList<int> lst_copy(lst);

  for(i = 0; i < sizeof(values)/sizeof(values[0]); i++)
    {
      s = values[i];
      EXPECT_EQ(lst_copy.Exists(s), true);
    }
}


// assignment operator
TEST(IntLinkedList, ASSIGNMENT_OPERATOR_2) {
  LinkedList<int> lst;
  unsigned int i;
  int values[6] = { -13, 42, 95, -7, 113, -7 };
  int s;
  for(i = 0; i < sizeof(values)/sizeof(values[0]); i++)
    {
      s = values[i];
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

  LinkedList<int> lst_copy;
  lst_copy = lst;

  for(i = 0; i < sizeof(values)/sizeof(values[0]); i++)
    {
      s = values[i];
      EXPECT_EQ(lst_copy.Exists(s), true);
    }
}
