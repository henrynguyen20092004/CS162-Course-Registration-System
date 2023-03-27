#ifndef CHECK_SCHOOL_YEAR_H
#define CHECK_SCHOOL_YEAR_H

#include <iostream>

#include "../../Struct/LinkedList.h"

bool checkSchoolYearExists(
    Node<std::string> *allSchoolyear, const std::string &schoolYearName
);
bool checkValidSchoolYear(const std::string &schoolYearName);

#endif
