#include "GetAllScores.h"

void readScore(std::ifstream &fin, Score &score) {
    getline(fin, score.studentCourse.studentID);

    if (!fin.good()) {
        return;
    }

    std::string otherMark, midtermMark, finalMark, totalMark;
    getline(fin, score.studentCourse.courseID);
    getline(fin, score.studentCourse.className);
    getline(fin, score.studentFullName);
    getline(fin, otherMark);
    getline(fin, midtermMark);
    getline(fin, finalMark);
    getline(fin, totalMark);
    score.otherMark = stoi(otherMark);
    score.midtermMark = stoi(midtermMark);
    score.finalMark = stoi(finalMark);
    score.totalMark = stoi(totalMark);
}

Node<Score> *getAllScores() {
    return getAll("Data/Score.txt", &readScore);
}
