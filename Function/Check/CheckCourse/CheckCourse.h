#ifndef CHECK_COURSE_H
#define CHECK_COURSE_H

#include "../../../Struct/Course.h"
#include "../../../Struct/LinkedList.h"

bool checkCourseExists(
    Node<Course> *allCourse, const std::string &courseID, const std::string &className
);

#endif
