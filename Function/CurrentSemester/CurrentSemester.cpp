#include "CurrentSemester.h"

#include "../GetAll/GetAllSchoolYears/GetAllSchoolYears.h"
#include "../GetAll/GetAllSemesters/GetAllSemesters.h"
#include "../Input/Input.h"
#include "../InputAndValidate/InputAndValidateSemester/InputAndValidateSemester.h"
#include "../Save/SaveCurrentSemester/SaveCurrentSemester.h"

Semester getCurrentSemester() {
    std::ifstream fin;
    readFile(fin, "Data/CurrentSemester.txt");
    Semester semester;
    getline(fin, semester.schoolYearName);

    if (fin.good()) {
        semester.number = intInput(fin);
        getline(fin, semester.startDate);
        getline(fin, semester.endDate);
    }

    fin.close();
    return semester;
}

void changeCurrentSemester(Semester &currentSemester, const User &currentUser) {
    Node<Semester> *allSemesters = getAllSemesters(), *cur = allSemesters;

    if (!allSemesters) {
        std::cout << "There's no semester at the moment, please ";

        if (currentUser.username != "admin") {
            std::cout << "ask the admin to ";
        }

        std::cout << "create one!\n";
        return;
    }

    Node<std::string> *allSchoolYears = getAllSchoolYears();
    bool validSemester = false;

    do {
        try {
            inputSemesterSchoolYearAndNumber(currentSemester);
            validateSemesterSchoolYearAndNumber(
                allSemesters, allSchoolYears, currentSemester, false
            );

            for (; cur; cur = cur->next) {
                Semester semester = cur->data;

                if (semester.schoolYearName == currentSemester.schoolYearName &&
                    semester.number == currentSemester.number) {
                    currentSemester.startDate = semester.startDate;
                    currentSemester.endDate = semester.endDate;
                    break;
                }
            }

            validSemester = true;
        } catch (std::exception &error) {
            std::cout << error.what();
        }
    } while (!validSemester);

    saveCurrentSemester(currentSemester);
    deleteLinkedList(allSemesters);
    deleteLinkedList(allSchoolYears);
    std::cout << "Current semester successfully changed!\n";
}
