#include "StudentAux.h" // Should make the rest of the data types available.
#include "gtest/gtest.h"
#include <cstring>
#include <sstream>

// ReadStudentFile
TEST(StudentFiles, READ_FILE_1) {
  std::string name = "tests/3_InsertNames-CS3005.txt";
  LinkedList<Student> lst;
  int n = ReadStudentFile(name, lst);
  EXPECT_EQ(n, 1);
}

// RemoveStudents
TEST(StudentFiles, REMOVE_1) {
  std::string name = "tests/3_InsertNames-CS3005.txt";
  LinkedList<Student> lst;
  int n = ReadStudentFile(name, lst);
  EXPECT_EQ(n, 1);

  std::string rname = "tests/3_DeleteNames-CS3005.txt";
  int d = RemoveStudents(rname, lst);
  EXPECT_EQ(d, 6607);
}

// AverageAgeStudents
TEST(StudentFiles, AVERAGE_1) {
  std::string name = "tests/3_InsertNames-CS3005.txt";
  LinkedList<Student> lst;
  int n = ReadStudentFile(name, lst);
  EXPECT_EQ(n, 1);

  std::string rname = "tests/3_DeleteNames-CS3005.txt";
  int d = RemoveStudents(rname, lst);
  EXPECT_EQ(d, 6607);

  std::string aname = "tests/3_RetrieveNames-CS3005.txt";
  double avg = AverageAgeStudents(aname, lst);
  EXPECT_GE(avg, 49.4);
  EXPECT_LE(avg, 49.6);
}
