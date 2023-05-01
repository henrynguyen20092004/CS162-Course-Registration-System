#ifndef COURSE_H
#define COURSE_H

#include <string>

struct Course {
    std::string id, name, className, teacherName, dayOfWeek, schoolYearName;
    int credits, maxStudent, sessionNumber, semesterNumber;
};

#endif
