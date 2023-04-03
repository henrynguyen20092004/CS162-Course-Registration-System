#include "CheckStudentInCourse.h"

bool checkStudentInCourse(
    Node<StudentCourse>* allStudentCourses, const std::string& studentID,
    const std::string& courseID, const std::string& className
) {
    for (; allStudentCourses; allStudentCourses = allStudentCourses->next) {
        StudentCourse studentCourse = allStudentCourses->data;

        if (studentCourse.studentID == studentID && studentCourse.courseID == courseID &&
            studentCourse.className == className) {
            return true;
        }
    }

    return false;
}
