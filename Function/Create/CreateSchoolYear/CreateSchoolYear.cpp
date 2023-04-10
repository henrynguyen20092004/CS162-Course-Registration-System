#include "CreateSchoolYear.h"

#include "../../../Struct/Data.h"
#include "../../Check/CheckSchoolYear/CheckSchoolYear.h"

void validateSchoolYear(
    Node<std::string> *allSchoolYears, const std::string &schoolYearName
) {
    if (!checkValidSchoolYear(schoolYearName)) {
        throw std::invalid_argument("Invalid school year, please try again!");
    }

    if (checkSchoolYearExists(allSchoolYears, schoolYearName)) {
        throw std::invalid_argument("This school year already exists, please try again!");
    }
}

void saveSchoolYear(const std::string &schoolYearName) {
    std::ofstream fout;
    writeFile(fout, "Data/SchoolYear.txt", std::ios::app);
    fout << schoolYearName << '\n';
    fout.close();
    addNewItemsToOldList(allData.allSchoolYears, new Node(schoolYearName));
}

void createSchoolYear(char *inputedSchoolYear) {
    std::string schoolYearName = inputedSchoolYear;
    validateSchoolYear(allData.allSchoolYears, schoolYearName);
    saveSchoolYear(schoolYearName);
    std::cout << "School year successfully added!\n";
}
