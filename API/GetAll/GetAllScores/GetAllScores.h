#ifndef GET_ALL_SCORES_H
#define GET_ALL_SCORES_H

#include "../../../Struct/Score.h"
#include "../../../Struct/Semester.h"
#include "../../../Struct/Student.h"
#include "../GetAll.h"

Node<Score>* getAllScores();
Node<Score>* getAllScoresOfStudentsInCourse(const std::string& course);
Node<Score>* getAllScoresOfClass(Node<Student>* allStudentsInClass);
Node<Score>* getAllScoresOfCurrentStudent();

#endif
