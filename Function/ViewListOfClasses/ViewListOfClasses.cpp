#include "ViewListOfClasses.h"

#include <fstream>

#include "../OpenFile/OpenFile.h"

void viewListOfClasses() {
    std::ifstream fin;
    readFile(fin, "Class.txt");

    std::string className;
    std::cout << "This is the list of all classes: " << '\n';
    while (fin.good()) {
        getline(std::cin, className);
        std::cout << className << '\n';
    }

    fin.close();
}