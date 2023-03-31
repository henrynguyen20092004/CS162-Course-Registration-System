#include "UpdateStudentResult.h"

#include "../GetAll/GetAllClasses/GetAllClasses.h"
#include "../GetAll/GetAllCourses/GetAllCourses.h"
#include "../GetAll/GetAllScores/GetAllScores.h"
#include "../GetAll/GetAllStudents/GetAllStudents.h"
#include "../Input/Input.h"
#include "../InputStudentCourse/InputStudentCourse.h"
#include "../SaveScore/SaveScore.h"
#include "../ValidateStudentCourse/ValidateStudentCourse.h"

void updateResult(Node<Score> *&allScores, const Score &score) {
    for (Node<Score> *cur = allScores; cur; cur = cur->next) {
        if (cur->data.student_course == score.student_course) {
            cur->data.otherMark = score.otherMark;
            cur->data.midtermMark = score.midtermMark;
            cur->data.finalMark = score.finalMark;
            cur->data.totalMark = score.totalMark;
            return;
        }
    }
}

void inputMarks(Score &score) {
    bool validScore = false;

    do {
        try {
            std::cout << "Please enter the student's other mark: ";
            score.otherMark = scoreInput();
            std::cout << "Please enter the student's midterm mark: ";
            score.midtermMark = scoreInput();
            std::cout << "Please enter the student's final mark: ";
            score.finalMark = scoreInput();
            std::cout << "Please enter the student's total mark: ";
            score.totalMark = scoreInput();
            validScore = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validScore);
}

void inputScoreToUpdate(Node<Course> *allCourses, Score &score) {
    Node<std::string> *allClasses = getAllClasses();
    Node<Student> *allStudents = getAllStudents();
    bool validInput = false;

    do {
        try {
            inputStudent_Course(score.student_course);
            validateStudent_Course(
                allStudents, allClasses, allCourses, score.student_course
            );
            inputMarks(score);
            validInput = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validInput);

    deleteLinkedList(allStudents);
    deleteLinkedList(allClasses);
}

void updateStudentResult() {
    Node<Course> *allCourses = getAllCourses();

    if (!allCourses) {
        std::cout << "No course records, please create one and try again later!\n";
        return;
    }

    Node<Score> *allScores = getAllScores();

    if (!allScores) {
        std::cout << "No score records, please import some and try again later!\n";
        return;
    }

    Score score;
    inputScoreToUpdate(allCourses, score);
    updateResult(allScores, score);
    saveScores(allScores);
    deleteLinkedList(allCourses);
    deleteLinkedList(allScores);
    std::cout << "Student's result successfully update!\n";
}