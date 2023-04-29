#include "RemoveStudentFromCourse.h"

#include "../../Struct/Data.h"
#include "../OperatorOverload/OperatorOverload.h"
#include "../Save/SaveCourse/SaveCourse.h"
#include "../Save/SaveScore/SaveScore.h"

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

void removeScore(Node<Score> *allScores, const StudentCourse &studentCourse) {
    Node<Score> *tmpScore;

    for (; allScores->next; allScores = allScores->next) {
        tmpScore = allScores->next;

        if (tmpScore->data.studentCourse == studentCourse) {
            allScores->next = tmpScore->next;
            delete tmpScore;
            return;
        }
    }
}

void removeStudentFromCourse(const std::string &studentID, const Course &course) {
    StudentCourse studentCourse;
    Node<StudentCourse> *allStudentCourses = new Node(allData.allStudentCourses);
    Node<Score> *allScores = new Node(allData.allScores);
    studentCourse.studentID = studentID;
    studentCourse.courseID = course.id;
    studentCourse.className = course.className;

    removeStudent(allStudentCourses, studentCourse);
    removeScore(allScores, studentCourse);
    saveAllStudentCourses(allStudentCourses->next);
    saveScores(allScores->next);
    allData.allStudentCourses = allStudentCourses->next;
    allData.allScores = allScores->next;
    delete allStudentCourses;
    delete allScores;
}
