#ifndef INPUT_AND_VALIDATE_SEMESTER_H
#define INPUT_AND_VALIDATE_SEMESTER_H

#include "../../../Struct/LinkedList.h"
#include "../../../Struct/Semester.h"

void inputSemesterSchoolYearAndNumber(Semester &semester);
void inputSemesterDates(Semester &semester);
void validateSemesterSchoolYearAndNumber(
    Node<Semester> *allSemesters, Node<std::string> *allSchoolYears,
    const Semester &semester, bool checkSemesterAlreadyExists
);
void validateSemesterDates(const Semester &semester);

#endif
