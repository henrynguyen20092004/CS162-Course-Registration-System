#include "ImportScoreboard.h"

#include <sstream>

#include "../../Struct/LinkedList.h"
#include "../../Struct/Score.h"
#include "../Check/CheckCourse/CheckCourse.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../Input/Input.h"
#include "../InputCourse/InputCourse.h"
#include "../OpenFile/OpenFile.h"
#include "../ValidatePath/ValidatePath.h"

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

void importScoreboard() {
    std::ifstream fin;
    std::string importPath, importLine, tempString;
    bool courseExists, validPath = false;
    Course course;
    Score score;
    Node<Course> *allCourses = getAllCourses();
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
            validatePath(importPath);
            readFile(fin, importPath);

            while (fin.good()) {
                getline(fin, importLine);
                std::istringstream importStream(importLine);
                getline(importStream, tempString, ',');
                getline(importStream, score.student_course.studentID, ',');
                getline(importStream, score.studentFullName, ',');
                score.otherMark = scoreInput(importStream, ',');
                score.midtermMark = scoreInput(importStream, ',');
                score.finalMark = scoreInput(importStream, ',');
                score.totalMark = scoreInput(importStream, ',');

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
    deleteLinkedList(allCourses);
    deleteLinkedList(allScores);
    std::cout << "Scoreboard successfully imported!\n";
}
