#include "GetAllScores.h"

#include "../../../Struct/Data.h"
#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void readScore(std::ifstream& fin, Score& score) {
    getline(fin, score.studentCourse.studentID);

    if (!fin.good()) {
        return;
    }

    std::string otherMark, midtermMark, finalMark, totalMark;
    getline(fin, score.studentCourse.courseID);
    getline(fin, score.studentCourse.className);
    getline(fin, score.studentFullName);
    getline(fin, otherMark);
    getline(fin, midtermMark);
    getline(fin, finalMark);
    getline(fin, totalMark);
    score.otherMark = stod(otherMark);
    score.midtermMark = stod(midtermMark);
    score.finalMark = stod(finalMark);
    score.totalMark = stod(totalMark);
}

Node<Score>* getAllScores() { return getAll("Data/Score.txt", &readScore); }

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
