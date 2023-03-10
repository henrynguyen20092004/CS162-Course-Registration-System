#include <iostream>

#include "Function/Function.h"
#include "Function/OpenFile/OpenFile.h"

int main() {
    std::ifstream fin;
    try {
        readFile(fin, "Data/User.txt");
        std::string test;
        fin >> test;
        std::cout << test;
        fin.close();
    } catch (std::exception &e) {
        std::cerr << e.what();
    }

    std::cout << "Hello, world!\n";
    system("pause");
    processCommand(STOP);
}
