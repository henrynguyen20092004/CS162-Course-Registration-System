#ifndef CHECK_STUDENT_ID_H
#define CHECK_STUDENT_ID_H

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Student.h"

bool checkStudentIDExists(Node<Student>* allStudents, const std::string& studentID);

#endif
