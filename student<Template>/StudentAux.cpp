#include "StudentAux.h"
#include <iostream>
#include <fstream>

int ReadStudentFile(const std::string &filename, LinkedList<Student> &students)
{
    std::ifstream fin(filename);
    int count = 0;
    while(fin)
    {
        fin >> students;
        if(!fin)
        {
            count++;
        }
    }
    return count;
}

int RemoveStudents(const std::string &filename, LinkedList<Student> &students)
{
    std::ifstream fin(filename);
    int count = 0;
    Student test;
    char tssn[max_ssn];
    while(fin)
    {
        fin >> tssn;
        if(fin)
	    {
	        test.setSsn(tssn);
	        if (!students.Delete(test))
	        {
	            count++;
	        }
	    }
    }
    return count;
}

double AverageAgeStudents(const std::string &filename, LinkedList<Student> &students)
{
    std::ifstream fin(filename);
    double total = 0;
    double ave = 0;
    double count = 0;
    Student test;
    Student found;
    int age = 0;
    char tssn[max_ssn];
    while(fin)
    {
        fin >> tssn;
        if(fin)
	    {
	        test.setSsn(tssn);
	        if(students.Exists(test))
	        {
	            found = students.Retrieve(test);
	            age = found.getAge();
	            count ++;
	            total += age;
	        }
	    }
    }
    ave = total/count;
    return ave;
}
