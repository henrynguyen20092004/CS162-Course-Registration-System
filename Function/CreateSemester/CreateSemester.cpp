#include "CreateSemester.h"

#include "../CheckDate/CheckDate.h"
#include "../GetAllSchoolYears/GetAllSchoolYears.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

bool schoolYearExists(Node<std::string> *allSchoolyear,
                      const std::string &schoolYearName) {
    while (allSchoolyear) {
        if (allSchoolyear->data == schoolYearName) {
            return true;
        }
        allSchoolyear = allSchoolyear->next;
    }
    return false;
}

bool checkStartBeforeEnd(const std::string &startDate, const std::string &endDate) {
    if (stoi(endDate.substr(6)) < stoi(startDate.substr(6))) {
        return false;
    }
    if (stoi(endDate.substr(3, 5)) < stoi(startDate.substr(3, 5))) {
        return false;
    }
    return true;
}

Semester inputSemester(Node<std::string> *&allSchoolyear) {
    Semester semester;
    allSchoolyear = getSchoolYear();

    bool checkSchoolYearExists, checkStartDate, checkEndDate, validSemesterNumber = false;
    int inputSemesterNumber;

    do {
        std::cout << "Please enter school year: ";
        getline(std::cin, semester.schoolYearName);
        checkSchoolYearExists = schoolYearExists(allSchoolyear, semester.schoolYearName);
        if (!checkSchoolYearExists) {
            std::cout << "This school year does not exist. Please enter again!\n";
        }
    } while (!checkSchoolYearExists);

    do {
        std::cout << "Please enter the start date in (dd/mm/yyyy) of this school year: ";
        getline(std::cin, semester.startDate);
        checkStartDate = checkDate(semester.startDate);
        if (!checkStartDate) {
            std::cout << "Your input is invalid. Please enter again!\n";
        }
    } while (!checkStartDate);

    do {
        std::cout << "Please enter the end date in (dd/mm/yyyy) of this school year: ";
        getline(std::cin, semester.endDate);
        checkEndDate = checkDate(semester.endDate) &&
                       checkStartBeforeEnd(semester.startDate, semester.endDate);
        if (!checkEndDate) {
            std::cout << "Your input is invalid. Please enter again!\n";
        }
    } while (!checkEndDate);

    do {
        try {
            std::cout << "Please choose the semester (1-3): ";
            inputSemesterNumber = intInput();
            validSemesterNumber = inputSemesterNumber > 0 && inputSemesterNumber <= 3;
            if (validSemesterNumber) {
                semester.number = static_cast<SemesterNumber>(inputSemesterNumber);
            } else {
                std::cout << "Invalid semester, please enter again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what() << '\n';
        }
    } while (!validSemesterNumber);
    return semester;
}

void saveSemester(const Semester &semester) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt", std::ios::app);
    fout << semester.schoolYearName << '\n'
         << semester.startDate << '\n'
         << semester.endDate << '\n'
         << semester.number << '\n';
    fout.close();
}

void createSemester() {
    Node<std::string> *allSchoolYear = nullptr;
    Semester semester = inputSemester(allSchoolYear);
    deleteLinkedList(allSchoolYear);
    saveSemester(semester);
}
