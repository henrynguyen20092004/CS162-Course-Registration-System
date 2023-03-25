#include "CreateSemester.h"

#include "../CheckDate/CheckDate.h"
#include "../CheckSchoolYear/CheckSchoolYear.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

bool compareDate(const std::string &firstDate, const std::string &secondDate) {
    if (stoi(secondDate.substr(6)) != stoi(firstDate.substr(6))) {
        return stoi(secondDate.substr(6)) > stoi(firstDate.substr(6));
    }

    if (stoi(secondDate.substr(3, 5)) != stoi(firstDate.substr(3, 5))) {
        return stoi(secondDate.substr(3, 5)) > stoi(firstDate.substr(3, 5));
    }

    return stoi(secondDate.substr(0, 2)) > stoi(firstDate.substr(0, 2));
}

Node<Semester> *getAllSemester() {
    Semester semester;
    std::ifstream fin;
    readFile(fin, "Data/Semester.txt");
    std::string semesterNumber;
    Node<Semester> *allSemester = nullptr, *cur = nullptr;

    while (fin.good()) {
        getline(fin, semester.schoolYearName);

        if (semester.schoolYearName == "") {
            break;
        }

        getline(fin, semesterNumber);
        semester.number = stoi(semesterNumber);
        getline(fin, semester.startDate);
        getline(fin, semester.endDate);
        Node<Semester> *tmp = new Node(semester);

        if (!allSemester) {
            allSemester = tmp;
            cur = allSemester;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }

    fin.close();
    return allSemester;
}

bool checkDateBeforeAddToList(Node<Semester> *allSemester, const Semester &semester) {
    if (!allSemester) {
        return true;
    }

    Node<Semester> *tmp = allSemester;

    while (allSemester) {
        if (allSemester->data.schoolYearName == semester.schoolYearName) {
            if (allSemester->data.number > semester.number) {
                return compareDate(semester.endDate, allSemester->data.startDate);
            }

            while (allSemester->next &&
                   allSemester->next->data.schoolYearName == semester.schoolYearName &&
                   allSemester->next->data.number < semester.number) {
                allSemester = allSemester->next;
            }

            return compareDate(allSemester->data.endDate, semester.startDate) &&
                   (allSemester->next
                        ? compareDate(semester.endDate, allSemester->next->data.startDate)
                        : true);
        }

        allSemester = allSemester->next;
    }

    while (tmp->next && tmp->next->data.schoolYearName < semester.schoolYearName) {
        tmp = tmp->next;
    }

    return tmp->data.schoolYearName < semester.schoolYearName
               ? compareDate(tmp->data.endDate, semester.startDate)
               : compareDate(semester.endDate, tmp->data.startDate);
}

void addSemseterToList(Node<Semester> *&allSemester, const Semester &newSemester) {
    Node<Semester> *newNode = new Node(newSemester);

    if (!allSemester) {
        allSemester = newNode;
        return;
    }

    Node<Semester> *cur = allSemester, *prev = nullptr;

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
        allSemester = newNode;
        allSemester->next = cur;
    } else {
        newNode->next = cur;
        prev->next = newNode;
    }
}

bool checkSemesterExists(
    Node<Semester> *allSemester, const int &semesterNumber,
    const std::string &schoolYearName
) {
    while (allSemester) {
        if (allSemester->data.number == semesterNumber &&
            allSemester->data.schoolYearName == schoolYearName) {
            return true;
        }

        allSemester = allSemester->next;
    }

    return false;
}

Semester inputSemester(Node<Semester> *&allSemester) {
    Semester semester;
    bool validSchoolYear, schoolYearExists = true, checkStartDate, checkEndDate,
                          validSemesterNumber = false, checkDateBeforeInsert;
    int inputSemesterNumber;
    allSemester = getAllSemester();
    Node<std::string> *allSchoolYears = getAllSchoolYears();

    do {
        do {
            std::cout << "Please enter the school year of this semester (yyyy-yyyy): ";
            getline(std::cin, semester.schoolYearName);

            validSchoolYear = checkValidSchoolYear(semester.schoolYearName);

            if (!validSchoolYear) {
                std::cout << "Invalid school year, please try again!\n";
            } else {
                schoolYearExists =
                    checkSchoolYearExists(allSchoolYears, semester.schoolYearName);

                if (!schoolYearExists) {
                    std::cout << "This school year doesn't exist, please try again!\n";
                }
            }
        } while (!validSchoolYear || !schoolYearExists);

        do {
            try {
                std::cout << "Please choose the semester (1-3): ";
                inputSemesterNumber = intInput();

                validSemesterNumber = inputSemesterNumber > 0 && inputSemesterNumber <= 3;

                if (validSemesterNumber) {
                    semester.number = inputSemesterNumber;
                } else {
                    std::cout << "Invalid semester, please try again!\n";
                }
            } catch (std::exception &error) {
                std::cout << error.what() << '\n';
            }
        } while (!validSemesterNumber);

        if (checkSemesterExists(allSemester, semester.number, semester.schoolYearName)) {
            std::cout << "This semester already exists, please try again!\n";
            continue;
        }

        do {
            std::cout << "Please enter the start date (dd/mm/yyyy) of this semester: ";
            getline(std::cin, semester.startDate);
            checkStartDate =
                checkDate(semester.startDate) &&
                (semester.startDate.substr(6) >= semester.schoolYearName.substr(0, 4) &&
                 semester.startDate.substr(6) <= semester.schoolYearName.substr(5));

            if (!checkStartDate) {
                std::cout << "Invalid start date, please try again!\n";
            }
        } while (!checkStartDate);

        do {
            std::cout << "Please enter the end date (dd/mm/yyyy) of this semester: ";
            getline(std::cin, semester.endDate);

            checkEndDate =
                checkDate(semester.endDate) &&
                compareDate(semester.startDate, semester.endDate) &&
                semester.endDate.substr(6) <= semester.schoolYearName.substr(5);

            if (!checkEndDate) {
                std::cout << "Invalid end date, please try again!\n";
            }
        } while (!checkEndDate);

        checkDateBeforeInsert = checkDateBeforeAddToList(allSemester, semester);

        if (!checkDateBeforeInsert) {
            std::cout << "Your start/end date can't overlap other semesters, please try "
                         "again!\n";
        }
    } while (!checkDateBeforeInsert);

    deleteLinkedList(allSchoolYears);
    return semester;
}

void saveSemester(Node<Semester> *allSemester) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt");

    while (allSemester) {
        fout << allSemester->data.schoolYearName << '\n';
        fout << allSemester->data.number << '\n';
        fout << allSemester->data.startDate << '\n';
        fout << allSemester->data.endDate << '\n';
        allSemester = allSemester->next;
    }

    deleteLinkedList(allSemester);
    fout.close();
}

Semester createSemester() {
    Node<Semester> *allSemester = nullptr;
    Semester semester = inputSemester(allSemester);
    addSemseterToList(allSemester, semester);
    saveSemester(allSemester);
    return semester;
}
