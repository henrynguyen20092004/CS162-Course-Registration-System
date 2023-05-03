#include "GetAllStudentsInCourse.h"

#include "../../../GlobalVar/GlobalVar.h"

Node<Student> *getAllStudentsInCourse(const Course &course) {
    Node<Student> *allStudentsInCourse = nullptr, *curStudentsInCourse;

    for (Node<StudentCourse> *curStudentCourse = GlobalVar::allData.allStudentCourses;
         curStudentCourse; curStudentCourse = curStudentCourse->next) {
        StudentCourse studentCourse = curStudentCourse->data;

        if (course.id == studentCourse.courseID &&
            course.className == studentCourse.className) {
            for (Node<Student> *curStudent = GlobalVar::allData.allStudents; curStudent;
                 curStudent = curStudent->next) {
                if (curStudent->data.id == studentCourse.studentID) {
                    pushToEndOfLinkedList(
                        allStudentsInCourse, curStudentsInCourse, curStudent->data
                    );
                }
            }
        }
    }

    return allStudentsInCourse;
}
