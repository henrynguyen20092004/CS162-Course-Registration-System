#ifndef GET_ALL_COURSES_OF_STUDENTS_IN_CLASS_H
#define GET_ALL_COURSES_OF_STUDENTS_IN_CLASS_H

#include "../../../Struct/Data.h"
#include "../../../Struct/StudentCourse.h"
#include "../GetAll.h"

Node<std::string>* getAllCoursesOfStudentsInClass(Node<Score>* allScoresOfClass);
int getCourseCredits(
    Node<Course>* allCourses, const std::string& courseID, const std::string& className
);

#endif
