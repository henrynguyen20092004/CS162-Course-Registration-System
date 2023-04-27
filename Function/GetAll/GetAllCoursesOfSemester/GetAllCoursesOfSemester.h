#ifndef GET_ALL_COURSES_OF_SEMESTER_H
#define GET_ALL_COURSES_OF_SEMESTER_H

#include "../../../Struct/Data.h"

Node<Course>* getAllCourseOfSemester(
    const std::string& schoolYear, const int& semesterNumber
);

#endif