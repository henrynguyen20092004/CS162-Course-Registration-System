#include "CreateSemester.h"

#include <algorithm>

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
void getALLSemester(Node<Semester> *&pHead) {
    Semester semester;
    std::ifstream fin;
    readFile(fin, "Data/Semester.txt");
    std::string tmpSemesterNumber;
    Node<Semester> *cur = nullptr;
    while (!fin.eof()) {
        fin >> semester.schoolYearName;
        if (semester.schoolYearName == " ") {
            break;
        }
        fin >> tmpSemesterNumber;
        semester.number = static_cast<SemesterNumber>(std::stoi(tmpSemesterNumber));
        fin >> semester.startDate;
        fin >> semester.endDate;
        Node<Semester> *tmp = new Node(semester);
        if (pHead == nullptr) {
            pHead = tmp;
            cur = pHead;
        } else {
            cur->next = tmp;
            cur = cur->next;
        }
    }
    cur->next = NULL;
    fin.close();
}
void AddtNewSemseterToSortedLinkedList(Node<Semester> *&pHead,
                                       const Semester &NewSemester) {
    getALLSemester(pHead);
    if (!pHead) {
        pHead = new Node(NewSemester);
        return;
    }
    Node<Semester> *cur = pHead;
    Node<Semester> *prev = nullptr;
    while (cur && (cur->data.schoolYearName < NewSemester.schoolYearName)) {
        prev = cur;
        cur = cur->next;
    }

    while (cur && (cur->data.number < NewSemester.number)) {
        prev = cur;
        cur = cur->next;
    }
    Node<Semester> *newNode = new Node(NewSemester);
    if (!prev) {
        pHead = newNode;
        pHead->next = cur;
    } else {
        newNode->next = cur;
        prev->next = newNode;
    }
}
bool checkSemesterExists(const std::string &semesterNumber,
                         const std::string &schoolYearName) {
      std::ifstream fin;
    readFile(fin, "Data/Semester.txt");
    std::string tmpSemesterNumber, tmpSchoolYearName;
    while (fin.good()) {
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

Semester inputSemester(Node<Semester> *&getAllSemester) {
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

    AddtNewSemseterToSortedLinkedList(getAllSemester, semester);

    deleteLinkedList(allSchoolyear);
    return semester;
}

void saveSemester(Node<Semester> *getAllSemester) {
    std::ofstream fout;
    fout.open("Data/Semester.txt", std::ios::trunc);
    while (getAllSemester) {
        fout << getAllSemester->data.schoolYearName << '\n';
        fout << getAllSemester->data.number << '\n';
        fout << getAllSemester->data.startDate << '\n';
        fout << getAllSemester->data.endDate << '\n';
        getAllSemester = getAllSemester->next;
    }
    deleteLinkedList(getAllSemester);
    fout.close();
}

void createSemester() {
    Node<Semester> *getAllSemester = nullptr;
    Semester semester = inputSemester(getAllSemester);
    saveSemester(getAllSemester);
}
