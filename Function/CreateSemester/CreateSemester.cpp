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
    return stoi(endDate.substr(0, 2)) > stoi(startDate.substr(0, 2));
}

bool checkSemesterExists(const std::string &semesterNumber,
                         const std::string &schoolYearName) {
    std::ifstream fin;
    readFile(fin, "Data/Semester.txt");
    std::string tmpSemesterNumber, tmpSchoolYearName;
    while (!fin.eof()) {
        getline(fin, tmpSchoolYearName);
        getline(fin, tmpSemesterNumber);
        if (tmpSchoolYearName == schoolYearName && tmpSemesterNumber == semesterNumber) {
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

Semester inputSemester() {
    Semester semester;
    Node<std::string> *allSchoolyear = getSchoolYear();

    bool checkSchoolYearExists, checkStartDate, checkEndDate, validSemesterNumber = false,
                                                              semesterExists;
    int inputSemesterNumber;
    do {
        do {
            std::cout << "Please enter school year: ";
            getline(std::cin, semester.schoolYearName);
            checkSchoolYearExists =
                schoolYearExists(allSchoolyear, semester.schoolYearName);
            if (!checkSchoolYearExists) {
                std::cout << "This school year does not exist. Please enter again!\n";
            }
        } while (!checkSchoolYearExists);

        do {
            std::cout
                << "Please enter the start date in (dd/mm/yyyy) of this school year: ";
            getline(std::cin, semester.startDate);
            checkStartDate =
                checkDate(semester.startDate) &&
                (semester.startDate.substr(6) == semester.schoolYearName.substr(0, 4));
            if (!checkStartDate) {
                std::cout << "Your input is invalid. Please enter again!\n";
            }
        } while (!checkStartDate);

        do {
            std::cout
                << "Please enter the end date in (dd/mm/yyyy) of this school year: ";
            getline(std::cin, semester.endDate);

            checkEndDate =
                checkDate(semester.endDate) &&
                checkStartBeforeEnd(semester.startDate, semester.endDate) &&
                semester.endDate.substr(6) <= semester.schoolYearName.substr(5);

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

        semesterExists = checkSemesterExists(std::to_string(inputSemesterNumber),
                                             semester.schoolYearName);
        if (!semesterExists) {
            std::cout << "This semester already exists, please try again!\n";
        }
    } while (!semesterExists);

    deleteLinkedList(allSchoolyear);
    return semester;
}

void saveSemester(const Semester &semester) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt", std::ios::app);
    fout << semester.schoolYearName << '\n'
         << semester.number << '\n'
         << semester.startDate << '\n'
         << semester.endDate << '\n';
    fout.close();
}

void createSemester() {
    Semester semester = inputSemester();
    saveSemester(semester);
}
