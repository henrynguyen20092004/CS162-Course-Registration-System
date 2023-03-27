#include "GetAllSemesters.h"

void readSemester(std::ifstream &fin, Semester &semester) {
    std::string semesterNumber;
    getline(fin, semester.schoolYearName);
    getline(fin, semesterNumber);
    semester.number = stoi(semesterNumber);
    getline(fin, semester.startDate);
    getline(fin, semester.endDate);
}

Node<Semester> *getAllSemester() {
    return getAll("Data/Semester.txt", readSemester);
}
