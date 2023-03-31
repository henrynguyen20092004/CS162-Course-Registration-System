#include "CheckSchoolYear.h"

bool checkSchoolYearExists(
    Node<std::string> *allSchoolyear, const std::string &schoolYearName
) {
    for (; allSchoolyear; allSchoolyear = allSchoolyear->next) {
        if (allSchoolyear->data == schoolYearName) {
            return true;
        }
    }

    return false;
}

bool checkValidSchoolYear(const std::string &schoolYearName) {
    int length = schoolYearName.length();

    if (length != 9) {
        return false;
    }

    for (int i = 0; i < 9; ++i) {
        if (i == 4) {
            if (schoolYearName[i] != '-') {
                return false;
            }
        } else if (!isdigit(schoolYearName[i])) {
            return false;
        }
    }

    int startYear = stoi(schoolYearName), endYear = stoi(schoolYearName.substr(5, 4));
    return endYear - startYear == 1 && startYear > 999 && endYear < 10000;
}
