#include "CreateSchoolYear.h"

#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

int inputSchoolStartYear() {
    std::cout << "Please enter the starting year of the school year: ";
    return intInput();
}

void saveSchoolYear(int startYear) {
    std::ofstream fout;
    writeFile(fout, "Data/SchoolYear.txt");
    fout << startYear << "-" << startYear + 1 << '\n';
    fout.close();
}

void createSchoolYear() {
    int startYear = inputSchoolStartYear();
    saveSchoolYear(startYear);
}
