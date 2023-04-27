#include "GetAllScoresOfStudent.h"

#include "../GetAllCoursesOfSemester/GetAllCoursesOfSemester.h"

bool checkCourseExistsInSemester(const Score& score, Node<Course>* allCoursesOfSemester) {
    for (; allCoursesOfSemester; allCoursesOfSemester = allCoursesOfSemester->next) {
        Course curCourse = allCoursesOfSemester->data;

        if (score.studentCourse.courseID == curCourse.id &&
            score.studentCourse.className == curCourse.className) {
            return true;
        }
    }

    return false;
}

Node<Score>* getAllScoresOfStudent(
    const std::string& studentID, const Semester& currentSemester
) {
    Node<Score>*allScoresOfStudent = new Node<Score>, *curScore = allScoresOfStudent;
    Node<Course>* allCoursesOfSemester =
        getAllCourseOfSemester(currentSemester.schoolYearName, currentSemester.number);

    for (Node<Score>* cur = allData.allScores; cur; cur = cur->next) {
        Score tmpScore = cur->data;

        if (tmpScore.studentCourse.studentID == studentID) {
            pushToEndLinkedList(allScoresOfStudent, curScore, tmpScore);
        }
    }

    for (Node<Score>* cur = allScoresOfStudent; cur->next;) {
        curScore = cur->next;

        if (!checkCourseExistsInSemester(curScore->data, allCoursesOfSemester)) {
            cur->next = curScore->next;
            delete curScore;
        } else {
            cur = cur->next;
        }
    }

    curScore = allScoresOfStudent;
    allScoresOfStudent = allScoresOfStudent->next;
    delete curScore;

    deleteLinkedList(allCoursesOfSemester);
    return allScoresOfStudent;
}
