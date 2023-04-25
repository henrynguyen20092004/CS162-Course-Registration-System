#include "RemoveStudentFromCourse.h"

#include "../../Struct/Data.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"
#include "../OperatorOverload/OperatorOverload.h"
#include "../Save/SaveCourse/SaveCourse.h"

void removeStudent(
    Node<StudentCourse> *allStudentCourses, const StudentCourse &studentCourse
) {
    Node<StudentCourse> *tmpStudentCourse;

    for (; allStudentCourses->next; allStudentCourses = allStudentCourses->next) {
        tmpStudentCourse = allStudentCourses->next;

        if (tmpStudentCourse->data == studentCourse) {
            allStudentCourses->next = tmpStudentCourse->next;
            delete tmpStudentCourse;
            return;
        }
    }
}

void removeStudentFromCourse(const std::string &studentID, const Course &course) {
    StudentCourse studentCourse;
    studentCourse.studentID = studentID;
    studentCourse.courseID = course.id;
    studentCourse.className = course.className;

    Node<StudentCourse> *allStudentCourses = new Node(allData.allStudentCourses);

    validateStudentCourse(
        allData.allStudents, allData.allClasses, allData.allCourses, studentCourse
    );

    if (!checkStudentInCourse(
            allStudentCourses, studentCourse.studentID, studentCourse.courseID,
            studentCourse.className
        )) {
        throw std::invalid_argument(
            "The student doesn't exist in course, please try again!"
        );
    }

    removeStudent(allStudentCourses, studentCourse);
    saveAllStudentCourses(allStudentCourses->next);
    allData.allStudentCourses = allStudentCourses->next;
    delete allStudentCourses;
}
