#include "UpdateStudentResult.h"

#include "../../GetAll/GetAllClasses/GetAllClasses.h"
#include "../../GetAll/GetAllCourses/GetAllCourses.h"
#include "../../GetAll/GetAllScores/GetAllScores.h"
#include "../../GetAll/GetAllStudents/GetAllStudents.h"
#include "../../Input/Input.h"
#include "../../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveScore/SaveScore.h"

void updateResult(Node<Score> *&allScores, const Score &score) {
    for (Node<Score> *cur = allScores; cur; cur = cur->next) {
        if (cur->data.studentCourse == score.studentCourse) {
            cur->data = score;
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
            inputStudentCourse(score.studentCourse);
            validateStudentCourse(
                allStudents, allClasses, allCourses, score.studentCourse
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
        std::cout << "No course records, please create one and try again!\n";
        return;
    }

    Node<Score> *allScores = getAllScores();

    if (!allScores) {
        std::cout << "No score records, please import some and try again!\n";
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
