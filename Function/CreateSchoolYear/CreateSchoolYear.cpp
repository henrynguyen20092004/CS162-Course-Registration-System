#include "CreateSchoolYear.h"

#include "../Input/Input.h"
#include "../OpenFile/OpenFile.h"

int inputSchoolStartYear() {
    bool valid;
    int startYear;
    do {
        try {
            startYear = intInput();
            std::cout << "Please enter the starting year (yyyy) of the school year: ";
            valid = (startYear > 999 && startYear < 10000);
            if (!valid) {
                std::cout << "Invalid start year, please enter again!\n";
            }
        } catch (std::exception &error) {
            std::cout << error.what();
        }

    } while (!valid);
    return startYear;
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
