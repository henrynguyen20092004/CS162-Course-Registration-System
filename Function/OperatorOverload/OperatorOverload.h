#ifndef OPERATOR_OVERLOAD_H
#define OPERATOR_OVERLOAD_H

#include "../../Struct/Course.h"
#include "../../Struct/Score.h"
#include "../../Struct/Student.h"
#include "../../Struct/StudentCourse.h"

bool operator==(const Student &firstStudent, const Student &secondStudent);
bool operator==(const Score &firstScore, const Score &secondScore);
bool operator==(
    const StudentCourse &firstStudentCourse, const StudentCourse &secondStudentCourse
);
bool operator<(const Student &firstStudent, const Student &secondStudent);
bool operator<(const Course &firstCourse, const Course &secondCourse);

#endif
