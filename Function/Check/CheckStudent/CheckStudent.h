#ifndef CHECK_STUDENT_H
#define CHECK_STUDENT_H

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Student.h"

bool checkStudentIDExists(Node<Student>* allStudents, const std::string& studentID);
bool checkStudentInClass(Node<Student>* allStudentsInClass, const std::string& studentID);

#endif
