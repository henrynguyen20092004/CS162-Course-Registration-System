#include "SaveCurrentSemester.h"

#include "../../OpenFile/OpenFile.h"

void saveCurrentSemester(const Semester &currentSemester) {
    std::ofstream fout;
    writeFile(fout, "Data/CurrentSemester.txt");
    fout << currentSemester.schoolYearName << '\n';
    fout << currentSemester.number << '\n';
    fout << currentSemester.startDate << '\n';
    fout << currentSemester.endDate << '\n';
    fout.close();
}
