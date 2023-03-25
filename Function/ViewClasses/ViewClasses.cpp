#include "ViewClasses.h"

#include <iostream>

#include "../OpenFile/OpenFile.h"

void viewClasses() {
    std::ifstream fin;
    readFile(fin, "Data/Class.txt");

    std::string className;
    std::cout << "This is the list of all classes: " << '\n';

    while (fin.good()) {
        getline(fin, className);

        if (className != "") {
            std::cout << className << '\n';
        }
    }

    fin.close();
}
