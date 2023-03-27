#include "GetAllSemesters.h"

void readSemester(std::ifstream &fin, Semester &semester) {
    std::string semesterNumber;
    getline(fin, semester.schoolYearName);

    if (!fin.good()) {
        return;
    }

    getline(fin, semesterNumber);
    semester.number = stoi(semesterNumber);
    getline(fin, semester.startDate);
    getline(fin, semester.endDate);
}

Node<Semester> *getAllSemesters() {
    return getAll("Data/Semester.txt", readSemester);
}
