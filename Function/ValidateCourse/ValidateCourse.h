#ifndef VALIDATE_COURSE_H
#define VALIDATE_COURSE_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"

void validateCourseIDAndClass(
    Node<Course> *allCourses, Node<std::string> *allClasses, const Course &course
);
void validateOtherInformation(const Course &course);

#endif
