#ifndef GET_ALL_COURSES_H
#define GET_ALL_COURSES_H

#include "../../../Struct/Course.h"
#include "../../../Struct/Score.h"
#include "../../../Struct/Semester.h"
#include "../GetAll.h"

Node<Course>* getAllCourses();
Node<Course>* getAllCoursesOfThisSemester();
Node<Course>* getAllCoursesOfStudent(
    const std::string& studentID, const Semester& semester
);
Node<std::string>* getAllCoursesInClassThisSemester(Node<Score>* allScoresOfClass);
int getCourseCredits(const StudentCourse& studentCourse);

#endif
