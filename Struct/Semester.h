#ifndef SEMESTER_H
#define SEMESTER_H

#include <string>

enum SemesterNumber {
    SEMESTER1 = 1,
    SEMESTER2 = 2,
    SEMESTER3 = 3,
};

struct Semester {
    std::string schoolYearName, startDate, endDate;
    SemesterNumber number;
};

#endif
