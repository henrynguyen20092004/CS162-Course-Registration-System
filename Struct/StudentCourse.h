#ifndef STUDENT_COURSE_H
#define STUDENT_COURSE_H

#include <iostream>

struct StudentCourse {
    std::string studentID, courseID, className;
};

inline bool operator==(
    const StudentCourse &firstStudentCourse, const StudentCourse &secondStudentCourse
) {
    return firstStudentCourse.studentID == secondStudentCourse.studentID &&
           firstStudentCourse.courseID == secondStudentCourse.courseID &&
           firstStudentCourse.className == secondStudentCourse.className;
}

#endif
