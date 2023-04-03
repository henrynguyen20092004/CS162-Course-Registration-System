#include "CreateSemester.h"

#include "../../DateFunction/DateFunction.h"
#include "../../GetAll/GetAllSchoolYears/GetAllSchoolYears.h"
#include "../../GetAll/GetAllSemesters/GetAllSemesters.h"
#include "../../InputAndValidate/InputAndValidateSemester/InputAndValidateSemester.h"
#include "../../Save/SaveCurrentSemester/SaveCurrentSemester.h"

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
}

Semester createSemester() {
    Node<Semester> *allSemesters = getAllSemesters();
    Node<std::string> *allSchoolYears = getAllSchoolYears();
    Semester semester;
    bool validSemester = false;

    do {
        try {
            inputSemesterSchoolYearAndNumber(semester);
            inputSemesterDates(semester);
            validateSemesterSchoolYearAndNumber(
                allSemesters, allSchoolYears, semester, true
            );
            validateSemesterDates(semester);

            if (!checkDateBeforeAddToList(allSemesters, semester)) {
                std::cout << "Your start/end date can't overlap other semesters, please "
                             "try again!\n";
                continue;
            }

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
    std::cout << "Semester successfully added!\n";
    return semester;
}
