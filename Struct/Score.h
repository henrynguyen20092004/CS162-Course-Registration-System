#ifndef SCORE_H
#define SCORE_H

#include <iostream>

#include "Student_Course.h"

struct Score {
    Student_Course student_course;
    std::string studentFullName;
    double otherMark, midtermMark, finalMark, totalMark;
};

#endif
