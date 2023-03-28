#ifndef VALIDATE_COURSE_AND_CLASS_H
#define VALIDATE_COURSE_AND_CLASS_H

#include "../Check/CheckClass/CheckClass.h"
#include "../Check/CheckCourse/CheckCourse.h"

void validateCourseAndClass(
    Node<Course> *allCourses, Node<std::string> *allClasses, const Course &course
);
void validateOtherInformation(const Course &course);

#endif
