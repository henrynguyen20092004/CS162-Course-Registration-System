#include "CheckDate.h"

bool checkLeapYear(int year) {
    return year % 400 == 0 || ((year % 4 == 0) && (year % 100 != 0));
}

bool checkDayMonthYear(const std::string &date) {
    int day = stoi(date.std::string::substr(0, 2));
    int month = stoi(date.std::string::substr(3, 5));
    int year = stoi(date.std::string::substr(6));

    if (day < 1) {
        return false;
    }

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: {
            return day < 32;
        }

        case 4:
        case 6:
        case 9:
        case 11: {
            return day < 31;
        }

        case 2: {
            return checkLeapYear(year) ? day < 30 : day < 29;
        }
    }

    return false;
}

bool checkLengthAndCharacters(const std::string &date) {
    if (date.size() != 10) {
        return false;
    }

    if ((date[2] != '/' && date[2] != '-') ||
        (date[5] != '/' && date[5] != '-')) {
        return false;
    }

    for (int i = 0; i < 10; ++i) {
        if (i == 2 || i == 5) {
            continue;
        }

        if (!isdigit(date[i])) {
            return false;
        }
    }

    return true;
}

bool checkDate(const std::string &date) {
    return checkLengthAndCharacters(date) && checkDayMonthYear(date);
}
