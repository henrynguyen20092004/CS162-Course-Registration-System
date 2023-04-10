#ifndef CHECK_AND_CONVERT_STRING_H
#define CHECK_AND_CONVERT_STRING_H

#include <iostream>

int checkAndConvertToInt(std::string input, const std::string &fieldName);
double checkAndConvertToScore(std::string input, const std::string &fieldName);
std::string checkNameAndConvertToName(std::string input, const std::string &fieldName);

#endif