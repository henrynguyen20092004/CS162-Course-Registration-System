#ifndef INPUT_AND_VALIDATE_STUDENT_H
#define INPUT_AND_VALIDATE_STUDENT_H

#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"

void inputStudent(Student &student);
void validateStudent(Node<std::string> *allClasses, Student &student);

#endif
