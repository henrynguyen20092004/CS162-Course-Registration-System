#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>

#include "Semester.h"

enum Gender {
    MALE,
    FEMALE,
};

struct Student {
    std::string id, firstName, lastName, dateOfBirth, socialID, className,
        schoolYearName;
    int ordinalNumber;
    Gender gender;
    SemesterNumber semesterNumber;
};

#endif
