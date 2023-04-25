#include "ShowCSVErrorLines.h"

void showErrorLines(
    Node<int> *errorLines, const std::string &errorMessage, std::string &error
) {
    error += '\n' + errorMessage;

    for (; errorLines; errorLines = errorLines->next) {
        error += ' ' + std::to_string(errorLines->data);
    }
}

void showCSVErrorLines(Node<int> *duplicateErrors, Node<int> *invalidErrors) {
    std::string error;

    if (duplicateErrors) {
        showErrorLines(duplicateErrors, "The following line(s) are duplicated:", error);
        deleteLinkedList(duplicateErrors);
    }

    if (invalidErrors) {
        showErrorLines(
            invalidErrors, "The following line(s) have invalid record(s):", error
        );
        deleteLinkedList(invalidErrors);
    }

    throw std::runtime_error("CSV successfully imported!" + error);
}
