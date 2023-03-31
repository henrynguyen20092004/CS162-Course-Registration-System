#include "CheckStudentInCourse.h"

bool checkStudentInCourse(
    Node<Student_Course>* allStudent_Courses, const std::string& studentID,
    const std::string& courseID, const std::string& className
) {
    for (; allStudent_Courses; allStudent_Courses = allStudent_Courses->next) {
        Student_Course student_course = allStudent_Courses->data;

        if (student_course.studentID == studentID &&
            student_course.courseID == courseID &&
            student_course.className == className) {
            return true;
        }
    }

    return false;
}
