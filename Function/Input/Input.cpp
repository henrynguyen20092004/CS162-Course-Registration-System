#include "Input.h"

#include <conio.h>

std::string passwordInput(const std::string &prompt) {
    std::string password;
    char passChar;
    std::cout << prompt;

    do {
        passChar = getch();
        if (passChar == '\b') {
            int currentPasswordLength = password.length();

            if (currentPasswordLength != 0) {
                password.erase(--currentPasswordLength);
            }
        } else if (passChar != '\r') {
            password += passChar;
        }
    } while (passChar != '\r');

    std::cout << '\n';
    return password;
}

int intInput() {
    std::string input;
    getline(std::cin, input);
    int n = input.size();

    if (!isdigit(input[0]) && input[0] != '-') {
        throw std::invalid_argument("The input is not an integer!\n");
    }

    for (int i = 1; i < n; i++) {
        if (!isdigit(input[i])) {
            throw std::invalid_argument("The input is not an integer!\n");
        }
    }

    try {
        return stoi(input);
    } catch (...) {
        throw std::out_of_range("The input is out of integer range!\n");
    }
}

double scoreInput(std::istream &in, char delimiter) {
    int numberOfDecimalPoint = 0;
    std::string input;
    getline(in, input, delimiter);
    int n = input.size();

    if (!isdigit(input[0])) {
        throw std::invalid_argument("The input is not a score!\n");
    }

    for (int i = 1; i < n; i++) {
        if (input[i] == '.') {
            if (numberOfDecimalPoint++) {
                throw std::invalid_argument("The input is not a score!\n");
            }
        } else if (!isdigit(input[i])) {
            throw std::invalid_argument("The input is not a score!\n");
        }
    }

    try {
        return stod(input);
    } catch (...) {
        throw std::out_of_range("The input is out of valid score range!\n");
    }
}

std::string normalization(const std::string &str) {
    std::string result;
    bool capitalize = true, whitespace = false;
    int length = str.length();

    for (int i = 0; i < length; i++) {
        if (str[i] == ' ') {
            whitespace = true;
            capitalize = true;
            continue;
        }

        if (whitespace) {
            whitespace = false;

            if (result != "") {
                result += ' ';
            }
        }

        if (capitalize) {
            result += toupper(str[i]);
            capitalize = false;
        } else {
            result += tolower(str[i]);
        }
    }

    return result;
}

std::string nameInput() {
    std::string input;
    getline(std::cin, input);
    int length = input.length();

    for (int i = 0; i < length; ++i) {
        if (input[i] != ' ' &&
            (input[i] < 'A' || (input[i] > 'Z' && input[i] < 'a') || input[i] > 'z')) {
            throw std::invalid_argument("The input is not a name!\n");
        }
    }

    return normalization(input);
}
