#include "CheckStudentInCourse.h"

bool checkStudentInCourse(
    Node<Student_Course>* allStudent_Course, const std::string& studentID,
    const std::string& courseID, const std::string& className
) {
    for (; allStudent_Course; allStudent_Course = allStudent_Course->next) {
        Student_Course student_course = allStudent_Course->data;

        if (student_course.studentID == studentID &&
            student_course.courseID == courseID &&
            student_course.className == className) {
            return true;
        }
    }

    return false;
}
