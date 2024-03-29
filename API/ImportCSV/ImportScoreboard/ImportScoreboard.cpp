#include "ImportScoreboard.h"

#include <cstring>
#include <sstream>

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckStudent/CheckStudent.h"
#include "../../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveScore/SaveScore.h"
#include "../../ShowCSVErrorLines/ShowCSVErrorLines.h"
#include "../../SplitCourseToIDAndClassName/SplitCourseToIDAndClassName.h"

void getScoreFromLine(Score &score, const std::string &importLine) {
    std::string part;
    std::istringstream importStream(importLine);
    getline(importStream, part, ',');
    getline(importStream, score.studentCourse.studentID, ',');
    getline(importStream, part, ',');
    score.studentFullName = checkAndConvertToName(part, "full name");
    getline(importStream, part, ',');
    score.otherMark = checkAndConvertToScore(part, "other mark");
    getline(importStream, part, ',');
    score.midtermMark = checkAndConvertToScore(part, "midterm mark");
    getline(importStream, part, ',');
    score.finalMark = checkAndConvertToScore(part, "final mark");
    getline(importStream, part);
    score.totalMark = checkAndConvertToScore(part, "total mark");
}

void checkImportedScore(
    Score &score, Node<Student> *allStudents, Node<Score> *allScores
) {
    StudentCourse studentCourse = score.studentCourse;

    if (!checkStudentIDExists(allStudents, studentCourse.studentID) ||
        !checkStudentInCourse(GlobalVar::allData.allStudentCourses, studentCourse)) {
        throw std::invalid_argument("Invalid student ID");
    }

    for (; allStudents; allStudents = allStudents->next) {
        Student student = allStudents->data;

        if (student.id == score.studentCourse.studentID) {
            std::string fullName = student.lastName + ' ' + student.firstName;

            if (fullName != score.studentFullName) {
                throw std::invalid_argument("Invalid student name");
            }
        }
    }

    for (; allScores; allScores = allScores->next) {
        if (allScores->data == score) {
            throw std::invalid_argument("Duplicated record");
        } else if (allScores->data.studentCourse == score.studentCourse) {
            allScores->data = score;
            throw std::runtime_error("Record updated");
        }
    }
}

void importScoreboard(char **inputs, char **dropDownItems, const std::string &course) {
    int curLine = 1;
    Score score;
    Node<Score> *newScores = nullptr, *cur;
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;
    std::string *courseIDAndClassName = new std::string[2], importPath = inputs[1],
                importLine, _;

    splitCourseToIDAndClassName(courseIDAndClassName, course);
    score.studentCourse.courseID = courseIDAndClassName[0];
    score.studentCourse.className = courseIDAndClassName[1];
    delete[] courseIDAndClassName;

    std::ifstream fin;
    readFile(fin, importPath);
    getline(fin, _);

    while (fin.good()) {
        getline(fin, importLine);

        if (!fin.good()) {
            break;
        }

        ++curLine;

        try {
            getScoreFromLine(score, importLine);
            checkImportedScore(
                score, GlobalVar::allData.allStudents, GlobalVar::allData.allScores
            );
        } catch (std::invalid_argument &error) {
            if (!strcmp(error.what(), "Duplicated record")) {
                pushToEndOfLinkedList(duplicateErrors, curDuplicateErrors, curLine);
            } else {
                pushToEndOfLinkedList(invalidErrors, curInvalidErrors, curLine);
            }
            continue;
        } catch (...) {
            continue;
        }

        pushToEndOfLinkedList(newScores, cur, score);
    }

    fin.close();
    addNewItemsToOldList(GlobalVar::allData.allScores, newScores);
    saveScores(GlobalVar::allData.allScores);
    showCSVErrorLines(duplicateErrors, invalidErrors, curLine);
}
