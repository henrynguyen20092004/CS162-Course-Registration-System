#include "ImportScoreboard.h"

#include <string.h>

#include <sstream>

#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllScores/GetAllScores.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../InputAndValidateCourse/InputAndValidateCourse.h"
#include "../SaveScore/SaveScore.h"
#include "../ShowCSVErrorLines/ShowCSVErrorLines.h"

void getScoreFromLine(Score &score, const std::string &importLine) {
    std::string _;
    std::istringstream importStream(importLine);
    getline(importStream, _, ',');
    getline(importStream, score.student_course.studentID, ',');
    getline(importStream, score.studentFullName, ',');
    score.otherMark = scoreInput(importStream, ',');
    score.midtermMark = scoreInput(importStream, ',');
    score.finalMark = scoreInput(importStream, ',');
    score.totalMark = scoreInput(importStream);
}

void checkImportedScore(
    const Score &score, Node<Student> *allStudents,
    Node<Student_Course> *allStudent_Courses, Node<Score> *allScores
) {
    Student_Course student_course = score.student_course;

    if (!checkStudentIDExists(allStudents, student_course.studentID) ||
        !checkStudentInCourse(
            allStudent_Courses, student_course.studentID, student_course.courseID,
            student_course.className
        )) {
        throw std::invalid_argument("Invalid student ID");
    }

    for (; allStudents; allStudents = allStudents->next) {
        Student student = allStudents->data;

        if (student.id == score.student_course.studentID) {
            std::string fullName = student.lastName + ' ' + student.firstName;

            if (fullName != score.studentFullName) {
                throw std::invalid_argument("Invalid student name");
            }
        }
    }

    for (; allScores; allScores = allScores->next) {
        if (allScores->data == score) {
            throw std::invalid_argument("Duplicated record");
        } else if (allScores->data.student_course == score.student_course) {
            allScores->data = score;
            throw std::runtime_error("Record updated");
        }
    }
}

void importScoreboard() {
    std::string importPath, importLine, _;
    bool validCourse = false, validPath = false;
    int curLine = 1;
    Course course;
    Score score;
    Node<Student_Course> *allStudent_Courses = getAllStudent_Courses();
    Node<Course> *allCourses = getAllCourses();
    Node<Student> *allStudents = getAllStudents();
    Node<Score> *newScores = nullptr, *cur, *allScores = getAllScores();
    Node<int> *duplicateErrors = nullptr, *curDuplicateErrors, *invalidErrors = nullptr,
              *curInvalidErrors;

    do {
        try {
            inputCourseIDAndClassName(course);
            validateCourseIDAndClass(allCourses, course, false);
            validCourse = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validCourse);

    score.student_course.courseID = course.id;
    score.student_course.className = course.className;

    do {
        try {
            std::cout << "Please enter the path to the CSV: ";
            getline(std::cin, importPath);

            if (importPath == "") {
                std::cout << "Please enter a path!\n";
                continue;
            }

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
                    checkImportedScore(score, allStudents, allStudent_Courses, allScores);
                } catch (std::invalid_argument &error) {
                    if (!strcmp(error.what(), "Duplicated record")) {
                        pushToEndLinkedList(duplicateErrors, curDuplicateErrors, curLine);
                    } else {
                        pushToEndLinkedList(invalidErrors, curInvalidErrors, curLine);
                    }

                    continue;
                } catch (...) {
                    continue;
                }

                pushToEndLinkedList(newScores, cur, score);
            }

            validPath = true;
            fin.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    showCSVErrorLines(duplicateErrors, invalidErrors);
    addNewListToOldList(allScores, newScores);
    saveScores(allScores);
    deleteLinkedList(allStudent_Courses);
    deleteLinkedList(allCourses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allScores);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    std::cout << "Scoreboard successfully imported!\n";
}
