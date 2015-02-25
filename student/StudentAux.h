#ifndef _STUDENT_AUX_H_
#define _STUDENT_AUX_H_
#include "Student.h"
#include "StudentLinkedList.h"

int ReadStudentFile(const std::string &filename, StudentLinkedList &students);
int RemoveStudents(const std::string &filename, StudentLinkedList &students);
double AverageAgeStudents(const std::string &filename, StudentLinkedList &students);


#endif
