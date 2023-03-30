#include "ImportScoreboard.h"

#include <sstream>

#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckScore/CheckScore.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllScores/GetAllScores.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../InputCourse/InputCourse.h"
#include "../OpenFile/OpenFile.h"

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

    if (checkScoreExists(allScores, score)) {
        throw std::invalid_argument("This record already exists");
    }
}

void saveScores(Node<Score> *newScores) {
    std::ofstream fout;
    writeFile(fout, "Data/Score.txt", std::ios::app);

    for (; newScores; newScores = newScores->next) {
        Score score = newScores->data;
        Student_Course student_course = score.student_course;
        fout << student_course.studentID << '\n';
        fout << student_course.courseID << '\n';
        fout << student_course.className << '\n';
        fout << score.studentFullName << '\n';
        fout << score.otherMark << '\n';
        fout << score.midtermMark << '\n';
        fout << score.finalMark << '\n';
        fout << score.totalMark << '\n';
    }

    fout.close();
}

void importScoreboard() {
    std::ifstream fin;
    std::string importPath, importLine, _;
    bool courseExists, validPath = false;
    Course course;
    Score score;
    Node<Student_Course> *allStudent_Courses = getAllStudent_Courses();
    Node<Course> *allCourses = getAllCourses();
    Node<Student> *allStudents = getAllStudents();
    Node<Score> *allImportedScores = nullptr, *cur, *allCurScores = getAllScores();

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

                try {
                    getScoreFromLine(score, importLine);
                    validateScore(score, allStudents, allStudent_Courses, allCurScores);
                } catch (...) {
                    continue;
                }

                Node<Score> *newNode = new Node(score);

                if (!allImportedScores) {
                    allImportedScores = newNode;
                } else {
                    cur->next = newNode;
                }

                cur = newNode;
            }

            validPath = true;
            fin.close();
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validPath);

    saveScores(allImportedScores);
    deleteLinkedList(allStudent_Courses);
    deleteLinkedList(allCourses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allImportedScores);
    deleteLinkedList(allCurScores);
    std::cout << "Scoreboard successfully imported!\n";
}
