#ifndef CURRENT_SEMESTER_H
#define CURRENT_SEMESTER_H

#include "../../Struct/Semester.h"
#include "../../Struct/User.h"

Semester getCurrentSemester();
void changeCurrentSemester(Semester &currentSemester, const User &currentUser);

#endif
