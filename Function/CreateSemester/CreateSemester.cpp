#include "CreateSemester.h"

#include "../Check/CheckSchoolYear/CheckSchoolYear.h"
#include "../Check/CheckSemester/CheckSemester.h"
#include "../DateFunction/DateFunction.h"
#include "../GetAll/GetAllSchoolYears/GetAllSchoolYears.h"
#include "../GetAll/GetAllSemesters/GetAllSemesters.h"
#include "../Input/Input.h"

bool checkDateBeforeAddToList(Node<Semester> *allSemesters, const Semester &semester) {
    if (!allSemesters) {
        return true;
    }

    Semester curSemester;
    Node<Semester> *tmp = allSemesters;

    for (; allSemesters; allSemesters = allSemesters->next) {
        curSemester = allSemesters->data;

        if (curSemester.schoolYearName == semester.schoolYearName) {
            if (curSemester.number > semester.number) {
                return compareDate(semester.endDate, curSemester.startDate);
            }

            while (allSemesters->next &&
                   allSemesters->next->data.schoolYearName == semester.schoolYearName &&
                   allSemesters->next->data.number < semester.number) {
                allSemesters = allSemesters->next;
            }

            return compareDate(curSemester.endDate, semester.startDate) &&
                   (allSemesters->next
                        ? compareDate(
                              semester.endDate, allSemesters->next->data.startDate
                          )
                        : true);
        }
    }

    while (tmp->next && tmp->next->data.schoolYearName < semester.schoolYearName) {
        tmp = tmp->next;
    }

    curSemester = tmp->data;

    return curSemester.schoolYearName < semester.schoolYearName
               ? compareDate(curSemester.endDate, semester.startDate)
               : compareDate(semester.endDate, curSemester.startDate);
}

void addSemseterToList(Node<Semester> *&allSemesters, const Semester &newSemester) {
    Node<Semester> *newNode = new Node(newSemester);

    if (!allSemesters) {
        allSemesters = newNode;
        return;
    }

    Node<Semester> *cur = allSemesters, *prev = nullptr;

    while (cur && cur->data.schoolYearName < newSemester.schoolYearName) {
        prev = cur;
        cur = cur->next;
    }

    while (cur && cur->data.schoolYearName <= newSemester.schoolYearName &&
           cur->data.number < newSemester.number) {
        prev = cur;
        cur = cur->next;
    }

    if (!prev) {
        allSemesters = newNode;
        allSemesters->next = cur;
    } else {
        newNode->next = cur;
        prev->next = newNode;
    }
}

void validateSemester(
    Node<Semester> *allSemesters, Node<std::string> *allSchoolYears,
    const Semester &semester
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

    if (checkSemesterExists(allSemesters, semester.number, semester.schoolYearName)) {
        throw std::invalid_argument("This semester already exists, please try again!\n");
    }

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

    if (!checkDateBeforeAddToList(allSemesters, semester)) {
        throw std::invalid_argument(
            "Your start/end date can't overlap other semesters, please try again!\n"
        );
    }
}

void inputSemester(Semester &semester) {
    std::cout << "Please enter the school year of this semester (yyyy-yyyy): ";
    getline(std::cin, semester.schoolYearName);
    std::cout << "Please choose the semester (1-3): ";
    semester.number = intInput();
    std::cout << "Please enter the start date (dd/mm/yyyy) of this semester: ";
    getline(std::cin, semester.startDate);
    std::cout << "Please enter the end date (dd/mm/yyyy) of this semester: ";
    getline(std::cin, semester.endDate);
}

void saveSemester(Node<Semester> *allSemesters) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt");

    while (allSemesters) {
        fout << allSemesters->data.schoolYearName << '\n';
        fout << allSemesters->data.number << '\n';
        fout << allSemesters->data.startDate << '\n';
        fout << allSemesters->data.endDate << '\n';
        allSemesters = allSemesters->next;
    }

    deleteLinkedList(allSemesters);
    fout.close();
    std::cout << "Semester successfully added!\n";
}

void saveCurrentSemester(const Semester &semester) {
    std::ofstream fout;
    writeFile(fout, "Data/CurrentSemester.txt");
    fout << semester.schoolYearName << '\n';
    fout << semester.number << '\n';
    fout << semester.startDate << '\n';
    fout << semester.endDate << '\n';
    fout.close();
}

Semester createSemester() {
    Node<Semester> *allSemesters = getAllSemesters();
    Node<std::string> *allSchoolYears = getAllSchoolYears();
    Semester semester;
    bool validSemester = false;

    do {
        try {
            inputSemester(semester);
            validateSemester(allSemesters, allSchoolYears, semester);
            validSemester = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validSemester);

    addSemseterToList(allSemesters, semester);
    saveSemester(allSemesters);
    saveCurrentSemester(semester);
    deleteLinkedList(allSemesters);
    deleteLinkedList(allSchoolYears);
    return semester;
}
