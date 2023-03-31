#include "CreateSchoolYear.h"

#include "../Check/CheckSchoolYear/CheckSchoolYear.h"
#include "../GetAll/GetAllSchoolYears/GetAllSchoolYears.h"

void validateSchoolYear(
    Node<std::string> *allSchoolYears, const std::string &schoolYearName
) {
    if (!checkValidSchoolYear(schoolYearName)) {
        throw std::invalid_argument("Invalid school year, please try again!\n");
    }

    if (checkSchoolYearExists(allSchoolYears, schoolYearName)) {
        throw std::invalid_argument("This school year already exists, please try again!\n"
        );
    }
}

void inputSchoolYear(std::string &schoolYearName) {
    std::cout << "Please enter the school year (yyyy-yyyy): ";
    getline(std::cin, schoolYearName);
}

void saveSchoolYear(const std::string &schoolYearName) {
    std::ofstream fout;
    writeFile(fout, "Data/SchoolYear.txt", std::ios::app);
    fout << schoolYearName << '\n';
    fout.close();
}

void createSchoolYear() {
    Node<std::string> *allSchoolYears = getAllSchoolYears();
    std::string schoolYearName;
    bool validSchoolYear = false;

    do {
        try {
            inputSchoolYear(schoolYearName);
            validateSchoolYear(allSchoolYears, schoolYearName);
            validSchoolYear = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validSchoolYear);

    saveSchoolYear(schoolYearName);
    deleteLinkedList(allSchoolYears);
    std::cout << "School year successfully added!\n";
}
