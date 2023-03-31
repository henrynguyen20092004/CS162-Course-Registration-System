#ifndef SCORE_H
#define SCORE_H

#include <iostream>

#include "Student_Course.h"

struct Score {
    Student_Course student_course;
    std::string studentFullName;
    double otherMark, midtermMark, finalMark, totalMark;
};

inline bool operator==(const Score &firstScore, const Score &secondScore) {
    return firstScore.student_course == secondScore.student_course &&
           firstScore.otherMark == secondScore.otherMark &&
           firstScore.midtermMark == secondScore.midtermMark &&
           firstScore.finalMark == secondScore.finalMark &&
           firstScore.totalMark == secondScore.totalMark;
}

#endif
