#include "CreateSemester.h"

#include "../../../GlobalVar/GlobalVar.h"
#include "../../Check/CheckSemester/CheckSemester.h"
#include "../../CheckAndConvertString/CheckAndConvertString.h"
#include "../../DateFunction/DateFunction.h"
#include "../../InputAndValidate/InputAndValidateSemester/InputAndValidateSemester.h"
#include "../../OpenFile/OpenFile.h"
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

void addSemseterToList(const Semester &newSemester) {
    Node<Semester> *newNode = new Node(newSemester);

    if (!GlobalVar::allData.allSemesters) {
        GlobalVar::allData.allSemesters = newNode;
        return;
    }

    Node<Semester> *cur = GlobalVar::allData.allSemesters, *prev = nullptr;

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
        newNode->next = cur;
        GlobalVar::allData.allSemesters = newNode;
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

    fout.close();
}

Semester createSemester(char **inputs, char **dropDownItems) {
    Semester semester;
    semester.schoolYearName = dropDownItems[0];
    semester.number = stoi(std::string(dropDownItems[1]));
    semester.startDate = inputs[0];
    semester.endDate = inputs[1];

    if (checkSemesterExists(
            GlobalVar::allData.allSemesters, semester.number, semester.schoolYearName
        )) {
        throw std::invalid_argument("This semester already exists, please try again!");
    }

    validateSemesterDates(semester);

    if (!checkDateBeforeAddToList(GlobalVar::allData.allSemesters, semester)) {
        throw std::invalid_argument(
            "Your start/end date can't overlap other semesters, please try again!"
        );
    }

    addSemseterToList(semester);
    saveSemester(GlobalVar::allData.allSemesters);
    saveCurrentSemester(semester);
    return semester;
}
