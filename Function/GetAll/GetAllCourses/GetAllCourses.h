#ifndef GET_ALL_COURSES_H
#define GET_ALL_COURSES_H

#include "../../../Struct/Course.h"
#include "../../../Struct/Score.h"
#include "../../../Struct/Semester.h"
#include "../GetAll.h"

Node<Course>* getAllCourses();
Node<Course>* getAllCoursesOfSemester(
    const std::string& schoolYear, const int& semesterNumber
);
Node<Course>* getAllCoursesOfStudent(
    const std::string& studentID, const Semester& semester
);
Node<std::string>* getAllCoursesOfStudentsInClass(Node<Score>* allScoresOfClass);
int getCourseCredits(
    Node<Course>* allCourses, const std::string& courseID, const std::string& className
);

#endif
