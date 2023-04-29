#include "GetCurrentSemester.h"

#include "../OpenFile/OpenFile.h"

Semester getCurrentSemester() {
    Semester semester;
    std::ifstream fin;
    readFile(fin, "Data/CurrentSemester.txt");
    getline(fin, semester.schoolYearName);

    if (fin.good()) {
        std::string semesterNumber;
        getline(fin, semesterNumber);
        semester.number = stoi(semesterNumber);
        getline(fin, semester.startDate);
        getline(fin, semester.endDate);
    }

    fin.close();
    return semester;
}
