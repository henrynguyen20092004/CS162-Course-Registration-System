#include "ImportScoreboard.h"

#include <sstream>

#include "../../Struct/LinkedList.h"
#include "../../Struct/Score.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../Check/CheckStudentID/CheckStudentID.h"
#include "../Check/CheckStudentInCourse/CheckStudentInCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../InputCourse/InputCourse.h"
#include "../OpenFile/OpenFile.h"

void saveScore(Node<Score> *newScores) {
    std::ofstream fout;
    writeFile(fout, "Data/Score.txt", std::ios::app);

    for (; newScores; newScores = newScores->next) {
        Score score = newScores->data;
        Student_Course student_course = score.student_course;
        fout << student_course.studentID << '\n';
        fout << student_course.courseID << '-' << student_course.className << '\n';
        fout << score.studentFullName << '\n';
        fout << score.otherMark << '\n';
        fout << score.midtermMark << '\n';
        fout << score.finalMark << '\n';
        fout << score.totalMark << '\n';
    }

    fout.close();
}

void getScoreFromLine(
    Score &score, const std::string &importLine, Node<Student> *allStudents,
    Node<Student_Course> *allStudent_Courses
) {
    std::string part;
    std::istringstream importStream(importLine);

    getline(importStream, part, ',');
    getline(importStream, part, ',');

    if (!checkStudentIDExists(allStudents, part) ||
        !checkStudentInCourse(
            allStudent_Courses, part, score.student_course.courseID,
            score.student_course.className
        )) {
        throw std::invalid_argument("Invalid student ID");
    }

    score.student_course.studentID = part;
    getline(importStream, part, ',');

    for (; allStudents; allStudents = allStudents->next) {
        Student student = allStudents->data;

        if (student.id == score.student_course.studentID) {
            std::string fullName = student.lastName + ' ' + student.firstName;

            if (fullName != part) {
                throw std::invalid_argument("Invalid student name");
            }
        }
    }

    score.studentFullName = part;
    score.otherMark = scoreInput(importStream, ',');
    score.midtermMark = scoreInput(importStream, ',');
    score.finalMark = scoreInput(importStream, ',');
    score.totalMark = scoreInput(importStream);
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
    Node<Score> *allScores = nullptr, *cur;

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
                    getScoreFromLine(score, importLine, allStudents, allStudent_Courses);
                } catch (...) {
                    continue;
                }

                Node<Score> *newNode = new Node(score);

                if (!allScores) {
                    allScores = newNode;
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

    saveScore(allScores);
    deleteLinkedList(allStudent_Courses);
    deleteLinkedList(allCourses);
    deleteLinkedList(allStudents);
    deleteLinkedList(allScores);
    std::cout << "Scoreboard successfully imported!\n";
}
