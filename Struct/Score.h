#ifndef SCORE_H
#define SCORE_H

#include <string>

#include "StudentCourse.h"

struct Score {
    StudentCourse studentCourse;
    std::string studentFullName;
    double otherMark = INT_MIN, midtermMark, finalMark, totalMark;
};

#endif
