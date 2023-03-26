#ifndef GET_ALL_STUDENTS_H
#define GET_ALL_STUDENTS_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Student.h"
#include "../../Struct/Student_Course_Class.h"

Node<Student> *getAllStudents();
Node<Student_Course_Class> *getAllStudent_Course_Class();
Node<std::string> *getAllStudentsIDInClass(std::string &className);
Node<Student_Course_Class> *getAllStudentsInCourse(Course &course);

#endif
