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

bool compareDate(const std::string &firstDate, const std::string &secondDate) {
    if (stoi(secondDate.substr(6)) != stoi(firstDate.substr(6))) {
        return stoi(secondDate.substr(6)) > stoi(firstDate.substr(6));
    }

    if (stoi(secondDate.substr(3, 5)) != stoi(firstDate.substr(3, 5))) {
        return stoi(secondDate.substr(3, 5)) > stoi(firstDate.substr(3, 5));
    }

    return stoi(secondDate.substr(0, 2)) > stoi(firstDate.substr(0, 2));
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
        semester.number = static_cast<SemesterNumber>(stoi(semesterNumber));
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

bool checkDateBeforeAddToList(
    Node<Semester> *allSemester, const Semester &semester
) {
    Node<Semester> *prev = nullptr;

    if (!allSemester) {
        return true;
    }

    while (allSemester) {
        if (allSemester->data.schoolYearName == semester.schoolYearName) {
            if (allSemester->data.number > semester.number) {
                return compareDate(
                    semester.endDate, allSemester->data.startDate
                );
            } else {
                if (allSemester->next &&
                    allSemester->next->data.schoolYearName !=
                        allSemester->data.schoolYearName) {
                    return compareDate(
                        allSemester->data.endDate, semester.startDate
                    );
                } else {
                    return allSemester->next
                               ? compareDate(
                                     allSemester->data.endDate,
                                     semester.startDate
                                 ) &&
                                     compareDate(
                                         semester.endDate,
                                         allSemester->next->data.startDate
                                     )
                               : compareDate(
                                     prev->data.endDate, semester.startDate
                                 );
                }
            }
        }

        prev = allSemester;
        allSemester = allSemester->next;
    }

    return compareDate(prev->data.endDate, semester.startDate);
}

void addSemseterToList(
    Node<Semester> *&allSemester, const Semester &newSemester
) {
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
    Node<Semester> *allSemester, const SemesterNumber &semesterNumber,
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
    Node<std::string> *allSchoolyear = getSchoolYear();
    bool checkSchoolYearExists, checkStartDate, checkEndDate,
        validSemesterNumber = false, checkDateBeforeInsert;
    int inputSemesterNumber;
    getAllSemester(allSemester);

    do {
        do {
            std::cout << "Please enter the school year: ";
            getline(std::cin, semester.schoolYearName);
            checkSchoolYearExists =
                schoolYearExists(allSchoolyear, semester.schoolYearName);

            if (!checkSchoolYearExists) {
                std::cout
                    << "This school year does not exist. Please try again!\n";
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
                    std::cout << "Invalid semester, please try again!\n";
                }
            } catch (std::exception &error) {
                std::cout << error.what() << '\n';
            }
        } while (!validSemesterNumber);

        if (checkSemesterExists(
                allSemester, semester.number, semester.schoolYearName
            )) {
            std::cout << "This semester already exists, please try again!\n";
            continue;
        }

        do {
            std::cout << "Please enter the start date (dd/mm/yyyy) of this "
                         "semester: ";
            getline(std::cin, semester.startDate);
            checkStartDate = checkDate(semester.startDate) &&
                             (semester.startDate.substr(6) >=
                                  semester.schoolYearName.substr(0, 4) &&
                              semester.startDate.substr(6) <=
                                  semester.schoolYearName.substr(5));

            if (!checkStartDate) {
                std::cout << "Invalid start date, please try again!\n";
            }
        } while (!checkStartDate);

        do {
            std::cout << "Please enter the end date (dd/mm/yyyy) of this "
                         "semester: ";
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
            std::cout << "Your start/end date can't overlap other semesters, "
                         "please try again!\n";
        }
    } while (!checkDateBeforeInsert);

    addSemseterToList(allSemester, semester);
    deleteLinkedList(allSchoolyear);
    return semester;
}

void saveSemester(Node<Semester> *allSemester) {
    std::ofstream fout;
    writeFile(fout, "Data/Semester.txt");

    while (allSemester) {
        fout << allSemester->data.schoolYearName << '\n';
        fout << allSemester->data.number << '\n';
        fout << allSemester->data.startDate << '\n';
        fout << allSemester->data.endDate;
        fout << '\n';
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
