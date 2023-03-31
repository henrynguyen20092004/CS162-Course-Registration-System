#ifndef VALIDATE_STUDENT_H
#define VALIDATE_STUDENT_H

#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"

void validateStudent(
    Node<Student> *allStudents, Node<std::string> *allClasses, Student &student,
    bool checkStudentAlreadyExists
);

#endif