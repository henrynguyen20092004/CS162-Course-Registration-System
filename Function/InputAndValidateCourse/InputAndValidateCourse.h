#ifndef INPUT_AND_VALIDATE_COURSE_H
#define INPUT_AND_VALIDATE_COURSE_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"

void inputCourseIDAndClassName(Course &course);
void inputOtherCourseInformation(Course &course);
void validateCourseIDAndClass(
    Node<Course> *allCourses, Node<std::string> *allClasses, const Course &course
);
void validateOtherCourseInformation(const Course &course);

#endif
