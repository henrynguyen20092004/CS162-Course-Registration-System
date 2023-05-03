#ifndef GET_ALL_STUDENTS_H
#define GET_ALL_STUDENTS_H

#include "../../../Struct/Student.h"
#include "../../../Struct/StudentCourse.h"
#include "../GetAll.h"

Node<Student> *getAllStudents();
Node<StudentCourse> *getAllStudentCourses();

#endif
