#ifndef SCORE_H
#define SCORE_H

#include <iostream>

#include "StudentCourse.h"

struct Score {
    StudentCourse studentCourse;
    std::string studentFullName;
    double otherMark, midtermMark, finalMark, totalMark;
};

#endif
