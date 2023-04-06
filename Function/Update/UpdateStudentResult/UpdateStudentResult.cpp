#include "UpdateStudentResult.h"

#include "../../../Struct/Data.h"
#include "../../Input/Input.h"
#include "../../InputAndValidate/InputAndValidateStudentCourse/InputAndValidateStudentCourse.h"
#include "../../OperatorOverload/OperatorOverload.h"
#include "../../Save/SaveScore/SaveScore.h"

void updateResult(Node<Score> *allScores, const Score &score) {
    for (; allScores; allScores = allScores->next) {
        if (allScores->data.studentCourse == score.studentCourse) {
            allScores->data = score;
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

void inputScoreToUpdate(Score &score) {
    bool validInput = false;

    do {
        try {
            inputStudentCourse(score.studentCourse);
            validateStudentCourse(
                allData.allStudents, allData.allClasses, allData.allCourses,
                score.studentCourse
            );
            inputMarks(score);
            validInput = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validInput);
}

void updateStudentResult() {
    if (!allData.allCourses) {
        std::cout << "No course records, please create one and try again!\n";
        return;
    }

    if (!allData.allScores) {
        std::cout << "No score records, please import some and try again!\n";
        return;
    }

    Score score;
    inputScoreToUpdate(score);
    updateResult(allData.allScores, score);
    saveScores(allData.allScores);
    std::cout << "Student's result successfully update!\n";
}
