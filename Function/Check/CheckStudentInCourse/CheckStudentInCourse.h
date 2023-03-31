#ifndef CHECK_STUDENT_IN_COURSE_H
#define CHECK_STUDENT_IN_COURSE_H

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Student_Course.h"

bool checkStudentInCourse(
    Node<Student_Course>* allStudent_Course, const std::string& studentID,
    const std::string& courseID, const std::string& className
);

#endif
