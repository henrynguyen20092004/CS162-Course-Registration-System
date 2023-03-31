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
#include "../InputCourse/InputCourse.h"
#include "../SaveScore/SaveScore.h"

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

void validateScore(
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
            allScores->data.otherMark = score.otherMark;
            allScores->data.midtermMark = score.midtermMark;
            allScores->data.finalMark = score.finalMark;
            allScores->data.totalMark = score.totalMark;
            throw std::runtime_error("Record updated");
        }
    }
}

void showCSVErrorLines(Node<int> *errorLines, const std::string &errorMessage) {
    if (!errorLines) {
        return;
    }

    std::cout << errorMessage;

    for (; errorLines; errorLines = errorLines->next) {
        std::cout << ' ' << errorLines->data;
    }

    std::cout << "\nPlease check them again!\n";
}

void addNewScoreToOldList(Node<Score> *&allScores, Node<Score> *newScores) {
    if (!allScores) {
        allScores = newScores;
        return;
    }

    Node<Score> *cur = allScores;
    for (; cur->next; cur = cur->next)
        ;
    cur->next = newScores;
}

void importScoreboard() {
    std::ifstream fin;
    std::string importPath, importLine, _;
    bool courseExists, validPath = false;
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
        inputCourseIDAndClassName(course);
        courseExists = checkCourseExists(allCourses, course.id, course.className);

        if (!courseExists) {
            std::cout << "This course does not exist. Please try again!\n";
        }
    } while (!courseExists);

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

            readFile(fin, importPath);
            getline(fin, _);

            while (fin.good()) {
                getline(fin, importLine);

                if (importLine == "") {
                    break;
                }

                ++curLine;

                try {
                    getScoreFromLine(score, importLine);
                    validateScore(score, allStudents, allStudent_Courses, allScores);
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

    showCSVErrorLines(duplicateErrors, "The following line(s) are duplicated:");
    showCSVErrorLines(invalidErrors, "The following line(s) have invalid record(s):");
    addNewScoreToOldList(allScores, newScores);
    saveScores(allScores);
    deleteLinkedList(allStudent_Courses);
    deleteLinkedList(allCourses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allScores);
    deleteLinkedList(duplicateErrors);
    deleteLinkedList(invalidErrors);
    std::cout << "Scoreboard successfully imported!\n";
}
