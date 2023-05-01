#ifndef PASSWORD_FUNCTION_H
#define PASSWORD_FUNCTION_H

#include <string>

void hidePassword(char *inputtedPassword, char *savedPassword);
std::string getPasswordFromDateOfBirth(const std::string &dateOfBirth);

#endif
