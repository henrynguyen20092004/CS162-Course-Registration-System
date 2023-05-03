#include "ShowCSVErrorLines.h"

#include <stdexcept>

void showErrorLines(
    Node<int> *errorLines, const std::string &errorMessage, std::string &error
) {
    error += errorMessage;

    for (; errorLines; errorLines = errorLines->next) {
        error += ' ' + std::to_string(errorLines->data);
    }

    error += '\n';
}

void showCSVErrorLines(
    Node<int> *duplicateErrors, Node<int> *invalidErrors, int numberOfLines
) {
    if (numberOfLines == 1) {
        throw std::invalid_argument("CSV has no records, please try again!");
    }

    int numberOfDuplicates = getLinkedListSize(duplicateErrors),
        numberOfInvalids = getLinkedListSize(invalidErrors);

    if (numberOfDuplicates + numberOfInvalids == numberOfLines - 1) {
        if (numberOfDuplicates > 0) {
            throw std::invalid_argument("CSV already imported, please try again!");
        } else {
            throw std::invalid_argument("CSV has only invalid records, please try again!"
            );
        }
    }

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

    throw std::runtime_error(error);
}
