#ifndef CHECK_COURSE_H
#define CHECK_COURSE_H

#include "../../Struct/Course.h"
#include "../../Struct/LinkedList.h"

Node<std::string> *getAllClassName();
bool checkClassExist(Node<std::string> *allClassName, const std::string &className);
bool checkValidDayOfWeek(const std::string &day);
bool checkCourseExist(
    Node<Course> *allCourse, const std::string &courseID, const std::string &className
);

#endif
