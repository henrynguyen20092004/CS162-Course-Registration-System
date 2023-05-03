#include "ChangeCurrentSemester.h"

#include "../../GlobalVar/GlobalVar.h"
#include "../Save/SaveCurrentSemester/SaveCurrentSemester.h"

Semester changeCurrentSemester(char** dropDownItems) {
    for (Node<Semester>* cur = GlobalVar::allData.allSemesters; cur; cur = cur->next) {
        Semester semester = cur->data;

        if (semester.schoolYearName == dropDownItems[0] &&
            semester.number == stoi(std::string(dropDownItems[1]))) {
            saveCurrentSemester(semester);
            return semester;
        }
    }

    throw std::invalid_argument("Semester doesn't exist, please try again!");
}
