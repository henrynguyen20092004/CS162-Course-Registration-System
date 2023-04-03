#ifndef SCORE_H
#define SCORE_H

#include <iostream>

#include "StudentCourse.h"

struct Score {
    StudentCourse studentCourse;
    std::string studentFullName;
    double otherMark, midtermMark, finalMark, totalMark;
};

inline bool operator==(const Score &firstScore, const Score &secondScore) {
    return firstScore.studentCourse == secondScore.studentCourse &&
           firstScore.otherMark == secondScore.otherMark &&
           firstScore.midtermMark == secondScore.midtermMark &&
           firstScore.finalMark == secondScore.finalMark &&
           firstScore.totalMark == secondScore.totalMark;
}

#endif
