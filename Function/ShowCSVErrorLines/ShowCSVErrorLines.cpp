#include "ShowCSVErrorLines.h"

void showCSVErrorLines(Node<int> *errorLines, const std::string &errorMessage) {
    if (!errorLines) {
        return;
    }

    std::cout << errorMessage;

    for (; errorLines; errorLines = errorLines->next) {
        std::cout << ' ' << errorLines->data;
    }

    std::cout << "\nPlease check them again!\n";
}
