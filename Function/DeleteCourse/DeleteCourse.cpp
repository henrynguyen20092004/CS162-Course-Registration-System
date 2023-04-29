#include "DeleteCourse.h"

#include "../../Struct/Data.h"
#include "../Save/SaveCourse/SaveCourse.h"
#include "../Save/SaveScore/SaveScore.h"
#include "../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void deleteAllScoresInCourse(const std::string &id, const std::string &className) {
    Node<Score> *allScores = new Node(allData.allScores), *cur = allScores, *tmpScore;

    while (cur->next) {
        StudentCourse tmpStudentCourse = cur->next->data.studentCourse;

        if (tmpStudentCourse.courseID == id && tmpStudentCourse.className == className) {
            tmpScore = cur->next;
            cur->next = tmpScore->next;
            delete tmpScore;
        } else {
            cur = cur->next;
        }
    }

    allData.allScores = allScores->next;
    saveScores(allData.allScores);
    delete allScores;
}

void deleteAllStudentsInCourse(const std::string &id, const std::string &className) {
    Node<StudentCourse> *allStudentCourses = new Node(allData.allStudentCourses),
                        *cur = allStudentCourses, *tmpStudentCourse;

    while (cur->next) {
        if (cur->next->data.courseID == id && cur->next->data.className == className) {
            tmpStudentCourse = cur->next;
            cur->next = tmpStudentCourse->next;
            delete tmpStudentCourse;
        } else {
            cur = cur->next;
        }
    }

    allData.allStudentCourses = allStudentCourses->next;
    saveAllStudentCourses(allData.allStudentCourses);
    delete allStudentCourses;
}

void deleteCourse(const std::string &course) {
    Node<Course> *allCourses = new Node(allData.allCourses), *cur = allCourses,
                 *tmpCourse;

    std::string *courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, course);

    for (; cur->next; cur = cur->next) {
        tmpCourse = cur->next;

        if (courseIDAndClassName[0] == tmpCourse->data.id &&
            courseIDAndClassName[1] == tmpCourse->data.className) {
            deleteAllScoresInCourse(courseIDAndClassName[0], courseIDAndClassName[1]);
            deleteAllStudentsInCourse(courseIDAndClassName[0], courseIDAndClassName[1]);
            cur->next = tmpCourse->next;
            delete tmpCourse;
            break;
        }
    }

    allData.allCourses = allCourses->next;
    saveAllCourses(allData.allCourses);
    delete allCourses;
    delete[] courseIDAndClassName;
}
