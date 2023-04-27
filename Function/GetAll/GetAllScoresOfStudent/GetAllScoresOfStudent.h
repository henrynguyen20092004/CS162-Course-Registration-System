#ifndef GET_ALL_SCORES_OF_STUDENT_H
#define GET_ALL_SCORES_OF_STUDENT_H

#include "../../../Struct/Data.h"

Node<Score>* getAllScoresOfStudent(
    const std::string& studentID, const Semester& currentSemester
);

#endif