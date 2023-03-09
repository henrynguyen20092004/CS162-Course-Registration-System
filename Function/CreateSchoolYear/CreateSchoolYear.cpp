#include "CreateSchoolYear.h"

#include <fstream>
#include <iostream>

int inputSchoolYear() {
    int startYear;
    std::cout << "Please enter the starting time: ";
    std::cin >> startYear;
    return startYear;
}

void saveFile(int startYear) {
    std::ofstream fout;
    fout.open("../Data/SchoolYear.txt");
    fout << startYear << "-" << startYear + 1 << '\n';
    fout.close();
}
void CreateSchoolYear() {
    int startYear = inputSchoolYear();
    saveFile(startYear);
}