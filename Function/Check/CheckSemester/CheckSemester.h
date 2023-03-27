#ifndef CHECK_COURSE_H
#define CHECK_COURSE_H

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Semester.h"

bool checkSemesterExists(
    Node<Semester> *allSemester, int semesterNumber, const std::string &schoolYearName
);

#endif
