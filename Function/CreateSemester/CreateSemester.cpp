#include "CreateSemester.h"

#include <fstream>
#include <iostream>

Semester inputSemester() {
    Semester semester;
    std::cout << "Enter school year: ";
    std::cin >> semester.schoolYearName;
    std::cout << "Enter the start day of this school year: ";
    std::cin >> semester.startDate;
    std::cout << "Enter the end day of this school year: ";
    std::cin >> semester.endDate;
    int inputSemesterNumber;
    do {
        std::cout << "Choose semester: ";
        std::cin >> inputSemesterNumber;
        if (inputSemesterNumber > 0 && inputSemesterNumber <= 3) {
            semester.number = static_cast<SemesterNumber>(inputSemesterNumber);
        } else {
            std::cout << "Enter again!\n";
        }
    } while (inputSemesterNumber > 3 || inputSemesterNumber <= 0);
    return semester;
}

void saveSemester(const Semester &semester) {
    std::ofstream fout;
    fout.open("../Data/Semester.txt");
    fout << semester.schoolYearName << '\n'
         << semester.startDate << '\n'
         << semester.endDate << '\n'
         << semester.number << '\n';
    fout.close();
}

void createSemester() {
    Semester semester = inputSemester();
    saveSemester(semester);
}