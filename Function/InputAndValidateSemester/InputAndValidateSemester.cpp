#include "InputAndValidateSemester.h"

#include "../Check/CheckSchoolYear/CheckSchoolYear.h"
#include "../Check/CheckSemester/CheckSemester.h"
#include "../DateFunction/DateFunction.h"
#include "../Input/Input.h"

void inputSemesterSchoolYearAndNumber(Semester &semester) {
    std::cout << "Please enter the school year of this semester (yyyy-yyyy): ";
    getline(std::cin, semester.schoolYearName);
    std::cout << "Please choose the semester (1-3): ";
    semester.number = intInput();
}

void inputSemesterDates(Semester &semester) {
    std::cout << "Please enter the start date (dd/mm/yyyy) of this semester: ";
    getline(std::cin, semester.startDate);
    std::cout << "Please enter the end date (dd/mm/yyyy) of this semester: ";
    getline(std::cin, semester.endDate);
}

void validateSemesterSchoolYearAndNumber(
    Node<Semester> *allSemesters, Node<std::string> *allSchoolYears,
    const Semester &semester, bool checkSemesterAlreadyExists
) {
    if (!checkValidSchoolYear(semester.schoolYearName)) {
        throw std::invalid_argument("Invalid school year, please try again!\n");
    }

    if (!checkSchoolYearExists(allSchoolYears, semester.schoolYearName)) {
        throw std::invalid_argument("This school year doesn't exist, please try again!\n"
        );
    }

    if (semester.number < 1 || semester.number > 3) {
        throw std::invalid_argument("Invalid semester, please try again!\n");
    }

    if (checkSemesterExists(allSemesters, semester.number, semester.schoolYearName) ==
        checkSemesterAlreadyExists) {
        if (checkSemesterAlreadyExists) {
            throw std::invalid_argument(
                "This semester already exists, please try again!\n"
            );
        } else {
            throw std::invalid_argument(
                "This semester does not exist, please try again!\n"
            );
        }
    }
}

void validateSemesterDates(const Semester &semester) {
    if (!checkDate(semester.startDate) ||
        semester.startDate.substr(6) < semester.schoolYearName.substr(0, 4) ||
        semester.startDate.substr(6) > semester.schoolYearName.substr(5)) {
        throw std::invalid_argument("Invalid start date, please try again!\n");
    }

    if (!checkDate(semester.endDate) ||
        semester.endDate.substr(6) < semester.schoolYearName.substr(0, 4) ||
        semester.endDate.substr(6) > semester.schoolYearName.substr(5)) {
        throw std::invalid_argument("Invalid end date, please try again!\n");
    }
}
