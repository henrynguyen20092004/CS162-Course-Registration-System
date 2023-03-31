#ifndef STUDENT_COURSE_H
#define STUDENT_COURSE_H

#include <iostream>

struct Student_Course {
    std::string studentID, courseID, className;
};

inline bool operator==(
    const Student_Course &firstStudent_Course, const Student_Course &secondStudent_Course
) {
    return firstStudent_Course.studentID == secondStudent_Course.studentID &&
           firstStudent_Course.courseID == secondStudent_Course.courseID &&
           firstStudent_Course.className == secondStudent_Course.className;
}

#endif
