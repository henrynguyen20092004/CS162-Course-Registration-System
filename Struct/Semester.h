#ifndef SEMESTER_H
#define SEMESTER_H

#include <iostream>

struct Semester {
    std::string schoolYearName, startDate, endDate;
    int number;

    Semester() : schoolYearName("") {}
};

#endif
