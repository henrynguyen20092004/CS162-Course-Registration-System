#ifndef GET_ALL_STUDENTS_H
#define GET_ALL_STUDENTS_H

#include "../../../Struct/Student.h"
#include "../../../Struct/Student_Course.h"
#include "../GetAll.h"

Node<Student> *getAllStudents();
Node<Student_Course> *getAllStudent_Courses();

#endif
