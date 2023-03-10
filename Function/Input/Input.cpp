#include "Input.h"

int intInput() {
    std::string input;
    getline(std::cin, input);

    for (char c : input) {
        if (!isdigit(c)) {
            throw std::invalid_argument("The input is not an integer!\n");
        }
    }

    try {
        return stoi(input);
    } catch (...) {
        throw std::out_of_range("The input is out of integer range!\n");
    }
}

double doubleInput() {
    int numberOfDecimalPoint = 0;
    std::string input;
    getline(std::cin, input);

    for (char c : input) {
        if (c == '.') {
            if (numberOfDecimalPoint++) {
                throw std::invalid_argument("The input is not a double!\n");
            }
        } else if (!isdigit(c)) {
            throw std::invalid_argument("The input is not a double!\n");
        }
    }

    try {
        return stod(input);
    } catch (...) {
        throw std::out_of_range("The input is out of double range!\n");
    }
}
