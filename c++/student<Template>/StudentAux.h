#ifndef _STUDENT_AUX_H_
#define _STUDENT_AUX_H_
#include "Student.h"
#include "LinkedList.h"

int ReadStudentFile(const std::string &filename, LinkedList<Student> &students);
int RemoveStudents(const std::string &filename, LinkedList<Student> &students);
double AverageAgeStudents(const std::string &filename, LinkedList<Student> &students);


#endif
