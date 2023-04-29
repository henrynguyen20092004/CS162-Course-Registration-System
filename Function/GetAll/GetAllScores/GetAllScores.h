#ifndef GET_ALL_SCORES_H
#define GET_ALL_SCORES_H

#include "../../../Struct/Score.h"
#include "../GetAll.h"

Node<Score>* getAllScores();
Node<Score>* getAllScoresOfStudentsInCourse(const std::string& course);

#endif
