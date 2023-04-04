#include "DateFunction.h"

#include <ctime>

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

    if ((date[2] != '/' && date[2] != '-') || (date[5] != '/' && date[5] != '-')) {
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

bool checkDayOfWeek(const std::string &day) {
    return day == "MON" || day == "TUE" || day == "WED" || day == "THU" || day == "FRI" ||
           day == "SAT";
}

bool compareDate(const std::string &firstDate, const std::string &secondDate) {
    if (stoi(secondDate.substr(6)) != stoi(firstDate.substr(6))) {
        return stoi(secondDate.substr(6)) > stoi(firstDate.substr(6));
    }

    if (stoi(secondDate.substr(3, 5)) != stoi(firstDate.substr(3, 5))) {
        return stoi(secondDate.substr(3, 5)) > stoi(firstDate.substr(3, 5));
    }

    return stoi(secondDate.substr(0, 2)) > stoi(firstDate.substr(0, 2));
}

std::string getToday() {
    time_t now = time(0);
    tm *today = localtime(&now);
    std::string day = std::to_string(today->tm_mday),
                month = std::to_string(1 + today->tm_mon),
                year = std::to_string(1900 + today->tm_year);

    if (day.size() == 1) {
        day = '0' + day;
    }

    if (month.size() == 1) {
        month = '0' + month;
    }

    return day + '/' + month + '/' + year;
}
