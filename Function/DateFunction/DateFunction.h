#ifndef DATE_FUNCTION_H
#define DATE_FUNCTION_H

#include <string>

bool checkDate(const std::string &date);
bool checkDayOfWeek(const std::string &day);
bool compareDate(const std::string &firstDate, const std::string &secondDate);
std::string getToday();

#endif
