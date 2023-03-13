#include "CreateClass.h"

#include <iostream>

#include "../OpenFile/OpenFile.h"

std::string inputClassName() {
    std::string className;
    std::cout << "Please enter the name of class: ";
    getline(std::cin, className);
    return className;
}
void saveClassName(const std::string &className) {
    std::ofstream fout;
    writeFile(fout, "Data/Class.txt", std::ios::app);
    fout << className << '\n';
    fout.close();
}
void createClass() {
    std::string className = inputClassName();
    saveClassName(className);
}