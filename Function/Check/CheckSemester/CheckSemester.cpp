#include "CheckSemester.h"

bool checkSemesterExists(
    Node<Semester> *allSemester, int semesterNumber, const std::string &schoolYearName
) {
    while (allSemester) {
        if (allSemester->data.number == semesterNumber &&
            allSemester->data.schoolYearName == schoolYearName) {
            return true;
        }

        allSemester = allSemester->next;
    }

    return false;
}
