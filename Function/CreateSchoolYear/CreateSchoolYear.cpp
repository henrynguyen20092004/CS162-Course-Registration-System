#include "CreateSchoolYear.h"

#include "../CheckSchoolYear/CheckSchoolYear.h"
#include "../OpenFile/OpenFile.h"

std::string inputSchoolYearName() {
    bool validSchoolYear, schoolYearExists = true;
    std::string schoolYearName;
    Node<std::string> *allSchoolYears = getAllSchoolYears();

    do {
        std::cout << "Please enter the school year (yyyy-yyyy): ";
        getline(std::cin, schoolYearName);

        validSchoolYear = checkValidSchoolYear(schoolYearName);

        if (!validSchoolYear) {
            std::cout << "Invalid school year, please try again!\n";
        } else {
            schoolYearExists = checkSchoolYearExists(allSchoolYears, schoolYearName);

            if (schoolYearExists) {
                std::cout << "This school year already exists, please try again!\n";
            }
        }
    } while (!validSchoolYear || schoolYearExists);

    deleteLinkedList(allSchoolYears);
    return schoolYearName;
}

void saveSchoolYear(const std::string &schoolYearName) {
    std::ofstream fout;
    writeFile(fout, "Data/SchoolYear.txt", std::ios::app);
    fout << schoolYearName << '\n';
    fout.close();
}

void createSchoolYear() {
    std::string schoolYearName = inputSchoolYearName();
    saveSchoolYear(schoolYearName);
}
