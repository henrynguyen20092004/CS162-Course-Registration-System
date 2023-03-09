#ifndef SCORE_H
#define SCORE_H

#include <string>

struct Score {
    std::string studentID, studentFullName, courseID;
    int ordinalNumber;
    float otherMark, midtermMark, finalMark, totalMark;
};

#endif
