#ifndef INPUT_H
#define INPUT_H

#include <iostream>

std::string passwordInput(const std::string &prompt);
int intInput(std::istream &in = std::cin);
double scoreInput(std::istream &in = std::cin, char delimiter = '\n');
std::string nameInput();

#endif
