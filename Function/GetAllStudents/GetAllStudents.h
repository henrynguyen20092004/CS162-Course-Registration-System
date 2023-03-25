#ifndef GET_ALL_STUDENTS_H
#define GET_ALL_STUDENTS_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"
#include "../../Struct/Student_Course.h"

Node<Student> *getAllStudents();
Node<Student_Course> *getAllStudent_Course();
Node<std::string> *getAllStudentsIDInClass(std::string &className);
Node<Student_Course> *getAllStudentsInCourse(Course &course);

#endif
