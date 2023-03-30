#include "GetAllSemesters.h"

#include "../../Input/Input.h"

void readSemester(std::ifstream &fin, Semester &semester) {
    getline(fin, semester.schoolYearName);

    if (!fin.good()) {
        return;
    }

    semester.number = intInput(fin);
    getline(fin, semester.startDate);
    getline(fin, semester.endDate);
}

Node<Semester> *getAllSemesters() {
    return getAll("Data/Semester.txt", readSemester);
}
