#include "GetAllScoresOfStudentsInCourse.h"

#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

Node<Score>* getAllScoresOfStudentsInCourse(const std::string& course) {
    std::string* courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, course);

    std::string courseID = courseIDAndClassName[0];
    std::string className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    Node<Score>*allScoresOfStudentsInCourse = nullptr, *curScore;

    for (Node<Score>* cur = allData.allScores; cur; cur = cur->next) {
        StudentCourse tmpStudentCourse = cur->data.studentCourse;

        if (tmpStudentCourse.courseID == courseID &&
            tmpStudentCourse.className == className) {
            pushToEndLinkedList(allScoresOfStudentsInCourse, curScore, cur->data);
        }
    }

    return allScoresOfStudentsInCourse;
}
