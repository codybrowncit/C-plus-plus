#include "StudentLinkedList.h"
#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <sstream>

// Output Operator
TEST(StudentLinkedList, OSTREAM_1) {
  const StudentLinkedList lst;
  std::stringstream ss;
  ss << lst;
  EXPECT_EQ(std::strcmp(ss.str().c_str(), ""), 0);
}

// Output Operator
TEST(StudentLinkedList, OSTREAM_2) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss,tt;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "70 Doe Jane chevy.chase@hollywood.com 999-55-9999" << std::endl;

  while(ss >> s)
    {
      lst.Insert(s);
    }

  tt << lst;

  // test for last character
  std::string str = tt.str();
  EXPECT_EQ(str[str.size()-1], '9');
  int count = 0;
  while(tt >> s)
    {
      EXPECT_EQ(lst.Exists(s), true);
      count ++;
    }
  EXPECT_EQ(count, 4); // unique entries
}

// Input Operator
TEST(StudentLinkedList, ISTREAM_1) {
  StudentLinkedList lst;
  Student s;
  std::stringstream ss,tt;

  ss << "123 Jones Davey davey.jones@locker.com 999-99-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "40 Dug Dig games@video.com 999-33-9999" << std::endl;
  ss << "30 Builder Bob bob.builder@tv.com 999-77-9999" << std::endl;
  ss << "70 Doe Jane chevy.chase@hollywood.com 999-55-9999" << std::endl;

  ss >> lst;

  // check for existence
  ss.clear(); ss.seekg(0); // rewind to beginning
  while(ss >> s)
    {
      EXPECT_EQ(lst.Exists(s), true);
    }

  // check for duplicates
  ss.clear(); ss.seekg(0); // rewind to beginning
  int count = 0;
  while(ss >> s)
    {
      if(lst.Delete(s))
        {
          count ++;
        }
    }
  EXPECT_EQ(count, 4);
}
