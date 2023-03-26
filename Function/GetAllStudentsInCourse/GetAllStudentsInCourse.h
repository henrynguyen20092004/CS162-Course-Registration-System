#ifndef GET_ALL_STUDENTS_IN_COURSE_H
#define GET_ALL_STUDENTS_IN_COURSE_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"
#include "../../Struct/Student_Course.h"

Node<Student_Course> *getAllStudentsInCourse(const Course &course);

#endif
