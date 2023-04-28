#ifndef GET_ALL_COURSES_OF_STUDENTS_IN_CLASS_H
#define GET_ALL_COURSES_OF_STUDENTS_IN_CLASS_H

#include "../../../Struct/Course.h"
#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Score.h"

Node<std::string>* getAllCoursesOfStudentsInClass(Node<Score>* allScoresOfClass);
int getCourseCredits(
    Node<Course>* allCourses, const std::string& courseID, const std::string& className
);

#endif
