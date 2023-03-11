#include <iostream>

#include "Function/Function.h"
#include "Function/Input/Input.h"

int main() {
    try {
        double test = doubleInput();
        std::cout << test;
    } catch (std::exception &e) {
        std::cout << e.what();
    }

    system("pause");
    processCommand(STOP);
}
