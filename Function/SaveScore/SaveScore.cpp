#include "SaveScore.h"

#include "../OpenFile/OpenFile.h"

void saveScores(Node<Score> *allScores) {
    std::ofstream fout;
    writeFile(fout, "Data/Score.txt");

    for (; allScores; allScores = allScores->next) {
        Score score = allScores->data;
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
