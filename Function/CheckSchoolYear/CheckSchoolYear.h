#ifndef CHECK_SCHOOL_YEAR_H
#define CHECK_SCHOOL_YEAR_H

#include "../GetAllSchoolYears/GetAllSchoolYears.h"

bool checkSchoolYearExists(
    Node<std::string> *allSchoolyear, const std::string &schoolYearName
);
bool checkValidSchoolYear(const std::string &schoolYearName);

#endif
