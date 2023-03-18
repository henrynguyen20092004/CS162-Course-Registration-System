#include "CreateSemester.h"

#include "../CheckDate/CheckDate.h"
#include "../GetAllSchoolYears/GetAllSchoolYears.h"
#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

bool schoolYearExists(
    Node<std::string> *allSchoolyear, const std::string &schoolYearName
) {
    while (allSchoolyear) {
        if (allSchoolyear->data == schoolYearName) {
            return true;
        }
        allSchoolyear = allSchoolyear->next;
    }
    return false;
}

bool checkStartBeforeEnd(
    const std::string &startDate, const std::string &endDate
) {
    if (stoi(endDate.substr(6)) != stoi(startDate.substr(6))) {
        return stoi(endDate.substr(6)) > stoi(startDate.substr(6));
    }
    if (stoi(endDate.substr(3, 5)) != stoi(startDate.substr(3, 5))) {
        return stoi(endDate.substr(3, 5)) > stoi(startDate.substr(3, 5));
    }
    return stoi(endDate.substr(0, 2)) > stoi(startDate.substr(0, 2));
}

void getAllSemester(Node<Semester> *&pHead) {
    Semester semester;
    std::ifstream fin;
    readFile(fin, "Data/Semester.txt");
    std::string semesterNumber;
    Node<Semester> *cur = nullptr;
    while (fin.good()) {
        getline(fin, semester.schoolYearName);
        if (semester.schoolYearName == "") {
            break;
        }
        getline(fin, semesterNumber);
        semester.number =
            static_cast<SemesterNumber>(std::stoi(semesterNumber));
        getline(fin, semester.startDate);
        getline(fin, semester.endDate);
        Node<Semester> *tmp = new Node(semester);
        if (pHead == nullptr) {
            pHead = tmp;
            cur = pHead;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }
    if (cur) {
        cur->next = nullptr;
    }
    fin.close();
}

bool checkDateBeforeInsertToList(
    Node<Semester> *&allSemester, Semester insertSemester
) {
    Node<Semester> *cur = allSemester;
    while (cur) {
        if (cur->data.schoolYearName == insertSemester.schoolYearName) {
            if (cur->data.number > insertSemester.number) {
                return checkStartBeforeEnd(
                    insertSemester.endDate, cur->data.startDate
                );
            } else {
                return checkStartBeforeEnd(
                    cur->data.endDate, insertSemester.startDate
                );
            }
        }
        cur = cur->next;
    }
    return true;
}

void addNewSemseterToList(
    Node<Semester> *&allSemester, const Semester &newSemester
) {
    Node<Semester> *newNode = new Node(newSemester);
    if (!allSemester) {
        allSemester = newNode;
        return;
    }
    Node<Semester> *cur = allSemester;
    Node<Semester> *prev = nullptr;

    while (cur && cur->data.schoolYearName < newSemester.schoolYearName) {
        prev = cur;
        cur = cur->next;
    }
    while (cur && cur->data.number < newSemester.number) {
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
    const std::string &semesterNumber, const std::string &schoolYearName
) {
    std::ifstream fin;
    readFile(fin, "Data/Semester.txt");
    std::string tmpSemesterNumber, tmpSchoolYearName;
    while (fin.good()) {
        getline(fin, tmpSchoolYearName);
        getline(fin, tmpSemesterNumber);
        if (tmpSchoolYearName == schoolYearName &&
            tmpSemesterNumber == semesterNumber) {
            fin.close();
            return false;
        }
    }
    fin.close();
    return true;
}

Semester inputSemester(Node<Semester> *&allSemester) {
    Semester semester;
    Node<std::string> *allSchoolyear = getSchoolYear();
    getAllSemester(allSemester);
    bool checkSchoolYearExists, checkStartDate, checkEndDate,
        validSemesterNumber = false, semesterExists, checkDateBeforeInsert;
    int inputSemesterNumber;
    do {
        do {
            std::cout << "Please enter school year: ";
            getline(std::cin, semester.schoolYearName);
            checkSchoolYearExists =
                schoolYearExists(allSchoolyear, semester.schoolYearName);
            if (!checkSchoolYearExists) {
                std::cout
                    << "This school year does not exist. Please enter again!\n";
            }
        } while (!checkSchoolYearExists);

        do {
            try {
                std::cout << "Please choose the semester (1-3): ";
                inputSemesterNumber = intInput();

                validSemesterNumber =
                    inputSemesterNumber > 0 && inputSemesterNumber <= 3;

                if (validSemesterNumber) {
                    semester.number =
                        static_cast<SemesterNumber>(inputSemesterNumber);
                } else {
                    std::cout << "Invalid semester, please enter again!\n";
                }
            } catch (std::exception &error) {
                std::cout << error.what() << '\n';
            }
        } while (!validSemesterNumber);

        semesterExists = checkSemesterExists(
            std::to_string(inputSemesterNumber), semester.schoolYearName
        );
        if (!semesterExists) {
            std::cout << "This semester already exists, please try again!\n";
        }

        do {
            std::cout << "Please enter the start date in (dd/mm/yyyy) of this "
                         "school year: ";
            getline(std::cin, semester.startDate);
            checkStartDate = checkDate(semester.startDate) &&
                             (semester.startDate.substr(6) >=
                                  semester.schoolYearName.substr(0, 4) &&
                              semester.startDate.substr(6) <=
                                  semester.schoolYearName.substr(5));
            if (!checkStartDate) {
                std::cout << "Your input is invalid. Please enter again!\n";
            }
        } while (!checkStartDate);

        do {
            std::cout << "Please enter the end date in (dd/mm/yyyy) of this "
                         "school year: ";
            getline(std::cin, semester.endDate);

            checkEndDate =
                checkDate(semester.endDate) &&
                checkStartBeforeEnd(semester.startDate, semester.endDate) &&
                semester.endDate.substr(6) <= semester.schoolYearName.substr(5);

            if (!checkEndDate) {
                std::cout
                    << "Your input is invalid because the end date is smaller "
                       "than the start date. Please enter again!\n";
            }
        } while (!checkEndDate);
        checkDateBeforeInsert =
            checkDateBeforeInsertToList(allSemester, semester);
        if (!checkDateBeforeInsert) {
            std::cout << "Your input is invalid. Please enter again!\n";
        }
    } while (semesterExists && !checkDateBeforeInsert);

    addNewSemseterToList(allSemester, semester);

    deleteLinkedList(allSchoolyear);
    return semester;
}

void saveSemester(Node<Semester> *allSemester) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt", std::ios::ate);
    while (allSemester) {
        fout << allSemester->data.schoolYearName << '\n';
        fout << allSemester->data.number << '\n';
        fout << allSemester->data.startDate << '\n';
        fout << allSemester->data.endDate;
        if (allSemester->next != NULL) {
            fout << '\n';
        }
        allSemester = allSemester->next;
    }
    deleteLinkedList(allSemester);
    fout.close();
}

void createSemester() {
    Node<Semester> *allSemester = nullptr;
    Semester semester = inputSemester(allSemester);
    saveSemester(allSemester);
}
