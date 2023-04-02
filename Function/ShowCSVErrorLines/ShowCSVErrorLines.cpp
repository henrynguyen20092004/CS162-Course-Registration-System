#include "ShowCSVErrorLines.h"

void showErrorLines(Node<int> *errorLines, const std::string &errorMessage) {
    if (!errorLines) {
        return;
    }

    std::cout << errorMessage;

    for (; errorLines; errorLines = errorLines->next) {
        std::cout << ' ' << errorLines->data;
    }

    std::cout << '\n';
}

void showCSVErrorLines(Node<int> *duplicateErrors, Node<int> *invalidErrors) {
    if (!duplicateErrors && !invalidErrors) {
        return;
    }

    showErrorLines(duplicateErrors, "The following line(s) are duplicated:");
    showErrorLines(invalidErrors, "The following line(s) have invalid record(s):");
    std::cout << "Please check them again!\n";
}
