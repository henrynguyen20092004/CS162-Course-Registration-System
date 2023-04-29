#include "CheckStudentInCourse.h"

#include "../../OperatorOverload/OperatorOverload.h"

bool checkStudentInCourse(
    Node<StudentCourse>* allStudentCourses, const StudentCourse& studentCourse
) {
    for (; allStudentCourses; allStudentCourses = allStudentCourses->next) {
        if (allStudentCourses->data == studentCourse) {
            return true;
        }
    }

    return false;
}
