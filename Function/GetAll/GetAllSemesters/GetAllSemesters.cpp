#include "GetAllSemesters.h"

// #include "../../Input/Input.h"

void readSemester(std::ifstream &fin, Semester &semester) {
    getline(fin, semester.schoolYearName);

    if (!fin.good()) {
        return;
    }

    std::string semesterNumber;
    getline(fin, semesterNumber);
    getline(fin, semester.startDate);
    getline(fin, semester.endDate);
    semester.number = stoi(semesterNumber);
}

Node<Semester> *getAllSemesters() {
    return getAll("Data/Semester.txt", readSemester);
}
