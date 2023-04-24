#ifndef GET_ALL_COURSES_OF_STUDENT_H
#define GET_ALL_COURSES_OF_STUDENT_H

#include "../../../Struct/Data.h"

Node<Course> *getAllCoursesOfStudent(
    const std::string &studentID, const Semester &semester
);

#endif
