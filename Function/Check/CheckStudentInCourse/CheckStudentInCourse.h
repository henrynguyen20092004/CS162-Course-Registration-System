#ifndef CHECK_STUDENT_IN_COURSE_H
#define CHECK_STUDENT_IN_COURSE_H

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/StudentCourse.h"

bool checkStudentInCourse(
    Node<StudentCourse>* allStudentCourses, const StudentCourse& studentCourse
);

#endif
