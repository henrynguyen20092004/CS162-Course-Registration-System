#include "GetAllScores.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckStudent/CheckStudent.h"
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
    Node<Score>*allScoresOfStudentsInCourse = nullptr,
    *cur = GlobalVar::allData.allScores, *curScore;
    std::string* courseIDAndClassName = new std::string[2];
    splitCourseToIDAndClassName(courseIDAndClassName, course);

    for (; cur; cur = cur->next) {
        StudentCourse tmpStudentCourse = cur->data.studentCourse;

        if (tmpStudentCourse.courseID == courseIDAndClassName[0] &&
            tmpStudentCourse.className == courseIDAndClassName[1]) {
            pushToEndOfLinkedList(allScoresOfStudentsInCourse, curScore, cur->data);
        }
    }

    delete[] courseIDAndClassName;
    return allScoresOfStudentsInCourse;
}

Node<Score>* getAllScoresOfStudentsInClass(Node<Student>* allStudentsInClass) {
    Node<Score>*allScoresOfStudentsInClass = nullptr, *cur = GlobalVar::allData.allScores,
    *curScore;

    for (; cur; cur = cur->next) {
        Score score = cur->data;

        if (checkStudentInClass(allStudentsInClass, score.studentCourse.studentID)) {
            pushToEndOfLinkedList(allScoresOfStudentsInClass, curScore, score);
        }
    }

    return allScoresOfStudentsInClass;
}

bool checkScoreExistsInSemester(const Score& score, Node<Course>* allCoursesOfSemester) {
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
    Node<Score>*allScoresOfStudent = nullptr, *curScore;
    Node<Course>* allCoursesOfSemester =
        getAllCoursesOfSemester(currentSemester.schoolYearName, currentSemester.number);

    for (Node<Score>* cur = GlobalVar::allData.allScores; cur; cur = cur->next) {
        Score tmpScore = cur->data;

        if (tmpScore.studentCourse.studentID == studentID &&
            checkScoreExistsInSemester(tmpScore, allCoursesOfSemester)) {
            pushToEndOfLinkedList(allScoresOfStudent, curScore, tmpScore);
        }
    }

    deleteLinkedList(allCoursesOfSemester);
    return allScoresOfStudent;
}
