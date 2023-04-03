#ifndef SAVE_COURSE_H
#define SAVE_COURSE_H

#include "../../../Struct/Course.h"
#include "../../../Struct/LinkedList.h"
#include "../../../Struct/StudentCourse.h"

void saveAllCourses(Node<Course> *allCourses);
void saveAllStudentCourses(Node<StudentCourse> *allStudentCourses);

#endif
