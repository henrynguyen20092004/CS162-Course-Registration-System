#include "CheckSemester.h"

bool checkSemesterExists(
    Node<Semester> *allSemester, int semesterNumber, const std::string &schoolYearName
) {
    for (; allSemester; allSemester = allSemester->next) {
        Semester semester = allSemester->data;

        if (semester.number == semesterNumber &&
            semester.schoolYearName == schoolYearName) {
            return true;
        }
    }

    return false;
}
