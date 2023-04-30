#include "GetCurrentSemester.h"

#include "../../GlobalVar/GlobalVar.h"
#include "../OpenFile/OpenFile.h"

void getCurrentSemester() {
    std::ifstream fin;
    readFile(fin, "Data/CurrentSemester.txt");
    getline(fin, GlobalVar::currentSemester.schoolYearName);

    if (fin.good()) {
        std::string semesterNumber;
        getline(fin, semesterNumber);
        GlobalVar::currentSemester.number = stoi(semesterNumber);
        getline(fin, GlobalVar::currentSemester.startDate);
        getline(fin, GlobalVar::currentSemester.endDate);
    }

    fin.close();
}
