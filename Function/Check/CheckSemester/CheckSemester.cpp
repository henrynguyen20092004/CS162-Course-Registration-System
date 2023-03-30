#include "CheckSemester.h"

bool checkSemesterExists(
    Node<Semester> *allSemesters, int semesterNumber, const std::string &schoolYearName
) {
    for (; allSemesters; allSemesters = allSemesters->next) {
        Semester semester = allSemesters->data;

        if (semester.number == semesterNumber &&
            semester.schoolYearName == schoolYearName) {
            return true;
        }
    }

    return false;
}
