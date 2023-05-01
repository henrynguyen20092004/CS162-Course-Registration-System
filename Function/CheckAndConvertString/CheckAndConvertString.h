#ifndef CHECK_AND_CONVERT_STRING_H
#define CHECK_AND_CONVERT_STRING_H

#include <string>

int checkAndConvertToInt(std::string input, const std::string &fieldName);
double checkAndConvertToScore(std::string input, const std::string &fieldName);
std::string checkAndConvertToName(std::string input, const std::string &fieldName);
std::string convertScoreToString(double score);

#endif
