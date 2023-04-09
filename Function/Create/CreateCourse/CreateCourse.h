#ifndef CREATE_COURSE_H
#define CREATE_COURSE_H

#include "../../../Struct/Semester.h"

void createCourse(
    const Semester &semester, char *&courseID, char *&className, char *&courseName,
    char *&teacherName, char *&credits, char *&maxStudent, char *&dayOfWeek,
    char *&sessionNumbe
);

#endif
