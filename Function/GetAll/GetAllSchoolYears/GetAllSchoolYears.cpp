#include "GetAllSchoolYears.h"

void readSchoolYear(std::ifstream &fin, std::string &schoolYearName) {
    getline(fin, schoolYearName);
}

Node<std::string> *getAllSchoolYears() {
    return getAll("Data/SchoolYear.txt", &readSchoolYear);
}
