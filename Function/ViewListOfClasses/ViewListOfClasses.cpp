#include "ViewListOfClasses.h"

#include "../OpenFile/OpenFile.h"
#include <iostream>

void viewListOfClasses() {
    std::ifstream fin;
    readFile(fin, "Data/Class.txt");

    std::string className;
    std::cout << "This is the list of all classes: " << '\n';
    while (fin.good()) {
        getline(std::cin, className);
        std::cout << className << '\n';
    }

    fin.close();
}
