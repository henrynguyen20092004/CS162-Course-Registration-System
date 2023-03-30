#include "GetAllScores.h"

#include "../../Input/Input.h"

void readScore(std::ifstream &fin, Score &score) {
    getline(fin, score.student_course.studentID);
    getline(fin, score.student_course.courseID);
    getline(fin, score.student_course.className);
    getline(fin, score.studentFullName);
    score.otherMark = scoreInput(fin);
    score.midtermMark = scoreInput(fin);
    score.finalMark = scoreInput(fin);
    score.totalMark = scoreInput(fin);
}

Node<Score> *getAllScores() {
    return getAll("Data/Score.txt", &readScore);
}
