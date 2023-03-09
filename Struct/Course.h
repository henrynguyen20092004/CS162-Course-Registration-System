#ifndef COURSE_H
#define COURSE_H

#include <string>

enum DayOfWeek {
    MON,
    TUE,
    WED,
    THU,
    FRI,
    SAT,
};

enum SessionNumber {
    SESSION1 = 1,
    SESSION2 = 2,
    SESSION3 = 3,
    SESSION4 = 4,
};

struct Course {
    std::string id, name, className, teacherName;
    int credits, maxStudent;
    DayOfWeek dayOfWeek;
    SessionNumber sessionNumber;
};

#endif
