#include "CreateSemester.h"

#include <fstream>
#include <iostream>

#include "../../Struct/LinkedList.h"
#include "../../Struct/SchoolYear.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

Node<SchoolYear> *getSchoolYear() {
    std::ifstream fin;
    readFile(fin, "Data/SchoolYear.txt");
    SchoolYear schoolYear;
    Node<SchoolYear> *result = nullptr, *cur = nullptr;
    while (!fin.eof()) {
        fin >> schoolYear.name;
        Node<SchoolYear> *tmp = new Node(schoolYear);
        if (result == nullptr) {
            result = tmp;
            cur = result;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }
    fin.close();
    return result;
}

bool exitSchoolYear(const std::string FindschoolYear, Node<SchoolYear> *allSchoolyear) {
    while (allSchoolyear) {
        if (allSchoolyear->data.name == FindschoolYear) {
            return true;
        }
        allSchoolyear = allSchoolyear->next;
    }
    return false;
}

bool checkLeapYear(int year) {
    return year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0));
}

bool checkDayMonthYear(std::string date) {
    int day = stoi(date.std::string::substr(0, 2));
    int month = stoi(date.std::string::substr(3, 5));
    int year = stoi(date.std::string::substr(6));
    if (day < 1) {
        return false;
    }
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: {
            return day < 32;
        }
        case 2: {
            return checkLeapYear(year) ? day < 30 : day < 29;
        }
        case 4:
        case 6:
        case 9:
        case 11: {
            return day < 31;
        }
    }
    return false;
}

bool checkDate(std::string date) {
    if (date.size() != 10) {
        return false;
    }

    if ((date[2] != '/' && date[2] != '-') || (date[5] != '/' && date[5] != '-')) {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) {
            continue;
        }
        if (!isdigit(date[i])) {
            return false;
        }
    }

    return checkDayMonthYear(date);
}

Semester inputSemester(Node<SchoolYear> *allSchoolyear) {
    Semester semester;
    allSchoolyear = getSchoolYear();
    bool checkExitSchoolyear = false;
    do {
        std::cout << "Enter school year: ";
        std::cin >> semester.schoolYearName;
        if (!exitSchoolYear(semester.schoolYearName, allSchoolyear)) {
            std::cout << "This school year does not exist. Please enter again!\n";
        } else {
            checkExitSchoolyear = true;
        }
    } while (!checkExitSchoolyear);

    bool checkStartDate = false;
    do {
        std::cout << "Enter the start date in (dd/mm/yyyy) of this school year: ";
        std::cin >> semester.startDate;
        if (!checkDate(semester.startDate)) {
            std::cout << "Your input is invalid. Please enter again!\n";
        } else {
            checkStartDate = true;
        }
    } while (!checkStartDate);

    bool checkEndDate = false;
    do {
        std::cout << "Enter the end date in (dd/mm/yyyy) of this school year: ";
        std::cin >> semester.endDate;
        if (!checkDate(semester.endDate)) {
            std::cout << "Your input is invalid. Please enter again!\n";
        } else {
            checkEndDate = true;
        }
    } while (!checkEndDate);

    int inputSemesterNumber;
    std::cin.ignore();

    do {
        std::cout << "Please choose the semester (1-3): ";
        inputSemesterNumber = intInput();
        if (inputSemesterNumber > 0 && inputSemesterNumber <= 3) {
            semester.number = static_cast<SemesterNumber>(inputSemesterNumber);
        } else {
            std::cout << "Invalid semester, please enter again!\n";
        }
    } while (inputSemesterNumber > 3 || inputSemesterNumber <= 0);

    return semester;
}

void saveSemester(const Semester semester) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt");
    fout << semester.schoolYearName << '\n'
         << semester.startDate << '\n'
         << semester.endDate << '\n'
         << semester.number << '\n';
    fout.close();
}

void createSemester() {
    Node<SchoolYear> *allSchoolYear = nullptr;
    Semester semester = inputSemester(allSchoolYear);
    saveSemester(semester);
    deleteLinkedList(allSchoolYear);
}
