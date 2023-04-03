#include "SaveScore.h"

#include "../OpenFile/OpenFile.h"

void saveScores(Node<Score> *allScores) {
    std::ofstream fout;
    writeFile(fout, "Data/Score.txt");

    for (; allScores; allScores = allScores->next) {
        Score score = allScores->data;
        StudentCourse studentCourse = score.studentCourse;
        fout << studentCourse.studentID << '\n';
        fout << studentCourse.courseID << '\n';
        fout << studentCourse.className << '\n';
        fout << score.studentFullName << '\n';
        fout << score.otherMark << '\n';
        fout << score.midtermMark << '\n';
        fout << score.finalMark << '\n';
        fout << score.totalMark << '\n';
    }

    fout.close();
}
