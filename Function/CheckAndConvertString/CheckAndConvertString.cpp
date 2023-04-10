#include "CheckAndConvertString.h"

#include <conio.h>

int checkAndConvertToInt(std::string input, const std::string &fieldName) {
    int n = input.size();

    if (!isdigit(input[0]) && input[0] != '-') {
        throw std::invalid_argument(
            "The inputted " + fieldName + " is not an integer!\n"
        );
    }

    for (int i = 1; i < n; ++i) {
        if (!isdigit(input[i])) {
            throw std::invalid_argument(
                "The inputted " + fieldName + " is not an integer!\n"
            );
        }
    }

    try {
        return stoi(input);
    } catch (...) {
        throw std::invalid_argument(
            "The inputted " + fieldName + " is out of integer range!\n"
        );
    }
}

double checkAndConvertToScore(std::string input, const std::string &fieldName) {
    int numberOfDecimalPoint = 0, n = input.size();
    double score;

    if (!isdigit(input[0]) && input[0] != '-') {
        throw std::invalid_argument("The inputted " + fieldName + " is not a score!\n");
    }

    for (int i = 1; i < n; ++i) {
        if (input[i] == '.') {
            if (numberOfDecimalPoint++) {
                throw std::invalid_argument(
                    "The inputted " + fieldName + " is not a score!\n"
                );
            }
        } else if (!isdigit(input[i])) {
            throw std::invalid_argument(
                "The inputted " + fieldName + " is not a score!\n"
            );
        }
    }

    try {
        score = stod(input);
    } catch (...) {
        throw std::invalid_argument(
            "The inputted " + fieldName + " is out of valid score range!\n"
        );
    }

    if (score < 0 || score > 10) {
        throw std::invalid_argument(
            "The inputted " + fieldName + " is out of valid score range!\n"
        );
    }

    return score;
}

std::string normalization(const std::string &str) {
    std::string result;
    bool capitalize = true, whitespace = false;
    int length = str.length();

    for (int i = 0; i < length; ++i) {
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

std::string checkNameAndConvertToName(std::string input, const std::string &fieldName) {
    int length = input.length();

    if (length == 0) {
        throw std::invalid_argument("The inputted " + fieldName + " is not a name!\n");
    }

    for (int i = 0; i < length; ++i) {
        if (input[i] != ' ' &&
            (input[i] < 'A' || (input[i] > 'Z' && input[i] < 'a') || input[i] > 'z')) {
            throw std::invalid_argument(
                "The inputted " + fieldName + " is not a name!\n"
            );
        }
    }

    return normalization(input);
}
